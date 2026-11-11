//
// StorageManager.cpp - Implementation of the StorageManager class
// This file contains the SQLite storage implementation for document data
//

#include "StorageManager.h"
#include <sqlite3.h>
#include <iostream>
#include <sstream>

namespace Memo {
namespace Storage {

StorageManager::StorageManager(const std::string& db_path) : db_path_(db_path), db_(nullptr) {
    // Constructor implementation
}

StorageManager::~StorageManager() {
    if (db_) {
        sqlite3_close(db_);
    }
}

bool StorageManager::initialize() {
    // Open database connection
    int rc = sqlite3_open(db_path_.c_str(), &db_);
    if (rc != SQLITE_OK) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db_) << std::endl;
        sqlite3_close(db_);
        db_ = nullptr;
        return false;
    }

    // Create schema
    if (!createSchema()) {
        std::cerr << "Failed to create database schema" << std::endl;
        return false;
    }

    return true;
}

bool StorageManager::createSchema() {
    const char* sql =
        "CREATE TABLE IF NOT EXISTS documents ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "title TEXT NOT NULL, "
        "content TEXT, "
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP, "
        "updated_at DATETIME DEFAULT CURRENT_TIMESTAMP); "

        "CREATE TABLE IF NOT EXISTS strokes ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "document_id INTEGER, "
        "stroke_data TEXT, "
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP, "
        "FOREIGN KEY(document_id) REFERENCES documents(id));";

    char* err_msg = nullptr;
    int rc = sqlite3_exec(db_, sql, nullptr, nullptr, &err_msg);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to create schema: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return false;
    }

    return true;
}

int64_t StorageManager::createDocument(const std::string& title, const std::string& content) {
    const char* sql = "INSERT INTO documents (title, content) VALUES (?, ?)";

    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_) << std::endl;
        return -1;
    }

    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, content.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int64_t doc_id = (rc == SQLITE_DONE) ? sqlite3_last_insert_rowid(db_) : -1;

    sqlite3_finalize(stmt);

    return doc_id;
}

bool StorageManager::loadDocument(int64_t doc_id, std::string& title, std::string& content) const {
    const char* sql = "SELECT title, content FROM documents WHERE id = ?";

    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }

    sqlite3_bind_int64(stmt, 1, doc_id);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const char* title_ptr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* content_ptr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        if (title_ptr) title = title_ptr;
        if (content_ptr) content = content_ptr;
    } else {
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool StorageManager::updateDocument(int64_t doc_id, const std::string& title, const std::string& content) {
    const char* sql = "UPDATE documents SET title = ?, content = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?";

    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, content.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 3, doc_id);

    rc = sqlite3_step(stmt);
    bool success = (rc == SQLITE_DONE);

    sqlite3_finalize(stmt);
    return success;
}

bool StorageManager::deleteDocument(int64_t doc_id) {
    const char* sql = "DELETE FROM documents WHERE id = ?";

    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }

    sqlite3_bind_int64(stmt, 1, doc_id);

    rc = sqlite3_step(stmt);
    bool success = (rc == SQLITE_DONE);

    sqlite3_finalize(stmt);
    return success;
}

std::vector<std::pair<int64_t, std::string>> StorageManager::getAllDocuments() const {
    std::vector<std::pair<int64_t, std::string>> documents;

    const char* sql = "SELECT id, title FROM documents ORDER BY created_at DESC";

    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_) << std::endl;
        return documents;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int64_t id = sqlite3_column_int64(stmt, 0);
        const char* title_ptr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string title = (title_ptr) ? title_ptr : "";

        documents.emplace_back(id, title);
    }

    sqlite3_finalize(stmt);
    return documents;
}

bool StorageManager::saveStrokes(int64_t doc_id, const std::string& stroke_data) {
    const char* sql = "INSERT INTO strokes (document_id, stroke_data) VALUES (?, ?)";

    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_) << std::endl;
        return false;
    }

    sqlite3_bind_int64(stmt, 1, doc_id);
    sqlite3_bind_text(stmt, 2, stroke_data.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    bool success = (rc == SQLITE_DONE);

    sqlite3_finalize(stmt);
    return success;
}

std::string StorageManager::loadStrokes(int64_t doc_id) const {
    const char* sql = "SELECT stroke_data FROM strokes WHERE document_id = ? ORDER BY created_at ASC";

    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db_) << std::endl;
        return "";
    }

    sqlite3_bind_int64(stmt, 1, doc_id);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const char* data_ptr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string stroke_data = (data_ptr) ? data_ptr : "";

        sqlite3_finalize(stmt);
        return stroke_data;
    }

    sqlite3_finalize(stmt);
    return "";
}

} // namespace Storage
} // namespace Memo