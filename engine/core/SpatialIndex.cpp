//
// SpatialIndex.cpp - Implementation of the SpatialIndex class
// This file contains the spatial indexing implementation for efficient lookups
//

#include "SpatialIndex.h"
#include <algorithm>
#include <cmath>

namespace Memo {
namespace Core {

SpatialIndex::SpatialIndex(float cell_size) : cell_size_(cell_size) {
    // Constructor implementation
}

SpatialIndex::~SpatialIndex() {
    // Destructor implementation
}

void SpatialIndex::insert(const std::string& element_id, const Rectangle& bounds) {
    // Calculate which cells this element intersects with
    int min_cell_x = static_cast<int>(std::floor(bounds.x / cell_size_));
    int max_cell_x = static_cast<int>(std::floor((bounds.x + bounds.width) / cell_size_));
    int min_cell_y = static_cast<int>(std::floor(bounds.y / cell_size_));
    int max_cell_y = static_cast<int>(std::floor((bounds.y + bounds.height) / cell_size_));

    // Add element to all intersecting cells
    for (int x = min_cell_x; x <= max_cell_x; ++x) {
        for (int y = min_cell_y; y <= max_cell_y; ++y) {
            Rectangle cell_bounds(x * cell_size_, y * cell_size_, cell_size_, cell_size_);

            // Find or create the cell
            auto cell_it = std::find_if(cells_.begin(), cells_.end(),
                [&cell_bounds](const Cell& cell) {
                    return cell.bounds.x == cell_bounds.x &&
                           cell.bounds.y == cell_bounds.y;
                });

            if (cell_it != cells_.end()) {
                // Add to existing cell
                cell_it->elements.push_back(element_id);
            } else {
                // Create new cell
                cells_.emplace_back(cell_bounds);
                cells_.back().elements.push_back(element_id);
            }
        }
    }

    // Store bounds for quick lookup
    element_bounds_[element_id] = bounds;
}

void SpatialIndex::remove(const std::string& element_id) {
    // Remove from all cells that contain this element
    for (auto& cell : cells_) {
        auto& elements = cell.elements;
        elements.erase(
            std::remove(elements.begin(), elements.end(), element_id),
            elements.end()
        );
    }

    // Remove from bounds mapping
    element_bounds_.erase(element_id);
}

void SpatialIndex::update(const std::string& element_id, const Rectangle& new_bounds) {
    // Remove from old position
    remove(element_id);

    // Insert into new position
    insert(element_id, new_bounds);
}

std::vector<std::string> SpatialIndex::query(const Rectangle& bounds) const {
    std::vector<std::string> results;

    // Calculate which cells this query intersects with
    int min_cell_x = static_cast<int>(std::floor(bounds.x / cell_size_));
    int max_cell_x = static_cast<int>(std::floor((bounds.x + bounds.width) / cell_size_));
    int min_cell_y = static_cast<int>(std::floor(bounds.y / cell_size_));
    int max_cell_y = static_cast<int>(std::floor((bounds.y + bounds.height) / cell_size_));

    // Check all intersecting cells
    for (int x = min_cell_x; x <= max_cell_x; ++x) {
        for (int y = min_cell_y; y <= max_cell_y; ++y) {
            Rectangle cell_bounds(x * cell_size_, y * cell_size_, cell_size_, cell_size_);

            // Find the cell
            auto cell_it = std::find_if(cells_.begin(), cells_.end(),
                [&cell_bounds](const Cell& cell) {
                    return cell.bounds.x == cell_bounds.x &&
                           cell.bounds.y == cell_bounds.y;
                });

            if (cell_it != cells_.end()) {
                // Check each element in this cell for intersection
                for (const auto& element_id : cell_it->elements) {
                    auto bounds_it = element_bounds_.find(element_id);
                    if (bounds_it != element_bounds_.end()) {
                        const Rectangle& element_bounds = bounds_it->second;

                        // Simple rectangle intersection test
                        if (!(bounds.x + bounds.width < element_bounds.x ||
                              element_bounds.x + element_bounds.width < bounds.x ||
                              bounds.y + bounds.height < element_bounds.y ||
                              element_bounds.y + element_bounds.height < bounds.y)) {
                            results.push_back(element_id);
                        }
                    }
                }
            }
        }
    }

    return results;
}

std::vector<std::string> SpatialIndex::getAllElements() const {
    std::vector<std::string> all_elements;

    for (const auto& cell : cells_) {
        all_elements.insert(all_elements.end(), cell.elements.begin(), cell.elements.end());
    }

    // Remove duplicates
    std::sort(all_elements.begin(), all_elements.end());
    all_elements.erase(std::unique(all_elements.begin(), all_elements.end()), all_elements.end());

    return all_elements;
}

} // namespace Core
} // namespace Memo