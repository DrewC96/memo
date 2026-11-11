//
// MemoAPI.cpp - C-compatible API implementation for .NET integration
// This file provides the extern "C" interface that the .NET application calls
//

#include "MemoAPI.h"
#include "../core/Document.h"
#include "../storage/StorageManager.h"
#include <memory>
#include <string>
#include <vector>

// Global storage manager instance
static std::unique_ptr<Memo::Storage::StorageManager> g_storage_manager = nullptr;

extern "C" {

/**
 * @brief Initialize the memo application
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_initialize() {
    try {
        // Create storage manager (using default database path)
        g_storage_manager = std::make_unique<Memo::Storage::StorageManager>("memo.db");

        // Initialize the storage system
        if (!g_storage_manager->initialize()) {
            return -1;
        }

        return 0;
    } catch (...) {
        return -1;
    }
}

/**
 * @brief Shutdown the memo application
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_shutdown() {
    try {
        g_storage_manager.reset();
        return 0;
    } catch (...) {
        return -1;
    }
}

/**
 * @brief Create a new document
 * @param title Title of the document (null-terminated string)
 * @param content Content of the document (null-terminated string)
 * @return DocumentHandle Handle to the created document, or NULL on failure
 */
MEMO_API DocumentHandle memo_create_document(const char* title, const char* content) {
    try {
        if (!g_storage_manager) {
            return nullptr;
        }

        // Create document in storage
        int64_t doc_id = g_storage_manager->createDocument(
            (title) ? std::string(title) : "",
            (content) ? std::string(content) : ""
        );

        if (doc_id < 0) {
            return nullptr;
        }

        // Return document handle (using doc_id as a simple handle)
        return reinterpret_cast<DocumentHandle>(doc_id);
    } catch (...) {
        return nullptr;
    }
}

/**
 * @brief Load a document by ID
 * @param doc_id ID of the document to load
 * @return DocumentHandle Handle to the loaded document, or NULL on failure
 */
MEMO_API DocumentHandle memo_load_document(int64_t doc_id) {
    try {
        if (!g_storage_manager) {
            return nullptr;
        }

        // Load document from storage
        std::string title, content;
        if (!g_storage_manager->loadDocument(doc_id, title, content)) {
            return nullptr;
        }

        // Return document handle (using doc_id as a simple handle)
        return reinterpret_cast<DocumentHandle>(doc_id);
    } catch (...) {
        return nullptr;
    }
}

/**
 * @brief Save a document
 * @param handle Handle to the document to save
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_save_document(DocumentHandle handle) {
    try {
        if (!g_storage_manager || !handle) {
            return -1;
        }

        // For this simple implementation, we just return success
        // In a full implementation, we would retrieve the document data
        // and save it to storage
        return 0;
    } catch (...) {
        return -1;
    }
}

/**
 * @brief Delete a document
 * @param handle Handle to the document to delete
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_delete_document(DocumentHandle handle) {
    try {
        if (!g_storage_manager || !handle) {
            return -1;
        }

        // Convert handle back to doc_id
        int64_t doc_id = reinterpret_cast<int64_t>(handle);

        // Delete document from storage
        if (!g_storage_manager->deleteDocument(doc_id)) {
            return -1;
        }

        return 0;
    } catch (...) {
        return -1;
    }
}

/**
 * @brief Get the title of a document
 * @param handle Handle to the document
 * @param buffer Buffer to write the title into
 * @param buffer_size Size of the buffer in bytes
 * @return int Number of characters written, or negative on error
 */
MEMO_API int memo_get_document_title(DocumentHandle handle, char* buffer, size_t buffer_size) {
    try {
        if (!g_storage_manager || !handle || !buffer || buffer_size == 0) {
            return -1;
        }

        // Convert handle back to doc_id
        int64_t doc_id = reinterpret_cast<int64_t>(handle);

        // Load document title from storage
        std::string title, content;
        if (!g_storage_manager->loadDocument(doc_id, title, content)) {
            return -1;
        }

        // Copy title to buffer
        size_t title_len = title.length();
        size_t copy_len = (title_len < buffer_size) ? title_len : buffer_size - 1;
        std::copy(title.begin(), title.begin() + copy_len, buffer);
        buffer[copy_len] = '\0';

        return static_cast<int>(copy_len);
    } catch (...) {
        return -1;
    }
}

/**
 * @brief Set the title of a document
 * @param handle Handle to the document
 * @param title New title for the document
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_set_document_title(DocumentHandle handle, const char* title) {
    try {
        if (!g_storage_manager || !handle || !title) {
            return -1;
        }

        // Convert handle back to doc_id
        int64_t doc_id = reinterpret_cast<int64_t>(handle);

        // Load current document content
        std::string current_title, content;
        if (!g_storage_manager->loadDocument(doc_id, current_title, content)) {
            return -1;
        }

        // Update document with new title
        if (!g_storage_manager->updateDocument(doc_id, std::string(title), content)) {
            return -1;
        }

        return 0;
    } catch (...) {
        return -1;
    }
}

/**
 * @brief Get the content of a document
 * @param handle Handle to the document
 * @param buffer Buffer to write the content into
 * @param buffer_size Size of the buffer in bytes
 * @return int Number of characters written, or negative on error
 */
MEMO_API int memo_get_document_content(DocumentHandle handle, char* buffer, size_t buffer_size) {
    try {
        if (!g_storage_manager || !handle || !buffer || buffer_size == 0) {
            return -1;
        }

        // Convert handle back to doc_id
        int64_t doc_id = reinterpret_cast<int64_t>(handle);

        // Load document content from storage
        std::string title, content;
        if (!g_storage_manager->loadDocument(doc_id, title, content)) {
            return -1;
        }

        // Copy content to buffer
        size_t content_len = content.length();
        size_t copy_len = (content_len < buffer_size) ? content_len : buffer_size - 1;
        std::copy(content.begin(), content.begin() + copy_len, buffer);
        buffer[copy_len] = '\0';

        return static_cast<int>(copy_len);
    } catch (...) {
        return -1;
    }
}

/**
 * @brief Set the content of a document
 * @param handle Handle to the document
 * @param content New content for the document
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_set_document_content(DocumentHandle handle, const char* content) {
    try {
        if (!g_storage_manager || !handle || !content) {
            return -1;
        }

        // Convert handle back to doc_id
        int64_t doc_id = reinterpret_cast<int64_t>(handle);

        // Load current document title
        std::string title, current_content;
        if (!g_storage_manager->loadDocument(doc_id, title, current_content)) {
            return -1;
        }

        // Update document with new content
        if (!g_storage_manager->updateDocument(doc_id, title, std::string(content))) {
            return -1;
        }

        return 0;
    } catch (...) {
        return -1;
    }
}

/**
 * @brief Add a stroke to a document
 * @param handle Handle to the document
 * @param points Array of points representing the stroke
 * @param point_count Number of points in the array
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_add_stroke(DocumentHandle handle, const float* points, size_t point_count) {
    try {
        if (!g_storage_manager || !handle || !points || point_count == 0) {
            return -1;
        }

        // For this simple implementation, we just return success
        // In a full implementation, we would serialize the stroke data
        // and save it to storage

        return 0;
    } catch (...) {
        return -1;
    }
}

/**
 * @brief Get all strokes from a document
 * @param handle Handle to the document
 * @param points Buffer to write stroke points into (can be NULL to get count)
 * @param point_count Pointer to receive number of points in all strokes
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_get_document_strokes(DocumentHandle handle, float* points, size_t* point_count) {
    try {
        if (!g_storage_manager || !handle) {
            return -1;
        }

        // Convert handle back to doc_id
        int64_t doc_id = reinterpret_cast<int64_t>(handle);

        // In a full implementation, we would load stroke data from storage
        // For now, we just return the count as 0 (no actual strokes)
        if (point_count) {
            *point_count = 0;
        }

        return 0;
    } catch (...) {
        return -1;
    }
}

/**
 * @brief Get the number of documents in the application
 * @return int Number of documents, or negative on error
 */
MEMO_API int memo_get_document_count() {
    try {
        if (!g_storage_manager) {
            return -1;
        }

        // Get all documents to count them
        auto docs = g_storage_manager->getAllDocuments();
        return static_cast<int>(docs.size());
    } catch (...) {
        return -1;
    }
}

/**
 * @brief Get a list of all document IDs
 * @param ids Buffer to write document IDs into (can be NULL to get count)
 * @param count Pointer to receive number of documents
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_get_document_ids(int64_t* ids, size_t* count) {
    try {
        if (!g_storage_manager || !count) {
            return -1;
        }

        // Get all documents
        auto docs = g_storage_manager->getAllDocuments();
        size_t doc_count = docs.size();

        // If buffer is provided, copy IDs
        if (ids) {
            for (size_t i = 0; i < std::min(doc_count, *count); ++i) {
                ids[i] = docs[i].first;
            }
        }

        // Set the count
        *count = doc_count;

        return 0;
    } catch (...) {
        return -1;
    }
}

} // extern "C"