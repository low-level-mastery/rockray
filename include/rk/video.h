#ifndef RK_VIDEO_H
#define RK_VIDEO_H

struct rk_video_instance;

/**
 * rk_video_alloc - Allocates memory for instance
 * 
 * This function allocates memory by system allocator
 * for instance
*/
struct rk_video_instance *rk_video_alloc(void);

/**
 * rk_video_init - Initialize instance
 * @inst: Instance pointer
 * @title: Window title
 * @width: Window width
 * @height: Window height
 * 
 * This function initialize video module
 * Return 0 if success or negative error code if fail
*/
int rk_video_init(struct rk_video_instance *inst, const char *title, int width,
		  int height);

/**
 * rk_video_ctx_clear - Clear window context
 * @inst: Instance pointer
 *
 * This function clear window context by current active color
*/
void rk_video_ctx_clear(struct rk_video_instance *inst);

/**
 * rk_video_ctx_swap - Swap context buffers
 * @inst: Instance pointer
 *
 * This function swap context buffers and present changes
*/
void rk_video_ctx_swap(struct rk_video_instance *inst);

/**
 * rk_video_ctx_use_color - Change draw color
 * @inst: Instance pointer
 * @r: Red component in color
 * @g: Green component in color
 * @b: Blue component in color
 * @a: Alpha component
 * 
 * This function set color for draw
 * 
 * Important!
 * Color sets in normalized type (0.0f - 1.0f)
*/
void rk_video_ctx_use_color(struct rk_video_instance *inst, float r, float g,
			    float b, float a);

/**
 * rk_video_ctx_add_line - Add line to context buffer
 * @inst: Instance pointer
 * @start_x: Line start x coord
 * @start_y: Line start y coord
 * @end_x: Line end x coord
 * @end_y: Line end y coord
 * 
 * This function add line to context buffer. For see changes
 * use rk_video_ctx_swap function
*/
void rk_video_ctx_add_line(struct rk_video_instance *inst, float start_x,
			   float start_y, float end_x, float end_y);

/**
 * rk_video_free - Free all module resources
 * @inst: Instance pointer
 * 
 * This function free all resources who allocated/used
*/
void rk_video_free(struct rk_video_instance *inst);

#endif /* RK_VIDEO_H */
