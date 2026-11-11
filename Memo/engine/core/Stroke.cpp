//
// Stroke.cpp - Implementation of the Stroke class
// This file contains the stroke implementation with point data
//

#include "Stroke.h"
#include <cmath>
#include <algorithm>

namespace Memo {
namespace Core {

Stroke::Stroke() {
    // Default constructor
}

Stroke::Stroke(const std::vector<Point>& points) : points_(points) {
    // Constructor with initial points
}

Stroke::~Stroke() {
    // Destructor
}

const std::vector<Point>& Stroke::getPoints() const {
    return points_;
}

void Stroke::addPoint(const Point& point) {
    points_.push_back(point);
}

Point Stroke::getStartPoint() const {
    if (points_.empty()) {
        return Point(0.0f, 0.0f, 0.5f);
    }
    return points_.front();
}

Point Stroke::getEndPoint() const {
    if (points_.empty()) {
        return Point(0.0f, 0.0f, 0.5f);
    }
    return points_.back();
}

float Stroke::getLength() const {
    if (points_.size() < 2) {
        return 0.0f;
    }

    float length = 0.0f;
    for (size_t i = 1; i < points_.size(); ++i) {
        const Point& prev = points_[i - 1];
        const Point& curr = points_[i];

        float dx = curr.x - prev.x;
        float dy = curr.y - prev.y;
        length += std::sqrt(dx * dx + dy * dy);
    }

    return length;
}

Stroke::Rectangle Stroke::getBounds() const {
    if (points_.empty()) {
        return Rectangle(0.0f, 0.0f, 0.0f, 0.0f);
    }

    float min_x = points_[0].x;
    float max_x = points_[0].x;
    float min_y = points_[0].y;
    float max_y = points_[0].y;

    for (const auto& point : points_) {
        min_x = std::min(min_x, point.x);
        max_x = std::max(max_x, point.x);
        min_y = std::min(min_y, point.y);
        max_y = std::max(max_y, point.y);
    }

    return Rectangle(min_x, min_y, max_x - min_x, max_y - min_y);
}

} // namespace Core
} // namespace Memo