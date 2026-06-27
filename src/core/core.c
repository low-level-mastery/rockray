#include "rk/core.h"
#include "rk/logger.h"
#include "rk/video.h"
#include "rk/input.h"
#include "rk/camera.h"

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* TODO: Workaround */
#define CAMERA_SIZE 20

struct rk_engine_instance {
	struct rk_video_instance *video;
	struct rk_input_instance *input;
	struct rk_camera *camera;

	int window_width;
	int window_height;

	bool is_running;
};

struct rk_engine_instance *rk_engine_alloc(void)
{
	struct rk_engine_instance *instance;
	instance = calloc(1, sizeof(*instance));

	if (!instance)
		return NULL;
	
	return instance;
}

int rk_engine_init(struct rk_engine_instance *engine)
{
	int ret = 0;
	engine->video = rk_video_alloc();
	if (!engine->video) {
		ret = -1;
		pr_err("Video module allocates: Failed");
		goto failure;
	}
	
	pr_info("Video module allocates: Success");

	engine->window_width = 900;
	engine->window_height = 600;

	if (rk_video_init(engine->video, "RockRay", engine->window_width,
			  engine->window_height) < 0) {
		ret = -2;
		pr_err("Video module initialize: Failed");
		goto failure;
	}

	pr_info("Video module initialize: Success");

	engine->input = rk_input_alloc();
	if (!engine->input) {
		ret = -3;
		pr_err("Input module allocates: Failed");
		goto failure;
	}

	pr_info("Input module allocates: Sucess");

	engine->camera = rk_camera_alloc();
	if (!engine->camera) {
		ret = -4;
		pr_err("Camera allocates: Failed");
		goto failure;
	}

	pr_info("Camera allocates: Success");

	/* Setup camera */
	rk_camera_init(
		engine->camera, engine->window_width / 2 - CAMERA_SIZE / 2,
		engine->window_height / 2 - CAMERA_SIZE / 2, 0.0f, 0.3f);
	
	pr_info("Camera is setup");
	
	engine->is_running = true;

	return true;

failure:
	/* main.c call rk_engine_free() */
	return ret;
}

static void controller_update(struct rk_engine_instance *engine)
{
	/* Move camera by HJKL */
	if (rk_input_is_key_pressed(engine->input, SDL_SCANCODE_L)) {
		float dx = -sinf(engine->camera->a) / 3.0f;
		float dy = cosf(engine->camera->a) / 3.0f;
		rk_camera_move(engine->camera, dx, dy);
	}

	if (rk_input_is_key_pressed(engine->input, SDL_SCANCODE_K)) {
		float dx = cosf(engine->camera->a) / 3.0f;
		float dy = sinf(engine->camera->a) / 3.0f;
		rk_camera_move(engine->camera, dx, dy);
	}

	if (rk_input_is_key_pressed(engine->input, SDL_SCANCODE_J)) {
		float dx = -cosf(engine->camera->a) / 3.0f;
		float dy = -sinf(engine->camera->a) / 3.0f;
		rk_camera_move(engine->camera, dx, dy);
	}

	if (rk_input_is_key_pressed(engine->input, SDL_SCANCODE_H)) {
		float dx = sinf(engine->camera->a) / 3.0f;
		float dy = -cosf(engine->camera->a) / 3.0f;
		rk_camera_move(engine->camera, dx, dy);
	}

	if (rk_input_is_key_pressed(engine->input, SDL_SCANCODE_E)) {
		rk_camera_rotate(engine->camera, -0.001f);
	}

	if (rk_input_is_key_pressed(engine->input, SDL_SCANCODE_R)) {
		rk_camera_rotate(engine->camera,  0.001f);
	}

}

void rk_engine_run(struct rk_engine_instance *engine)
{
	pr_info("Starting mainloop...");
	while (engine->is_running) {
		/* Handle event's part */
		rk_input_handle(engine->input);
		
		if (rk_input_is_key_pressed(engine->input,
					    SDL_SCANCODE_ESCAPE)) {
			engine->is_running = false;
		}

		controller_update(engine);

		/* Render part */
		rk_video_ctx_use_color(engine->video, 1.0f, 1.0f, 1.0f, 1.0f);
		rk_video_ctx_clear(engine->video);
		
		/* 2D Map */
		rk_video_ctx_use_color(engine->video, 1.0f, 0.0f, 0.0f, 1.0f);
		rk_video_ctx_rectangle(engine->video, engine->camera->x,
				       engine->camera->y, CAMERA_SIZE,
				       CAMERA_SIZE);
	
		float end_x =
			500.0f * cosf(engine->camera->a) + engine->camera->x;
		float end_y =
			500.0f * sinf(engine->camera->a) + engine->camera->y;

		rk_video_ctx_use_color(engine->video, 0.8f, 0.8f, 0.4f, 1.0f);
		rk_video_ctx_line(engine->video, engine->camera->x + CAMERA_SIZE / 2,
				  engine->camera->y + CAMERA_SIZE / 2, end_x +
				  CAMERA_SIZE / 2, end_y + CAMERA_SIZE / 2);
	
		rk_video_ctx_swap(engine->video);
	}
}

void rk_engine_free(struct rk_engine_instance *engine)
{
	if (!engine) {
		return;
	}

	if (engine->camera) {
		rk_camera_free(engine->camera);
		engine->camera = NULL;
		pr_info("Camera is free");
	}
	
	if (engine->input) {
		rk_input_free(engine->input);
		engine->input = NULL;
		
		pr_info("Input module free: Success");
	}



	if (engine->video) {
		rk_video_free(engine->video);
		engine->video = NULL;

		pr_info("Video module free: Success");
	}
	
	free(engine);

	pr_info("All memory is free");

}
