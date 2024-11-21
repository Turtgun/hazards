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

static inline lv_obj_t* createLabel(lv_obj_t* parent, lv_align_t align, lv_coord_t yPos, const char* text, lv_color_t textColor = lv_color_white())
{
    // Create label
    lv_obj_t* label = lv_label_create(parent);
    lv_label_set_text(label, text);

    // Align label based on provided alignment
    lv_obj_set_pos(label, (align + 1) * 50, yPos);

    // Initialize and configure label style
    static lv_style_t labelStyle;
    lv_style_init(&labelStyle);
    lv_style_set_text_color(&labelStyle, textColor);

    // Apply style to label
    lv_obj_add_style(label, &labelStyle, LV_PART_MAIN | LV_STATE_DEFAULT);

    return label;
}

static inline lv_obj_t* createBtn(lv_obj_t* parent, lv_align_t align, lv_coord_t yPos, lv_coord_t width, lv_coord_t height, const char* title,
                                  lv_color_t rel, lv_color_t tglRel, lv_color_t textColor = lv_color_white())
{
    lv_obj_t* btn = lv_btn_create(parent);
    lv_obj_set_pos(btn, (align + 1) * 50, yPos);
    lv_obj_set_size(btn, width, height);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, title);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

    // Initialize styles
    static lv_style_t btnStyleDefault, btnStylePressed, btnStyleTglRel, btnStyleTglPr;
    lv_style_init(&btnStyleDefault);
    lv_style_init(&btnStylePressed);
    lv_style_init(&btnStyleTglRel);
    lv_style_init(&btnStyleTglPr);

    // Configure styles
    lv_style_set_bg_color(&btnStyleDefault, rel);
    lv_style_set_bg_color(&btnStylePressed, lv_color_darken(rel, 50));
    lv_style_set_bg_color(&btnStyleTglRel, tglRel);
    lv_style_set_bg_color(&btnStyleTglPr, lv_color_darken(tglRel, 50));

    lv_style_set_text_color(&btnStyleDefault, textColor);
    lv_style_set_text_color(&btnStylePressed, textColor);
    lv_style_set_text_color(&btnStyleTglRel, textColor);
    lv_style_set_text_color(&btnStyleTglPr, textColor);

    // Apply styles
    lv_obj_add_style(btn, &btnStyleDefault, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(btn, &btnStylePressed, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_add_style(btn, &btnStyleTglRel, LV_PART_MAIN | LV_STATE_CHECKED);
    lv_obj_add_style(btn, &btnStyleTglPr, LV_PART_MAIN | (LV_STATE_CHECKED | LV_STATE_PRESSED));

    lv_obj_add_flag(btn, LV_OBJ_FLAG_CHECKABLE);

    return btn;
}

    static inline void btnSetToggled(lv_obj_t* btn, bool toggled)
    {
        if(toggled != (lv_obj_get_state(btn) >= 2)) lv_obj_add_state(btn, LV_STATE_CHECKED);
    }
};
