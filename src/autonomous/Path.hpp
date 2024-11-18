#pragma  once

#include "LinkedList.hpp"
#include "Segment.hpp"
#include "Vector2.hpp"
#include <vector>

using namespace std;

class Path {
    public:
        LinkedList<Segment> segments;
        bool done = false;

    private:
        vector<Vector2> points;
        vector<double> distances;
        vector<double> headings;

        Vector2 getPoint(double t) {
            Vector2 p0,p1,p2,p3;

            p0 = points[(int)t];
            p1 = points[(int)t+1];
            p2 = points[(int)t+2];
            p3 = points[(int)t+3];
            

            t = t - (int) t;
            double tt = t * t;
            double ttt = tt * t;

            double tx = ((2 * p1.x) + (-p0.x + p2.x)*t + (2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x)*tt + (-p0.x + 3 * p1.x - 3 * p2.x + p3.x)*ttt);
            double ty = ((2 * p1.y) + (-p0.y + p2.y)*t + (2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y)*tt + (-p0.y + 3 * p1.y - 3 * p2.y + p3.y)*ttt);

            return Vector2(tx/2,ty/2);
        }
        void setDists(){
            for (int i = 1; i < points.size(); i++) {
                distances.push_back(points[i-1].distanceTo(points[i]));
            }
        }

        void loadSpline() {
            vector<Vector2> sPoints = {points[0]};
            for (double i = 1; i < points.size(); i+=1/distances[(int)i-1]) {
                sPoints.push_back(getPoint(i));
            }
            points = sPoints;
        }

        void loadHeadings() {
            for (int i = 1; i<points.size(); i++) {
                headings.push_back(points[i-1].headingTo(M_PI_2, points[i]));
            }
        }

        void cutLoadSegments() {
            const double angleThreshold = 0.0523599; // 3 degrees in radians
            int startIndex, x = 0;

            while (startIndex < headings.size() - 1) {
                Segment currentSegment;
                currentSegment.addPoint(points[startIndex]); // Start a new segment with the initial point
                
                bool segmentFinalized = false;

                for (int j = startIndex + 1; j < headings.size(); j++) {
                    // Calculate angle difference between headings[startIndex] and headings[j]
                    double angleDifference = fabs(headings[startIndex] - headings[j]);

                    // Normalize angle difference to [0, π]
                    if (angleDifference > M_PI) {
                        angleDifference = 2 * M_PI - angleDifference;
                    }

                    // Check if headings are parallel within the threshold
                    if (angleDifference <= angleThreshold) {
                        // Use the specified midpoint calculation
                        Vector2 midpoint = points[(j - startIndex) / 2 + startIndex];
                        
                        // Add the midpoint as a boundary for segment continuity
                        currentSegment.addPoint(midpoint);
                        
                        // Finalize the segment and add it to the segments list
                        segments.insertAtEnd(currentSegment);

                        // Set the midpoint index as the new start point for the next segment
                        startIndex = (j - startIndex) / 2 + startIndex;
                        segmentFinalized = true;
                        x=0;
                        break;
                    } else {
                        // Temporarily add points for comparison
                        currentSegment.addPoint(points[j]);
                    }
                }

                // If no parallel segment was found, reset to only include the initial point
                if (!segmentFinalized) {
                    currentSegment.keepX(x);               // Clear any added points except the first x
                    currentSegment.addPoint(points[startIndex]);  // Only retain the start point
                    startIndex++;                         // Move to the next point
                    x++; //add to the failcount
                }
            }
        }
    public:
        Path(vector<Vector2> points):points(points){
            setDists();
            loadSpline();
            loadHeadings();
            cutLoadSegments();
        }

        void checkIfNearEnd(Vector2 position, double currentHeading) {
            if (segments.head->data.checkIfNearEnd(position, currentHeading)) {
                segments.head = segments.head->next;
                if (segments.head == nullptr) {
                    done = true;
                }
            }
        }
};