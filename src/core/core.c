#include "rk/core.h"
#include "rk/logger.h"
#include "rk/video.h"
#include "rk/input.h"

#include <stdlib.h>
#include <stdbool.h>

struct rk_engine_instance {
	struct rk_video_instance *video;
	struct rk_input_instance *input;
	
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
		goto failure;
	}

	if (rk_video_init(engine->video, "RockRay", 900, 600) < 0) {
		ret = -2;
		goto failure;
	}

	engine->input = rk_input_alloc();
	if (!engine->input) {
		ret = -3;
		goto failure;
	}
	
	engine->is_running = true;

	return true;

failure:
	if (engine->input) {
		rk_input_free(engine->input);
	}

	if (engine->video) {
		rk_video_free(engine->video);
	}

	return ret;
}

void rk_engine_run(struct rk_engine_instance *engine)
{
	while (engine->is_running) {
		/* Handle event's part */
		rk_input_handle(engine->input);
		
		if (rk_input_is_key_pressed(engine->input, SDL_SCANCODE_ESCAPE)) {
			engine->is_running = false;
		}

		/* Render part */
		rk_video_ctx_use_color(engine->video, 1.0f, 1.0f, 1.0f, 1.0f);
		rk_video_ctx_clear(engine->video);
		
		rk_video_ctx_use_color(engine->video, 1.0f, 0.0f, 0.0f, 1.0f);
		rk_video_ctx_add_line(engine->video, 0.0f, 0.0f, 500.0f, 500.0f);
		
		rk_video_ctx_swap(engine->video);
	}
}

void rk_engine_free(struct rk_engine_instance *engine)
{
	if (!engine) {
		return;
	}
	
	rk_input_free(engine->input);
	rk_video_free(engine->video);

	free(engine);
}
