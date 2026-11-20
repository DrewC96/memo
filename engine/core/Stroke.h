//
// Stroke.h - Represents a single stroke of handwriting or drawing
// This file defines the data structure for individual strokes in the document
//

#pragma once

#include <vector>
#include <memory>

namespace Memo {
namespace Core {

/**
 * @brief Point structure representing a coordinate in 2D space
 */
struct Point {
    float x;    // X coordinate
    float y;    // Y coordinate
    float pressure; // Pressure value (0.0 to 1.0)

    /**
     * @brief Construct a new Point object
     * @param x X coordinate
     * @param y Y coordinate
     * @param pressure Pressure value (default: 0.5)
     */
    Point(float x = 0.0f, float y = 0.0f, float pressure = 0.5f)
        : x(x), y(y), pressure(pressure) {}
};

/**
 * @brief Stroke class representing a sequence of points
 *
 * A stroke represents a continuous line or drawing operation that can be
 * from handwriting input or freehand drawing. Each stroke consists of a
 * series of points with pressure information.
 */
class Stroke {
public:
    /**
     * @brief Construct a new Stroke object
     */
    Stroke();

    /**
     * @brief Construct a new Stroke object with initial points
     * @param points Initial vector of points for the stroke
     */
    explicit Stroke(const std::vector<Point>& points);

    /**
     * @brief Destroy the Stroke object
     */
    ~Stroke();

    /**
     * @brief Get all points in the stroke
     * @return const std::vector<Point>& Vector of points in the stroke
     */
    const std::vector<Point>& getPoints() const;

    /**
     * @brief Add a point to the stroke
     * @param point Point to add
     */
    void addPoint(const Point& point);

    /**
     * @brief Get the start point of the stroke
     * @return Point Start point
     */
    Point getStartPoint() const;

    /**
     * @brief Get the end point of the stroke
     * @return Point End point
     */
    Point getEndPoint() const;

    /**
     * @brief Get the length of the stroke in pixels
     * @return float Length of the stroke
     */
    float getLength() const;

    /**
     * @brief Get the bounding box of the stroke
     * @return Rectangle Bounding box containing all points
     */
    struct Rectangle {
        float x, y, width, height;

        Rectangle(float x = 0.0f, float y = 0.0f, float width = 0.0f, float height = 0.0f)
            : x(x), y(y), width(width), height(height) {}
    };

    Rectangle getBounds() const;

private:
    std::vector<Point> points_;   // Vector of points that make up the stroke
};

} // namespace Core
} // namespace Memo