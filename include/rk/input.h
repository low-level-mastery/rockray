#ifndef RK_INPUT_H
#define RK_INPUT_H

#include <stdbool.h>

struct rk_input_instance;

enum rk_input_mouse_button {
	RK_INPUT_LEFT_BUTTON,
	RK_INPUT_RIGHT_BUTTON
};

/**
 * rk_input_alloc - Allocates memory for instance
 *
 * This function allocates memory for instance
 * Returns allocates memory
*/
struct rk_input_instance *rk_input_alloc(void);

/**
 * rk_input_handle - Update event list
 * @inst: Instance pointer
 * 
 * This function conducts a survey of states
 * and save it to rk_input_instance.keyboard_state
 *
 * Also this function get cursor pos and save it
 * to rk_input_instance.cursor.x/y
*/
void rk_input_handle(struct rk_input_instance *inst);

/**
 * rk_input_get_mouse - Get mouse position in window
 * @inst: Instance pointer
 * 
 * This function returns mouse position from @inst
*/
float *rk_input_get_mouse(struct rk_input_instance *inst);

/**
 * rk_input_is_mouse_pressed - Check mouse button state
 * @inst: Instance pointer
 * @btn: Button side
 * 
 * This function check mouse button state
 * Return true if @btn side is pressed, else false
*/
bool rk_input_is_mouse_pressed(struct rk_input_instance *inst,
			       enum rk_input_mouse_button btn);

/**
 * rk_input_is_key_pressed - Check is key pressed
 * @inst: Instance pointer
 * @key: Key for check state
 * 
 * This function check key state
 * Returns key state, true - pressed, else false
*/
bool rk_input_is_key_pressed(struct rk_input_instance *inst, char key);

#endif /* RK_INPUT_H */
