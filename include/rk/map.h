#ifndef RK_MAP_H
#define RK_MAP_H

#include "rk/video.h"

/**
 * struct map - Map data structure
 *
 * This structure need to organize data for map
*/
struct rk_map {
	char *text_map; /* Map with symbols */
	int width; /* Map width */
	int height; /* Map height */
	int field_size; /* Filed size in map */
};

/**
 * map_render_2d - Render 2d map
 * @map: Map instance
 * @video: Video instance pointer
 *
 * This function render 2d map
*/
void rk_map_render_2d(struct rk_map *map, struct rk_video_instance *video);


#endif /* RK_MAP_H */
