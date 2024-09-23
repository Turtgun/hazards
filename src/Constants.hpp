#pragma once

#include <cmath>
namespace Constants {
    static constexpr unsigned char fl_p = 10; // Port of Front Left motor
    static constexpr unsigned char ml_p = 9; // Port of Middle Left motor
    static constexpr unsigned char bl_p = 8; // Port of Back Left motor
    static constexpr unsigned char fr_p = 20; // Port of Front Right motor
    static constexpr unsigned char mr_p = 19; // Port of Middle Right motor
    static constexpr unsigned char br_p = 18; // Port of Back Right motor

    static constexpr unsigned char cata_p = 11; // Port of the Catapult

    static constexpr unsigned char ele_p = 1; // Port of the Elevation mech

    static constexpr unsigned char flapsL_p = 'A'; // Port for the Left Pneumatic flaps
    static constexpr unsigned char flapsR_p = 'B'; // Port for the Right Pneumatic flaps

    static constexpr unsigned char btn_p = 'C'; // Port for the Catapult's button

    static constexpr unsigned char threshold = 11; // Threshhold for controller to start moving the robot
    
    static constexpr float trackwidth = 4.6f; // The distance between both the left and an right motors

    static const double pi = 3.14159265358979323846; // pi
    static const double radToDeg = 180/pi;
    static constexpr float wheelDiameter = 3.25f; // Diameter of drive wheels

    /*
    1800 ticks/rev with 36:1 gears (BLUE)
    900 ticks/rev with 18:1 gears (GREEN)
    300 ticks/rev with 6:1 gears (RED)
    */

    static constexpr double unitsToRevolution = 642.8571429; // Motor units per revolution for drive wheels (900 * 5/7)
    static const double inchesPerTick = wheelDiameter*pi/unitsToRevolution; // The inches per tick for the drive encoders

    static inline double headingRestrict(double heading) {
        if (heading <= 0) heading += pi*2;
        heading = fmod(std::abs(heading),pi*2);
        return heading;
    }
};