//
// StorageManager.h - SQLite persistence layer for memo application
// This file defines the storage interface and database operations for the application
//

#pragma once

#include <string>
#include <memory>
#include <vector>

// Forward declarations
struct sqlite3;
struct sqlite3_stmt;

namespace Memo {
namespace Storage {

/**
 * @brief StorageManager class for handling SQLite database operations
 *
 * The StorageManager provides an abstraction layer over SQLite for storing
 * and retrieving document data. It handles connection management, query execution,
 * and data serialization/deserialization.
 */
class StorageManager {
public:
    /**
     * @brief Construct a new StorageManager object
     * @param db_path Path to the SQLite database file
     */
    explicit StorageManager(const std::string& db_path);

    /**
     * @brief Destroy the StorageManager object
     */
    ~StorageManager();

    /**
     * @brief Initialize the storage system
     * @return bool True if initialization was successful, false otherwise
     */
    bool initialize();

    /**
     * @brief Create a new document in the database
     * @param title Title of the document
     * @param content Content of the document
     * @return int64_t ID of the created document, or -1 on failure
     */
    int64_t createDocument(const std::string& title, const std::string& content);

    /**
     * @brief Load a document from the database
     * @param doc_id ID of the document to load
     * @param title Output parameter for document title
     * @param content Output parameter for document content
     * @return bool True if loading was successful, false otherwise
     */
    bool loadDocument(int64_t doc_id, std::string& title, std::string& content) const;

    /**
     * @brief Update a document in the database
     * @param doc_id ID of the document to update
     * @param title New title for the document
     * @param content New content for the document
     * @return bool True if update was successful, false otherwise
     */
    bool updateDocument(int64_t doc_id, const std::string& title, const std::string& content);

    /**
     * @brief Delete a document from the database
     * @param doc_id ID of the document to delete
     * @return bool True if deletion was successful, false otherwise
     */
    bool deleteDocument(int64_t doc_id);

    /**
     * @brief Get a list of all documents in the database
     * @return std::vector<std::pair<int64_t, std::string>> Vector of document IDs and titles
     */
    std::vector<std::pair<int64_t, std::string>> getAllDocuments() const;

    /**
     * @brief Save strokes for a document to the database
     * @param doc_id ID of the document
     * @param stroke_data Serialized stroke data
     * @return bool True if saving was successful, false otherwise
     */
    bool saveStrokes(int64_t doc_id, const std::string& stroke_data);

    /**
     * @brief Load strokes for a document from the database
     * @param doc_id ID of the document
     * @return std::string Serialized stroke data, or empty string on failure
     */
    std::string loadStrokes(int64_t doc_id) const;

private:
    std::string db_path_;                 // Path to SQLite database file
    sqlite3* db_;                         // SQLite database handle

    /**
     * @brief Create the database schema
     * @return bool True if schema creation was successful, false otherwise
     */
    bool createSchema();

    /**
     * @brief Prepare a SQL statement
     * @param sql SQL query string
     * @return sqlite3_stmt* Prepared statement or nullptr on failure
     */
    sqlite3_stmt* prepareStatement(const std::string& sql) const;

    /**
     * @brief Execute a non-query SQL statement
     * @param sql SQL query string
     * @return bool True if execution was successful, false otherwise
     */
    bool executeNonQuery(const std::string& sql);

    /**
     * @brief Execute a query and return the result set
     * @param sql SQL query string
     * @return sqlite3_stmt* Prepared statement with results or nullptr on failure
     */
    sqlite3_stmt* executeQuery(const std::string& sql) const;
};

} // namespace Storage
} // namespace Memo