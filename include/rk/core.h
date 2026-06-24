#ifndef RK_CORE_H
#define RK_CORE_H

struct rk_engine_instance;

/**
 * rk_engine_alloc - Allocate memory for instance
 * 
 * This function use system allocator and allocate
 * memory for instance.
*/
struct rk_engine_instance *rk_engine_alloc(void);

/**
 * rk_engine_init - Initialize instance
 * @engine: Engine instance pointer
 *
 * This function initialize all submodules of engine
 * and allocates memory for custom allocator.
 * 
 * Return 0 if success or negative error code if fail.
*/
int rk_engine_init(struct rk_engine_instance *engine);

/**
 * rk_engine_run - Start engine mainloop
 * @engine: Engine instance pointer
 * 
 * This function start engine mainloop.
*/
void rk_engine_run(struct rk_engine_instance *engine);

/**
 * rk_engine_free - Free all resources
 * @engine: Engine instance pointer
 *
 * This function destroy all submodules and free
 * used memory and descriptors.
*/
void rk_engine_free(struct rk_engine_instance *engine);

#endif /* RK_CORE_H */
