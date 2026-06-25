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
 * rk_video_ctx_rectangle - Render rectangle
 * @inst: Instance pointer
 * @x: X position
 * @y: Y position
 * @w: Width
 * @h: Height
 *
 * This function render filled rectangle in @x/@y position
 * and width/height from @w/@h
*/
void rk_video_ctx_rectangle(struct rk_video_instance *inst, float x, float y,
			    float w, float h);

/**
 * rk_video_free - Free all module resources
 * @inst: Instance pointer
 * 
 * This function free all resources who allocated/used
*/
void rk_video_free(struct rk_video_instance *inst);

#endif /* RK_VIDEO_H */
