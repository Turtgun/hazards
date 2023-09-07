# Display.hpp

## Namespaces
So namespaces in c++ are just holders of functions, variables, and types
Display.hpp uses the Display namespace to hold all of its tools

To use the namespace in a different file you must first include the file
```cpp
#include "/location/to/Display.hpp"
```
Then, as an example:
```cpp
Display::btnSetToggled(btn, true);
```
Is a way to use the Display namespace in your code, however a different way and in my personal opinion easier way to do this is by using the
```cpp
using namespace Display;
.
.
.
btnSetToggled(btn, true);
```

# The actual objects here

## disp_obj_align

 ```cpp
 enum disp_obj_align {
    DISP_LEFT,
    DISP_CENTER,
    DISP_RIGHT
};
```
This is an enum which is just like a state of variable that is declared here so when you use something like
```cpp
disp_obj_align align = DISP_LEFT;
```
This will be used to set the alignment for creating new labels and new buttons. I made it so that when you use the createLabel and createButton functions you can only decide on where the object is aligned on the screen. Pretty much everytime you use them you place the object below the previous object and you can set its alignment in the align parameter.

## lv_img_disp()
```cpp
static inline lv_obj_t* lv_img_disp(const lv_img_dsc_t* cArr, lv_align_t align = LV_ALIGN_IN_TOP_LEFT, short x = 0, short y = 0)
```
This function is used to put an image

### cArr
This is the C Array of the picture