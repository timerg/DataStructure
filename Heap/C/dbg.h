#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

// The start of a #ifdef which lets you recompile your program so that all the debug log messages are removed.
    // the "debug log messages" are the messages behind "fprintf"
#ifdef NDEBUG
#define debug(M, ...)
#else
                                                            // %s      %d         M
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
// This will replace "debug(M, arg1, arg2, ...)"
// The " ##__VA_ARGS__" means:
    // "put whatever they had for extra arguments (...) here"

#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }



#endif




// "perror("...")" vs fprintf(stderr, "...")
    // perror:  are used to interpret value of errno
    // fprintf...: Can be used to print your own custom error messages.
        // By printing to stderr,
        // you avoid your error reporting output being muxed with "normal" output that should be going to stdout.




















//