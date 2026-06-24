#include "rk/video.h"

#include <SDL3/SDL.h>
#include <stdlib.h>

struct rk_video_instance {
	SDL_Window *native_window;
	SDL_Renderer *native_renderer;
	int window_width;
	int window_height;
};

struct rk_video_instance *rk_video_alloc(void)
{
	struct rk_video_instance *instance = malloc(sizeof(*instance));
	if (!instance) {
		return NULL;
	}

	return instance;
}

int rk_video_init(struct rk_video_instance *inst, const char *title, int width,
		  int height)
{
	int ret = 0;
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		return -1;
	}

	inst->native_window = SDL_CreateWindow(title, width, height, 0);
	if (!inst->native_window) {
		ret = -2;
		goto failure;
	}
	
	inst->native_renderer = SDL_CreateRenderer(inst->native_window, NULL);
	if (!inst->native_renderer) {
		ret = -3;
		goto failure;
	}

	return 0;

failure:
	if (inst->native_renderer) {
		SDL_DestroyRenderer(inst->native_renderer);
	}
	
	if (inst->native_window) {
		SDL_DestroyWindow(inst->native_window);
	}
	
	SDL_Quit();

	return ret;
}

void rk_video_ctx_clear(struct rk_video_instance *inst)
{
	SDL_RenderClear(inst->native_renderer);
}

void rk_video_ctx_swap(struct rk_video_instance *inst)
{
	SDL_RenderPresent(inst->native_renderer);
}

void rk_video_ctx_use_color(struct rk_video_instance *inst, float r, float g,
			    float b, float a)
{
	SDL_SetRenderDrawColorFloat(inst->native_renderer, r, g, b, a);
}

void rk_video_ctx_add_line(struct rk_video_instance *inst, float start_x,
			   float start_y, float end_x, float end_y)
{
	SDL_RenderLine(inst->native_renderer, start_x, start_y, end_x, end_y);
}

void rk_video_free(struct rk_video_instance *inst)
{
	if (!inst) {
		return;
	}

	if (inst->native_renderer) {
		SDL_DestroyRenderer(inst->native_renderer);
	}

	if (inst->native_window) {
		SDL_DestroyWindow(inst->native_window);
	}

	SDL_Quit();

	free(inst);
}
