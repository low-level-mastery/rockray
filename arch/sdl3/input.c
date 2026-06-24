#include "rk/input.h"

#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdio.h>

struct rk_input_instance {
	bool *keys_state;
};

struct rk_input_instance *rk_input_alloc(void)
{
	struct rk_input_instance *instance = calloc(1, sizeof(*instance));
	if (!instance) {
		return NULL;
	}

	return instance;
}

void rk_input_free(struct rk_input_instance *inst)
{
	if (!inst) {
		return;
	}

	free(inst);
}

void rk_input_handle(struct rk_input_instance *inst)
{
	SDL_Event e;
	while (SDL_PollEvent(&e));

	inst->keys_state = (bool *)SDL_GetKeyboardState(NULL);
}

void rk_input_get_mouse(float *x, float *y)
{
	SDL_GetMouseState(x, y);
}

bool rk_input_is_mouse_pressed(enum rk_input_mouse_button btn)
{
	if (btn == RK_INPUT_LEFT_BUTTON) {
		return (SDL_GetMouseState(NULL, NULL) &
			SDL_BUTTON_MASK(SDL_BUTTON_LEFT));
	} else {
		return (SDL_GetMouseState(NULL, NULL) &
			SDL_BUTTON_MASK(SDL_BUTTON_RIGHT));
	}
}

bool rk_input_is_key_pressed(struct rk_input_instance *inst, SDL_Scancode key)
{
	return inst->keys_state[key];
}

