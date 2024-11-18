#pragma once

#include "../include/liblvgl/lvgl.h"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/misc/lv_area.h"
#include "liblvgl/misc/lv_color.h"
#include "liblvgl/misc/lv_style.h"


namespace Display {
    enum disp_obj_align {
        DISP_LEFT,
        DISP_CENTER,
        DISP_RIGHT
    };

    static inline lv_obj_t* lv_img_disp(const lv_img_dsc_t* cArr, lv_align_t align = LV_ALIGN_TOP_LEFT, short x = 0, short y = 0)
    {
        lv_obj_t* img = lv_img_create(lv_scr_act());
        lv_img_set_src(img, cArr);
        lv_obj_align(img, align, x, y);

        return img;
    }

    static inline lv_obj_t* createLabel(lv_obj_t* parent, disp_obj_align align, lv_coord_t width, lv_coord_t height, const char* title,
                    lv_color_t bgCol = lv_color_black(), lv_opa_t opa = LV_OPA_0, lv_color_t textColor = lv_color_white())
    {
        lv_obj_t* label =  lv_label_create(parent);
        lv_obj_set_pos(label, lv_obj_get_x(lv_obj_get_child(parent, -1)) + 40, (align+1)*100);
        lv_obj_set_size(label, width, height);
        lv_label_set_text(label,title);
        lv_obj_set_align(label, LV_ALIGN_CENTER);

        static lv_style_t labelSty;
        lv_style_init(&labelSty);

        lv_style_set_bg_color(&labelSty, bgCol);
        lv_style_set_opa(&labelSty, opa);
        lv_style_set_text_color(&labelSty, textColor);

        lv_obj_add_style(label, &labelSty, 0);

        return label;
    }

    static inline lv_obj_t* createBtn(lv_obj_t* parent, disp_obj_align align, lv_coord_t width, lv_coord_t height, const char* title, 
                    lv_color_t rel, lv_color_t tglRel, lv_color_t textColor = lv_color_white())
    {
        lv_obj_t* btn = lv_btn_create(parent);
        lv_obj_set_pos(btn, lv_obj_get_x(lv_obj_get_child(parent, -1)) + 40, (align+1)*100);
        lv_obj_set_size(btn, width, height);

        lv_obj_t* label = lv_label_create(btn);
        lv_label_set_text(label, title);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

        lv_style_t* btnStyle = new lv_style_t[4];

        lv_color_t pr = LV_COLOR_MAKE((uint8_t)(rel.ch.red+10), (uint8_t)(rel.ch.green+10), (uint8_t)(rel.ch.blue+10));
        lv_color_t tglPr = LV_COLOR_MAKE((uint8_t)(tglRel.ch.red+10), (uint8_t)(tglRel.ch.green+10), (uint8_t)(tglRel.ch.blue+10));

        lv_style_set_bg_color(&btnStyle[0], rel);
        lv_style_set_bg_grad_color(&btnStyle[0], rel);
        lv_style_set_text_color(&btnStyle[0], textColor);

        lv_style_set_bg_color(&btnStyle[1], pr);
        lv_style_set_bg_grad_color(&btnStyle[1], pr);
        lv_style_set_text_color(&btnStyle[1], textColor);


        lv_style_set_bg_color(&btnStyle[2], tglRel);
        lv_style_set_bg_grad_color(&btnStyle[2], tglRel);
        lv_style_set_text_color(&btnStyle[2], textColor);


        lv_style_set_bg_color(&btnStyle[3], tglPr);
        lv_style_set_bg_grad_color(&btnStyle[3], tglPr);
        lv_style_set_text_color(&btnStyle[3], textColor);

        lv_obj_add_style(btn, &btnStyle[0], 0);
        lv_obj_add_style(btn, &btnStyle[1], 1);
        lv_obj_add_style(btn, &btnStyle[2], 2);
        lv_obj_add_style(btn, &btnStyle[3], 3);


        lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);

        return btn;
    }
    static inline void btnSetToggled(lv_obj_t* btn, bool toggled)
    {
        if(toggled != (lv_obj_get_state(btn) >= 2)) lv_obj_add_state(btn, LV_STATE_CHECKED);
    }
};
