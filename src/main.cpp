#include "main.h"

#include "Display.hpp"

#include "liblvgl/core/lv_event.h"
#include "systems/DriveTrain.hpp"

#include <cstdint>

using namespace pros;
using namespace Display;

Controller master(E_CONTROLLER_MASTER);

DriveTrain dt = DriveTrain();
LV_IMG_DECLARE(normal);
lv_obj_t* bgImg = lv_img_disp(&normal);

char lY,rY,rX = 0;

bool arcade;
bool skills_auton;
bool right_auton;

static void event_cb(lv_event_t* e) {
	lv_obj_t* btn = lv_event_get_target(e);
	int id = static_cast<int>(reinterpret_cast<intptr_t>(lv_event_get_user_data(e)));
	switch (id) {
		case 0:
			arcade = !arcade;
			if (arcade) {
				dt.teleMove = [=]{dt.arcadeDrive(lY,rX);};
				lv_label_set_text(lv_obj_get_child(btn, 0), "Arcade Drive");
				} else {
				dt.teleMove = [=]{dt.tankDrive(lY,rY);};
				lv_label_set_text(lv_obj_get_child(btn, 0), "Tank Drive");
			}
			btnSetToggled(btn, arcade);
			break;
		case 1:
			skills_auton = !skills_auton;
			if (skills_auton) {
				lv_label_set_text(lv_obj_get_child(btn, 0), "Skills Auton");
			} else {
				lv_label_set_text(lv_obj_get_child(btn, 0), "Match Auton");
			}
			btnSetToggled(btn, skills_auton);
			break;
		case 2:
			right_auton = !right_auton;
			if (right_auton) {
				lv_label_set_text(lv_obj_get_child(btn, 0), "Right Auton");
			} else {
				lv_label_set_text(lv_obj_get_child(btn, 0), "Left Auton");
			}
			btnSetToggled(btn, right_auton);
			break;
		default:
			break;	
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	//lv_obj_t* odometryInfo = createLabel(lv_scr_act(), DISP_CENTER, 300, 40, "Odom Info");
	//Odometry odom = Odometry(&dt, &odometryInfo);
/*
	dt.teleMove = [=]{dt.tankDrive(lY,rY);};
	lv_obj_t* driveBtn = createBtn(lv_scr_act(), DISP_CENTER, 300, 20, "Tank Drive", LV_COLOR_MAKE(62, 180, 137), LV_COLOR_MAKE(153, 50, 204));
	lv_obj_add_event_cb(driveBtn, event_cb, LV_EVENT_CLICKED, reinterpret_cast<void*>(static_cast<intptr_t>(0)));

	lv_obj_t* autonTypeBtn = createBtn(lv_scr_act(), DISP_CENTER, 300, 20, "Match Auton", LV_COLOR_MAKE(62, 180, 137), LV_COLOR_MAKE(153, 50, 204));
	lv_obj_add_event_cb(autonTypeBtn, event_cb, LV_EVENT_CLICKED, reinterpret_cast<void*>(static_cast<intptr_t>(1)));

	lv_obj_t* autonSideBtn = createBtn(lv_scr_act(), Display::DISP_CENTER, 300, 20, "Match Left", LV_COLOR_MAKE(62, 180, 137), LV_COLOR_MAKE(153, 50, 204));
	lv_obj_add_event_cb(autonSideBtn, event_cb, LV_EVENT_CLICKED, reinterpret_cast<void*>(static_cast<intptr_t>(2)));

	lv_obj_t* pickleT = createLabel(lv_scr_act(), DISP_CENTER, 300, 100,
		"Current pickle high scores (5 min)\nEsteban: 11\nJayleen: 10\nJI: 9");
*/
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void kickturn(bool flip) {
	dt.arcadeDrive(127, ((flip)?-1:1)*-65);
	delay(500);
	dt.arcadeDrive(80, ((flip)?-1:1)*70);
	delay(500);

	int time = millis();

	while(time>=millis()-250) {
		dt.arcadeDrive(0, ((flip)?-1:1)*(millis()-time-127)/1.96850393701 );
		delay(20);
	}

	dt.arcadeDrive(-127, -127);
	delay(300);
	dt.arcadeDrive(127, 60);
	delay(500);
	dt.arcadeDrive(127, 0);
	delay(200);
	dt.arcadeDrive(-127, 0);
	delay(400);
	dt.arcadeDrive(-10, ((flip)?-1:1)*127);
	delay(150);
	dt.arcadeDrive(-60, 60);
	delay(150);
}

void debugWait() {
	dt.arcadeDrive(0, 0);
	delay(1000); // change to 500 when running fr
}

void autonomous() {

}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	bool prcsM = false;
	int prcsET, fpLET, fpRET = 0;
	while (true) {
		// Set precision mode (dont repeat until half a second)
		if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN) && (millis() - prcsET > 500)) {prcsM = !prcsM; prcsET = millis();}

		// Toggle flaps (dont repeat until half a second) 
		/* 
		if (master.get_digital(E_CONTROLLER_DIGITAL_UP) && (millis() - fpLET > 500)) {fp.toggleL(); fpLET = millis();}
		if (master.get_digital(E_CONTROLLER_DIGITAL_X) && (millis() - fpRET > 500)) {fp.toggleR(); fpRET = millis();} 
		*/

		{ // Set input for the drivetrain's teleMove according to precision mode.
			lY = (prcsM) ? master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)/2 : master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
			rY = (prcsM) ? master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)/2 : master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
			rX = (prcsM) ? master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)/2 : master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
		}

		dt.teleMove();

		// Automatically move the catapult down unless it's hitting the button, or continue moving down if B is pressed
		//cata.move(-127, !master.get_digital(E_CONTROLLER_DIGITAL_B));
/* 		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {cata.move(-127);} 
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {cata.move(127);}
		else {cata.move(0);}
		
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {ele.move(-127);}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {ele.move(127);}
		else {ele.move(0);} 
*/

		delay(20);
	}
}