#ifndef RK_CAMERA_H
#define RK_CAMERA_H

struct rk_camera_instance;

/**
 * rk_camera_alloc - Allocates memory for instance
 * 
 * This function allocates memory for instance
 * Returns allocates memory address
*/
struct rk_camera_instance *rk_camera_alloc(void);

/**
 * rk_camera_init - Initialize camera instance
 * @inst: Instance pointer
 * @pos_x: Position x
 * @pos_y: Position y
 * @angle: Angle in radians
 * @FOV: Camera FOV
 * @near: Camera near
 * @far: Camera far
 * @rays: Num of rays
 *
 * This function initialize instance
 * Return 0 if success, else negative error code
*/
int rk_camera_init(struct rk_camera_instance *inst, float pos_x, float pos_y,
		   float angle, float FOV, float near, float far, size_t rays);

/**
 * rk_camera_mode - Movement for camera
 * @inst: Instance pointer
 * @x: New x position
 * @y: New y position
 * 
 * This function move camera for instance
*/
void rk_camera_move(struct rk_camera_instance *instance, float x, float y);

/**
 * rk_camera_free - Free allocated memory
 * @inst: Instance pointer
 * 
 * This function deallocates memory for instance
*/
void rk_camera_free(struct rk_camera_instance *inst);

#endif /* RK_CAMERA_H */
