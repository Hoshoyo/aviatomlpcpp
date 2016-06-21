#include "input.h"

namespace ho {

bool Input::Keys[NUM_KEYS] = {};
glm::vec2 Input::mouse_pos;
bool Input::left_mouse_down = false;
bool Input::right_mouse_down = false;
bool Input::left_click = false;

}