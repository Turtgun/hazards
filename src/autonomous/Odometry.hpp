#pragma once

#include "../systems/DriveTrain.hpp"
#include "../../include/liblvgl/lvgl.h"
#include "Vector2.hpp"
#include <string>

using namespace Constants;
using namespace pros;

#define ODOM_DEBUG

class Odometry {
	private:
		DriveTrain* dt;
		lv_obj_t** odometryInfo;
		
		double newLeft, newRight;
		double phi;
		double dLeft, dRight, rCenter;
		double hCos, hSin, pCos, pSin;
		double* vel = new double[2];

	public:
		Vector2 pos = {0,0};
		double heading = pi/2;
		double leftEncoder, rightEncoder;

		void odomTick(){
			while(true) {
			newLeft = (dt->fl_mtr.get_position() + dt->bl_mtr.get_position()) / 2 * inchesPerTick;
			newRight = (dt->fr_mtr.get_position() + dt->br_mtr.get_position()) / 2 * inchesPerTick;
			
			dLeft = newLeft - leftEncoder;
			dRight = newRight - rightEncoder;

			phi = (dRight-dLeft)/trackwidth;

			if (phi == 0) {
				pos.x += dLeft*cos(heading);
				pos.y += dLeft*sin(heading);
			} else {
				rCenter = ((dLeft+dRight)/2)/phi;

				hCos = cos(heading); hSin = sin(heading);
				pCos = cos(phi); pSin = sin(phi);

				pos.x += (rCenter)*(-hSin + pSin*hCos + hSin*pCos);
				pos.y += (rCenter)*(hCos - pCos*hCos + hSin*pSin);
			}
			heading+=phi;

			heading = headingRestrict(heading);

			//std::cout << pos.x << " " << pos.y << " " << heading*radToDeg << " " << phi*radToDeg << std::endl;

			leftEncoder = newLeft;
			rightEncoder = newRight;

#ifdef ODOM_DEBUG
			lv_label_set_text(*odometryInfo, ("Position: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ") \nTheta: " + std::to_string(heading*radToDeg)).c_str());
#endif
			delay(10);
			}
		};

        Odometry(DriveTrain* dt, lv_obj_t** odometryInfo):dt(dt), odometryInfo(odometryInfo){}
		Task odomTask{std::bind(&Odometry::odomTick, this)};

};