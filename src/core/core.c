#include "rk/map.h"
#include "rk/video.h"
#include "rk/input.h"
#include "rk/video.h"
#include "rk/logger.h"
#include "rk/camera.h"

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

/* TODO: Workaround */
#define CAMERA_SIZE 20

struct rk_engine_instance {
	struct rk_map map;
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
	
	engine->map.field_size = 20.0f;
	engine->map.width = (int)(engine->window_width / engine->map.field_size);
	engine->map.height = (int)(engine->window_height / engine->map.field_size);

	size_t total_cells = engine->map.width * engine->map.height;
	
	engine->map.text_map = malloc(engine->map.width * engine->map.height /
				     (engine->map.field_size * engine->map.field_size));

	pr_info("Map initialize: %d x %d cells. Success", engine->map.width, engine->map.height);

	engine->map.text_map = calloc(total_cells, sizeof(char));

	if (!engine->map.text_map) {
		ret = -5;
		pr_err("Map allocates: Failed");
		goto failure;
	}
	
	for (int y = 0; y < engine->map.height; ++y) {
                for (int x = 0; x < engine->map.width; ++x) {
                        if (y == 0 || y == engine->map.height - 1 || 
                            x == 0 || x == engine->map.width - 1) {
                                int index = engine->map.width * y + x;
                                engine->map.text_map[index] = '#';
                        }
                }
        }

	pr_info("Map allocates: Success");
	
	engine->is_running = true;

	return 0;

failure:
	/* main.c call rk_engine_free() */
	return ret;
}

static void controller_update(struct rk_engine_instance *engine)
{
	float dx = 0.0f;
	float dy = 0.0f;

	/* Move camera by HJKL */
	if (rk_input_is_key_pressed(engine->input, SDL_SCANCODE_L)) {
		dx = -sinf(engine->camera->a) / 5.0f;
		dy = cosf(engine->camera->a) / 5.0f;
	}

	if (rk_input_is_key_pressed(engine->input, SDL_SCANCODE_K)) {
		dx = cosf(engine->camera->a) / 5.0f;
		dy = sinf(engine->camera->a) / 5.0f;
	}

	if (rk_input_is_key_pressed(engine->input, SDL_SCANCODE_J)) {
		dx = -cosf(engine->camera->a) / 5.0f;
		dy = -sinf(engine->camera->a) / 5.0f;
	}

	if (rk_input_is_key_pressed(engine->input, SDL_SCANCODE_H)) {
		dx = sinf(engine->camera->a) / 5.0f;
		dy = -cosf(engine->camera->a) / 5.0f;
	}

	rk_camera_move(engine->camera, dx, dy);

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
	
		rk_video_ctx_use_color(engine->video, 0.0f, 0.0f, 0.0f, 1.0f);
		rk_map_render_2d(&engine->map, engine->video);
	
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

	if (engine->map.text_map) {
		free(engine->map.text_map);
		engine->map.text_map = NULL;
		pr_info("Text map is free");
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
