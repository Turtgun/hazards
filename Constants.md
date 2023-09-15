# Constants.hpp

Mainly self-explainable but I'll give you a rundown

## For explanations on namespaces look at [Display.hpp docs](Display.md)

## The code

So here's pi and radToDeg

```cpp
static constexpr double pi = 3.141592653586; // pi
static const double radToDeg = 180/pi;
```

## Ports

Ports are placed in constants so that you can access them from wherever you need that port and dont have to change the number for everyfile you have that port being used. The port numbers are on the brain and connect to the system in question. You'll 100% be changing these.

```cpp
static constexpr unsigned char fl_p = 10; // Port of Front Left motor
static constexpr unsigned char bl_p = 9; // Port of Back Left motor
static constexpr unsigned char btl_p = 6; // Port of Top Back Left motor
static constexpr unsigned char fr_p = 5; // Port of Front Right motor
static constexpr unsigned char br_p = 4; // Port of Back Right motor
static constexpr unsigned char btr_p = 3; // Port of Top Back Right motor
static constexpr unsigned char troller_p = 19; // Port of Roller
    
static constexpr unsigned char cata_p = 16; // Port of the Catapult

static constexpr char button_p = 'A'; // Port of Button for Catapult
static constexpr char xtend1_p = 'B'; // Port of the First pneumatics system
static constexpr char xtend2_p = 'C'; // Port of the Second pnewumatics system

```

## Threshold

Threshold is used for when using the controller. Pretty much the joysticks work in a matter of ticks ranging from -128 to 127. Threshold is just a way in which the controller doesn't do anything unless the amount of ticks is greater than the threshold. Some of our drivers like it because when they get nervous they don't move the robot with their accidental jittering.

```cpp
static constexpr unsigned char threshold = 11; // Threshhold for controller to start moving the robot
```

## Misc

```cpp
static constexpr float trackwidth = 9.9f; // The distance between both the left and an right motors

static constexpr float wheelDiameter = 2.25f; // Diameter of drive wheels
static constexpr double unitsToRevolution = 642.8571429; // Motor units per revolution for drive wheels (900 * 5/7)
static const double inchesPerTick = wheelDiameter*pi/unitsToRevolution; // The inches per tick for the drive encoders
```

## Functions

headingRestrict is a function in which takes the heading of the robot and gives the heading in the range inside [0, 2*pi).

```cpp
static inline double headingRestrict(double heading) {
    if (heading <= 0) heading += pi*2;
    heading = fmod(std::abs(heading),pi*2);
    return heading;
}
```

constrain takes in an input a lower bound and a upper bound, if the input is inbetween the bounds, it returns the input else it will return the respective bound it surpassed.

```cpp
static inline double constrain(double input, double lowerBound, double upperBound) {
    if (input > lowerBound) {
        if (input < upperBound) {
            return input;
        } else {
            return upperBound;
        }
    } else {
        return lowerBound;
    }
}
```

signum returns -1 if the input is less than 0, 0 if its its 0 and 1 if its greater than 0

```cpp
static inline signed char signum(double x){
    return (x > 0) - (x < 0);
}
```
