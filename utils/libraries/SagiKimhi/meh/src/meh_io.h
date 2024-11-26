#ifndef MEH_REPORT_MACROS_H_
#define MEH_REPORT_MACROS_H_

#ifndef meh_log
# define meh_log(fd, tag, ...)                                              \
     do {                                                                   \
         fprintf(                                                           \
             fd, "[%s] %s (file: %s, line: %0d): ", tag, __func__, __FILE__, __LINE__); \
         fprintf(fd, __VA_ARGS__);                                          \
         fprintf(fd, "\n");                                                 \
     } while (0)
#endif

#ifndef meh_info
# define meh_info(fmt, ...) meh_log(stdout, "INFO", fmt, ##__VA_ARGS__)
#endif

#ifndef meh_debug
# define meh_debug(fmt, ...) meh_log(stdout, "DEBUG", fmt, ##__VA_ARGS__)
#endif

#ifndef meh_error
# define meh_error(fmt, ...) meh_log(stderr, "ERROR", fmt, ##__VA_ARGS__)
#endif

#ifndef meh_fatal
# define meh_fatal(fmt, ...) meh_log(stderr, "FATAL", fmt, ##__VA_ARGS__)
#endif

#ifndef meh_check
# define meh_check(cond)                                 \
     do {                                                \
         if (!(cond)) {                                  \
             meh_error("condition '" #cond "' failed."); \
         }                                               \
     } while (0)
#endif

#ifndef meh_ensure
# define meh_ensure(cond, ret)                           \
     do {                                                \
         if (!(cond)) {                                  \
             meh_error("condition '" #cond "' failed."); \
             return ret;                                 \
         }                                               \
     } while (0)
#endif

#endif
