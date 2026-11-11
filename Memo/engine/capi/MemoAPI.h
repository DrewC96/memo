//
// MemoAPI.h - C-compatible API boundary for .NET application integration
// This file defines the extern "C" interface that the .NET application calls
//

#pragma once

#ifdef _WIN32
    #ifdef MEMO_EXPORTS
        #define MEMO_API __declspec(dllexport)
    #else
        #define MEMO_API __declspec(dllimport)
    #endif
#else
    #define MEMO_API
#endif

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Handle for a document instance
 *
 * This is an opaque handle used to reference document instances in the C API.
 * The actual implementation is hidden from the .NET application.
 */
typedef void* DocumentHandle;

/**
 * @brief Initialize the memo application
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_initialize();

/**
 * @brief Shutdown the memo application
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_shutdown();

/**
 * @brief Create a new document
 * @param title Title of the document (null-terminated string)
 * @param content Content of the document (null-terminated string)
 * @return DocumentHandle Handle to the created document, or NULL on failure
 */
MEMO_API DocumentHandle memo_create_document(const char* title, const char* content);

/**
 * @brief Load a document by ID
 * @param doc_id ID of the document to load
 * @return DocumentHandle Handle to the loaded document, or NULL on failure
 */
MEMO_API DocumentHandle memo_load_document(int64_t doc_id);

/**
 * @brief Save a document
 * @param handle Handle to the document to save
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_save_document(DocumentHandle handle);

/**
 * @brief Delete a document
 * @param handle Handle to the document to delete
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_delete_document(DocumentHandle handle);

/**
 * @brief Get the title of a document
 * @param handle Handle to the document
 * @param buffer Buffer to write the title into
 * @param buffer_size Size of the buffer in bytes
 * @return int Number of characters written, or negative on error
 */
MEMO_API int memo_get_document_title(DocumentHandle handle, char* buffer, size_t buffer_size);

/**
 * @brief Set the title of a document
 * @param handle Handle to the document
 * @param title New title for the document
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_set_document_title(DocumentHandle handle, const char* title);

/**
 * @brief Get the content of a document
 * @param handle Handle to the document
 * @param buffer Buffer to write the content into
 * @param buffer_size Size of the buffer in bytes
 * @return int Number of characters written, or negative on error
 */
MEMO_API int memo_get_document_content(DocumentHandle handle, char* buffer, size_t buffer_size);

/**
 * @brief Set the content of a document
 * @param handle Handle to the document
 * @param content New content for the document
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_set_document_content(DocumentHandle handle, const char* content);

/**
 * @brief Add a stroke to a document
 * @param handle Handle to the document
 * @param points Array of points representing the stroke
 * @param point_count Number of points in the array
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_add_stroke(DocumentHandle handle, const float* points, size_t point_count);

/**
 * @brief Get all strokes from a document
 * @param handle Handle to the document
 * @param points Buffer to write stroke points into (can be NULL to get count)
 * @param point_count Pointer to receive number of points in all strokes
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_get_document_strokes(DocumentHandle handle, float* points, size_t* point_count);

/**
 * @brief Get the number of documents in the application
 * @return int Number of documents, or negative on error
 */
MEMO_API int memo_get_document_count();

/**
 * @brief Get a list of all document IDs
 * @param ids Buffer to write document IDs into (can be NULL to get count)
 * @param count Pointer to receive number of documents
 * @return int 0 on success, non-zero on failure
 */
MEMO_API int memo_get_document_ids(int64_t* ids, size_t* count);

#ifdef __cplusplus
}
#endif