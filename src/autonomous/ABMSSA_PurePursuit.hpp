#pragma once

#include "Path.hpp"
#include "Odometry.hpp"
#include <cmath>
#include <cstdlib>
#include <random>

class ABMSSA_PurePursuit {
    private:
        Path path;                      // Path with segments
        Odometry* odometry;             // Pointer to the Odometry object for robot position
        int populationSize;             // Salp population for ABMSSA
        vector<Vector2> salps;          // Positions of salps representing potential lookahead points
        double lookaheadDistance;       // Lookahead distance for Pure Pursuit
        double maxIterations = 10;      // Maximum iterations for ABMSSA adjustment

        std::random_device rd;
        std::mt19937 gen;
        std::normal_distribution<double> distribution{0.0, 1.0};

        int lastTime = 0;
    
        Vector2 currentPosition;
        double currentHeading;

        DriveTrain* dt;

    public:
        ABMSSA_PurePursuit(Path& p, Odometry* odom, DriveTrain* dt, int popSize = 10, double lookDist = 12)
            : path(p), odometry(odom), dt(dt),  populationSize(popSize), lookaheadDistance(lookDist), gen(rd()) {
            initializeSalps();
        }

        void initializeSalps() {
            Vector2 initPos = odometry->pos;
            // Initialize salps near the robot's initial position
            for (int i = 0; i < populationSize; i++) {
                Vector2 offset {gaussianRandom(), gaussianRandom()};
                salps.push_back(initPos + offset); // Use initial position from odometry
            }
        }

        Vector2 updateLookahead() {
            Vector2 bestSalpPosition;
            double minError = std::numeric_limits<double>::max();

            for (int iter = 0; iter < maxIterations; iter++) {
                // Update each salp position using Brownian motion & Adaptive SSA
                for (int i = 0; i < populationSize; i++) {
                    Vector2 salpPos = salps[i];
                    
                    // Apply Brownian motion for exploration
                    salpPos.x += gaussianRandom();
                    salpPos.y += gaussianRandom();

                    // SSA influence (leader/follower behavior)
                    if (i == 0) {
                        salpPos = updateLeader(salpPos, currentPosition);
                    } else {
                        salpPos = updateFollower(salpPos, salps[i - 1]);
                    }

                    // Calculate Pure Pursuit’s lookahead error
                    Vector2 lookaheadPoint = calculateLookaheadPoint(salpPos, currentHeading, lookaheadDistance);
                    double error = calculateError(lookaheadPoint, currentPosition, currentHeading);

                    // Update best salp position if the error is lower
                    if (error < minError) {
                        minError = error;
                        bestSalpPosition = salpPos;
                    }
                }

                // Update salp population based on the best salp’s position
                for (int i = 0; i < populationSize; i++) {
                    salps[i] = salps[i] + adaptiveStepTowards(bestSalpPosition, salps[i]);
                }
            }

            return bestSalpPosition;
        }

        Vector2 calculateLookaheadPoint(Vector2 position, double currentHeading, double lookaheadDistance) {
            // Calculate lookahead point based on the path and lookahead distance
            // Use the path segment to locate the lookahead point given the salp's position
            // Implement this based on your Path class’s segment traversal methods
            return path.segments.head->data.findClosestPointWithinRadius(position, lookaheadDistance);
        }

        double calculateError(Vector2 lookaheadPoint, Vector2 currentPosition, double currentHeading) {
            // Error calculation based on distance and heading difference
            double distanceError = lookaheadPoint.distanceTo(currentPosition);
            double headingError = currentPosition.headingTo(currentHeading, lookaheadPoint);
            return distanceError + headingError;
        }

        Vector2 updateLeader(Vector2 leader, Vector2 currentPosition) {
            // Movement logic for leader salp toward the target
            return leader + adaptiveStepTowards(currentPosition, leader);
        }

        Vector2 updateFollower(Vector2 follower, Vector2 leader) {
            // Movement logic for follower salps
            Vector2 offset = leader - follower;
            return follower + offset * (0.8 + (distribution(gen) + 1.0) * 0.2);
        }

        Vector2 adaptiveStepTowards(Vector2 target, Vector2 position) {
            // Adaptive step size toward target
            return (target - position) * 0.8;
        }

        double gaussianRandom() {
            // Random function for Brownian motion
            double gRand = distribution(gen) * std::sqrt(pros::millis()-lastTime);
            lastTime = pros::millis();
            return gRand;
        }

        void follow() {
            while (true) {
                currentPosition = odometry->pos;
                currentHeading = odometry->heading;

                Vector2 lookaheadPoint = updateLookahead();
                double headingError = currentPosition.headingTo(currentHeading, lookaheadPoint);

                if (headingError > M_PI) headingError -= 2 * M_PI;
                else if (headingError < -M_PI) headingError += 2 * M_PI;      

                double turningRadius = lookaheadDistance/(2.0 * sin(fabs(headingError)));

                double leftDist = ((turningRadius - (trackwidth/2.0)) * headingError)/inchesPerTick;
                double rightDist = ((turningRadius + (trackwidth/2.0)) * headingError)/inchesPerTick;

                dt->left_g.move_relative(leftDist, maxVel);   
                dt->left_g.move_relative(rightDist, maxVel);        

                path.checkIfNearEnd(currentPosition, currentHeading);

                if (path.done) break;

                delay(20);
            }
        }
};
