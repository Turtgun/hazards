# Drivetrain.hpp

## Motor

To initialize a motor you place in the port number of that motor and whether you want to reverse or it not (default false)

### 6 motor drive example

```cpp
    Motor fl_mtr = Motor(fl_p, true);
    Motor btl_mtr = Motor(btl_p);
    Motor bl_mtr = Motor(bl_p, true);
    Motor fr_mtr = Motor(fr_p);
    Motor btr_mtr = Motor(btr_p, true);
    Motor br_mtr = Motor(br_p);
```

## Motor_Group

Motor groups take in a list of motors and place them into a group so that you can edit the group as a whole

```cpp
    Motor_Group left_g =  Motor_Group({fl_mtr, btl_mtr, bl_mtr});
    Motor_Group right_g = Motor_Group({fr_mtr, btr_mtr, br_mtr});
```

## teleMove

Telemove is a function with nothing in it until the initialization phase of the robot, this is to say you can make teleMove in tankDrive or arcadeDrive by using a button, here's what I did last year.

### main.cpp

```cpp
bool arcade;

inline lv_res_t toggleMode(lv_obj_t * btn)
{
    if (arcade) {
    dt.teleMove = [=]{dt.tankDrive(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));};
    } else {
    dt.teleMove = [=]{dt.arcadeDrive(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X));};
    }
    arcade = !arcade;

    btnSetToggled(btn, arcade);

    return LV_RES_OK;
}

...

void initialize() {
    lv_obj_t* driveBtn = createBtn(lv_scr_act(), Display::DISP_CENTER, 150, 20, "Switch drive types", LV_COLOR_MAKE(62, 180, 137), LV_COLOR_MAKE(153, 50, 204));
    lv_btn_set_action(driveBtn, LV_BTN_ACTION_CLICK, toggleMode);

    ...

    dt.teleMove = [=]{dt.tankDrive(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));};
}
```

## tankDrive

```cpp
inline void tankDrive(signed char leftY, signed char rightY){
    left_g.move(abs(leftY)<threshold ? 0 :leftY);
    right_g.move(abs(rightY)<threshold ? 0 :rightY);
}
```

Self explanatory code, the left side moves with the leftY and vice versa. (Most drivers prefer this so set it as default)

## arcadeDrive

```cpp
inline void arcadeDrive(signed char leftY, signed char rightX) {
    leftY = abs(leftY)<threshold ? 0 : leftY;
    rightX = abs(rightX)<threshold ? 0 : rightX;
    left_g.move(leftY + rightX);
    right_g.move(leftY - rightX);
}
```

You move forward and backward with the leftY and you turn with the rightX (Most programmers prefer this)
