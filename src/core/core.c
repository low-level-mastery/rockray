#include "rk/core.h"
#include "rk/logger.h"
#include "rk/video.h"
#include "rk/input.h"

#include <stdlib.h>
#include <stdbool.h>

struct rk_engine_instance {
	struct rk_video_instance *video;
	struct rk_input_instance *input;

	float camera_x;
	float camera_y;

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

	engine->camera_x = engine->window_width / 2;
	engine->camera_y = engine->window_height / 2;

	engine->is_running = true;

	return true;

failure:
	/* main.c call rk_engine_free() */
	return ret;
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

		/* Render part */
		rk_video_ctx_use_color(engine->video, 1.0f, 1.0f, 1.0f, 1.0f);
		rk_video_ctx_clear(engine->video);
		
		rk_video_ctx_use_color(engine->video, 1.0f, 0.0f, 0.0f, 1.0f);
		rk_video_ctx_rectangle(engine->video, 100.0f, 100.0f, 50.0f, 50.0f);
		
		rk_video_ctx_swap(engine->video);
	}
}

void rk_engine_free(struct rk_engine_instance *engine)
{
	if (!engine) {
		return;
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
