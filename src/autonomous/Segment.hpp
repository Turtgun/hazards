#pragma once

#include "Vector2.hpp"
#include <vector>
struct Segment {
    std::vector<Vector2> points;
    double threshold = 2.0;

    Vector2 findClosestPointWithinRadius(Vector2 center, double radius) {
        double min = center.distanceTo(points[0]);
        int index = 0;
        for (int i = 1; i < points.size(); i++) {
            double dist = center.distanceTo(points[i]);
            if (dist<=min) {
                index = i;
                min = dist;
            }
        }
        index = (index+1 < points.size()) ? index+1 : index;
        return points[index];
    }

    void addPoint(Vector2 point) {
        points.push_back(point);
    }

    void keepX(int x) {
        if (x < points.size()) {
            points.resize(x); // Keep only the first x points
        }
    }

    bool checkIfNearEnd(Vector2 position, double currentHeading) {
        return  (position.distanceTo(points[points.size()-1]) + 12*fabs(position.headingTo(currentHeading, points[points.size()-1])) < threshold);
    }
};