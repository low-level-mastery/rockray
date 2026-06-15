#ifndef RK_LOGGER_H
#define RK_LOGGER_H

#include <stdio.h>

/* ANSI Terminal Colors for Output */
#define LOG_CLR_RESET   "\033[0m"
#define LOG_CLR_ERR     "\033[1;31m" /* Bold Red */
#define LOG_CLR_WARN    "\033[1;33m" /* Bold Yellow */
#define LOG_CLR_INFO    "\033[1;32m" /* Bold Green */
#define LOG_CLR_DEBUG   "\033[1;36m" /* Bold Cyan */

/* Core logging engine macro using do-while-0 guard */
#define rk_log(stream, color, prefix, fmt, ...)                         \
	do {                                                            \
		fprintf(stream, color "[%s] " LOG_CLR_RESET             \
			"[%s:%d -> %s()]: " fmt "\n",                   \
			prefix, __FILE__, __LINE__, __func__,           \
			##__VA_ARGS__);                                 \
	} while (0)

/* Public log levels */
#define pr_err(fmt, ...)   rk_log(stderr, LOG_CLR_ERR,   "ERR",   fmt, ##__VA_ARGS__)
#define pr_warn(fmt, ...)  rk_log(stdout, LOG_CLR_WARN,  "WARN",  fmt, ##__VA_ARGS__)
#define pr_info(fmt, ...)  rk_log(stdout, LOG_CLR_INFO,  "INFO",  fmt, ##__VA_ARGS__)

/* Debug log (can be completely disabled in release builds) */
#ifdef CONFIG_RK_DEBUG
#define pr_debug(fmt, ...) rk_log(stdout, LOG_CLR_DEBUG, "DEBUG", fmt, ##__VA_ARGS__)
#else
#define pr_debug(fmt, ...) do { } while (0)
#endif

#endif /* RK_LOGGER_H */

