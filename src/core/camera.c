#include "rk/camera.h"

#include <stdlib.h>

struct rk_camera *rk_camera_alloc(void)
{
	struct rk_camera *camera = calloc(1, sizeof(*camera));
	if (!camera) {
		return NULL;
	}

	return camera;
}

void rk_camera_init(struct rk_camera *inst, float pos_x, float pos_y,
		    float angle, float speed)
{
	inst->x = pos_x;
	inst->y = pos_y;
	inst->a = angle;
	inst->speed = speed;
}

void rk_camera_move_at(struct rk_camera *inst, float x, float y)
{
	inst->x = x;
	inst->y = y;
}

void rk_camera_move(struct rk_camera *inst, float x_rel, float y_rel)
{
	inst->x += x_rel;
	inst->y += y_rel;
}

void rk_camera_free(struct rk_camera *inst)
{
	if (!inst) {
		return;
	}

	free(inst);
}
