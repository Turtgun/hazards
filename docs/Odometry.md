# Odometry.hpp

## Usage

This is to show the relative position of your bobot, along with the angle, its good so that you can use it in you autonomous period. To use it just place in a reference to the DriveTrain and a reference to the label it will be outputting to.

```cpp
DriveTrain dt = DriveTrain();

...

lv_obj_t * odometryInfo = createLabel(lv_scr_act(), DISP_CENTER 150, 40, "Odom Info");
Odometry odom = Odometry(&dt, &odometryInfo);
```

## Configuration

Currently this odometry is configured for 4 motor drive but you can configure to be whatever you want just edit this area

```cpp
newLeft = (dt->fl_mtr.get_position() + dt->bl_mtr.get_position()) / 2 * inchesPerTick;
newRight = (dt->fr_mtr.get_position() + dt->br_mtr.get_position()) / 2 * inchesPerTick;
```
