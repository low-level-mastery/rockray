#include "rk/core.h"
#include "rk/logger.h"

#include <stdlib.h>
#include <stdbool.h>

struct rk_engine_instance {
	
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
	return true;
}

void rk_engine_run(struct rk_engine_instance *engine)
{

}

void rk_engine_free(struct rk_engine_instance *engine)
{
	if (!engine) {
		return;
	}
	
	free(engine);
}
