#pragma once

#include <cmath>
#include <sys/_types.h>
namespace Constants {
    static const double pi = 3.14159265358979323846; // pi
    static const double radToDeg = 180/pi;

    static constexpr unsigned char fl_p = 10; // Port of Front Left motor
    static constexpr unsigned char bl_p = 9; // Port of Back Left motor
    static constexpr unsigned char btl_p = 6; // Port of Top Back Left motor
    static constexpr unsigned char fr_p = 5; // Port of Front Right motor
    static constexpr unsigned char br_p = 4; // Port of Back Right motor
    static constexpr unsigned char btr_p = 3; // Port of Top Back Right motor

    static constexpr unsigned char threshold = 11; // Threshhold for controller to start moving the robot
    
    static constexpr float trackwidth = 9.9f; // The distance between both the left and an right motors

    static constexpr float wheelDiameter = 2.25f; // Diameter of drive wheels
    static constexpr double unitsToRevolution = 642.8571429; // Motor units per revolution for drive wheels (900 * 5/7)
    static const double inchesPerTick = wheelDiameter*pi/unitsToRevolution; // The inches per tick for the drive encoders

    static inline double headingRestrict(double heading) {
        if (heading <= 0) heading += pi*2;
        heading = fmod(std::abs(heading),pi*2);
        return heading;
    }
};