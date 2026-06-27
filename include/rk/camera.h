#ifndef RK_CAMERA_H
#define RK_CAMERA_H

/**
 * struct rk_camera - Camera data
 *
 * This structure need for organize camera
 * data in one place
*/
struct rk_camera {
	float x; /* X position */
	float y; /* Y position */
	float a; /* Rotate angle */
	float speed; /* Movement speed */
};

/**
 * rk_camera_alloc - Allocates memory for instance
 * 
 * This function allocates memory for instance
 * Returns allocates memory address
*/
struct rk_camera *rk_camera_alloc(void);

/**
 * rk_camera_init - Initialize camera instance
 * @inst: Instance pointer
 * @pos_x: Position x
 * @pos_y: Position y
 * @angle: Angle in radians
 * @speed: Movement speed
 *
 * This function initialize instance
 * Always success if @inst available
*/
void rk_camera_init(struct rk_camera *inst, float pos_x, float pos_y,
		   float angle, float speed);

/**
 * rk_camera_move - Set new camera position
 * @inst: Instance pointer
 * @x: New x position
 * @y: New y position
 * 
 * This function move camera for instance
*/
void rk_camera_move_at(struct rk_camera *inst, float x, float y);

/**
 * rk_camera_move - Move camera
 * @inst: Instance pointer
 * @x_rel: X relative
 * @y_rel: Y relative
 * 
 * This function relative move camera
*/
void rk_camera_move(struct rk_camera *inst, float x_rel, float y_rel);

/**
 * rk_camera_rotate - Rotate camera
 * @inst: Instance pointer
 * @angle: Rotate angle
 *
 * This function rototate camera
 * camera->a += @angle
*/
inline void rk_camera_rotate(struct rk_camera *inst, float angle) {
	inst->a += angle;
}

/**
 * rk_camera_free - Free allocated memory
 * @inst: Instance pointer
 * 
 * This function deallocates memory for instance
*/
void rk_camera_free(struct rk_camera *inst);

#endif /* RK_CAMERA_H */
