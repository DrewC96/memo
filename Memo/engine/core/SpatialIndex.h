//
// SpatialIndex.h - Spatial index for efficient document element lookup
// This file defines the spatial indexing system used for organizing document elements
//

#pragma once

#include <vector>
#include <memory>
#include "Stroke.h"

namespace Memo {
namespace Core {

/**
 * @brief Rectangle structure for spatial operations
 */
struct Rectangle {
    float x, y, width, height;

    Rectangle(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f)
        : x(x), y(y), width(width), height(height) {}
};

/**
 * @brief SpatialIndex class for efficient document element organization
 *
 * The spatial index organizes document elements (strokes, text, etc.) in a way
 * that allows for efficient queries based on spatial relationships. This is
 * particularly important for features like:
 * - Finding strokes within a selection area
 * - Collision detection between elements
 * - Efficient rendering of visible elements
 */
class SpatialIndex {
public:
    /**
     * @brief Construct a new SpatialIndex object
     * @param cell_size Size of each grid cell in the spatial index (default: 100.0f)
     */
    explicit SpatialIndex(float cell_size = 100.0f);

    /**
     * @brief Destroy the SpatialIndex object
     */
    ~SpatialIndex();

    /**
     * @brief Insert an element into the spatial index
     * @param element_id Unique identifier for the element
     * @param bounds Bounding rectangle of the element
     */
    void insert(const std::string& element_id, const Rectangle& bounds);

    /**
     * @brief Remove an element from the spatial index
     * @param element_id Identifier of the element to remove
     */
    void remove(const std::string& element_id);

    /**
     * @brief Update an element's position in the spatial index
     * @param element_id Identifier of the element to update
     * @param new_bounds New bounding rectangle for the element
     */
    void update(const std::string& element_id, const Rectangle& new_bounds);

    /**
     * @brief Query elements that intersect with a given rectangle
     * @param bounds Query rectangle
     * @return std::vector<std::string> Vector of element IDs that intersect
     */
    std::vector<std::string> query(const Rectangle& bounds) const;

    /**
     * @brief Get all elements in the spatial index
     * @return std::vector<std::string> Vector of all element IDs
     */
    std::vector<std::string> getAllElements() const;

private:
    float cell_size_;              // Size of each grid cell
    struct Cell {
        Rectangle bounds;
        std::vector<std::string> elements;

        Cell(const Rectangle& bounds) : bounds(bounds) {}
    };

    std::vector<Cell> cells_;      // Grid of cells for spatial indexing
    std::map<std::string, Rectangle> element_bounds_;  // Mapping from element ID to bounds
};

} // namespace Core
} // namespace Memo