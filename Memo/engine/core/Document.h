//
// Document.h - Core document model for the memo application
// This file defines the main document structure and operations
//

#pragma once

#include <string>
#include <vector>
#include <memory>

namespace Memo {
namespace Core {

// Forward declarations
class Stroke;
class SpatialIndex;

/**
 * @brief Main document class representing a note or collection of notes
 *
 * The Document class manages the core data structures for a memo application,
 * including text content, strokes (for handwriting), spatial relationships,
 * and undo/redo functionality.
 */
class Document {
public:
    /**
     * @brief Construct a new Document object
     * @param title Optional title for the document
     */
    explicit Document(const std::string& title = "Untitled");

    /**
     * @brief Destroy the Document object
     */
    ~Document();

    /**
     * @brief Get the document's title
     * @return const std::string& Reference to the document title
     */
    const std::string& getTitle() const;

    /**
     * @brief Set the document's title
     * @param title The new title for the document
     */
    void setTitle(const std::string& title);

    /**
     * @brief Get the document's content
     * @return const std::string& Reference to the document content
     */
    const std::string& getContent() const;

    /**
     * @brief Set the document's content
     * @param content The new content for the document
     */
    void setContent(const std::string& content);

    /**
     * @brief Add a stroke to the document
     * @param stroke Shared pointer to the stroke to add
     */
    void addStroke(std::shared_ptr<Stroke> stroke);

    /**
     * @brief Remove a stroke from the document
     * @param stroke Shared pointer to the stroke to remove
     */
    void removeStroke(std::shared_ptr<Stroke> stroke);

    /**
     * @brief Get all strokes in the document
     * @return const std::vector<std::shared_ptr<Stroke>>& Vector of stroke pointers
     */
    const std::vector<std::shared_ptr<Stroke>>& getStrokes() const;

    /**
     * @brief Perform undo operation
     * @return bool True if undo was successful, false otherwise
     */
    bool undo();

    /**
     * @brief Perform redo operation
     * @return bool True if redo was successful, false otherwise
     */
    bool redo();

private:
    std::string title_;           // Document title
    std::string content_;         // Document text content
    std::vector<std::shared_ptr<Stroke>> strokes_;  // Handwriting strokes
    std::unique_ptr<SpatialIndex> spatial_index_;   // Spatial index for efficient lookups
    std::vector<std::string> undo_stack_;  // Undo history
    std::vector<std::string> redo_stack_;  // Redo history
};

} // namespace Core
} // namespace Memo