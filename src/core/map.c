#include "rk/map.h"
#include "rk/video.h"

#include <stdio.h>

void rk_map_render_2d(struct rk_map *map, struct rk_video_instance *video)                         
{                                                                                                  
        for (int y = 0; y < map->height; ++y) {                                  
                for (int x = 0; x < map->width; ++x) {                           
                        int map_index = map->width * y + x;
                        if (map->text_map[map_index] == '#') {                            
                                int screen_x = x * map->field_size;
                                int screen_y = y * map->field_size;

                                rk_video_ctx_rectangle(                                            
                                        video, screen_x, screen_y,
					map->field_size, map->field_size
                                );                         
                        }                                                                          
                }                                                                                  
        }                                                                                          
}
