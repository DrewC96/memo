//
// Document.cpp - Implementation of the Document class
// This file contains the core document model implementation
//

#include "Document.h"
#include "Stroke.h"
#include "SpatialIndex.h"
#include <iostream>

namespace Memo {
namespace Core {

Document::Document(const std::string& title)
    : title_(title),
      content_(""),
      spatial_index_(std::make_unique<SpatialIndex>()) {
    // Constructor implementation
    std::cout << "Document created: " << title_ << std::endl;
}

Document::~Document() {
    // Destructor implementation
    std::cout << "Document destroyed: " << title_ << std::endl;
}

const std::string& Document::getTitle() const {
    return title_;
}

void Document::setTitle(const std::string& title) {
    title_ = title;
}

const std::string& Document::getContent() const {
    return content_;
}

void Document::setContent(const std::string& content) {
    content_ = content;
}

void Document::addStroke(std::shared_ptr<Stroke> stroke) {
    if (stroke) {
        strokes_.push_back(stroke);
        // Update spatial index with new stroke bounds
        auto bounds = stroke->getBounds();
        // In a real implementation, we would add to spatial index
    }
}

void Document::removeStroke(std::shared_ptr<Stroke> stroke) {
    if (stroke) {
        // Remove from strokes vector
        auto it = std::find(strokes_.begin(), strokes_.end(), stroke);
        if (it != strokes_.end()) {
            strokes_.erase(it);
        }
        // Update spatial index - remove from spatial index
        // In a real implementation, we would remove from spatial index
    }
}

const std::vector<std::shared_ptr<Stroke>>& Document::getStrokes() const {
    return strokes_;
}

bool Document::undo() {
    // TODO: Implement undo functionality
    // This would involve restoring the previous state from the undo stack
    if (!undo_stack_.empty()) {
        // Restore state from undo stack
        // Move to redo stack
        return true;
    }
    return false;
}

bool Document::redo() {
    // TODO: Implement redo functionality
    // This would involve restoring the next state from the redo stack
    if (!redo_stack_.empty()) {
        // Restore state from redo stack
        // Move to undo stack
        return true;
    }
    return false;
}

} // namespace Core
} // namespace Memo