#include "rk/logger.h"
#include "rk/core.h"

#include <stdlib.h>

int main(void)
{
	struct rk_engine_instance *engine = rk_engine_alloc();
	if (!engine) {
		pr_err("Instance allocate:\tFailed");
		return -1;
	}
	
	pr_info("Instance allocate:\tSuccess");

	int err = rk_engine_init(engine);
	if (err < 0) {
		pr_err("Instance initialize:\tFailed");
		goto out_free;
	}
	
	pr_info("Instance initialize:\tSuccess");

	rk_engine_run(engine);

	rk_engine_free(engine);

	return 0;

out_free:
	pr_err("Engine crushed. Free all resources...");
	free(engine);
	return -1;

}
