#ifndef __dbg_h__
#define __dbg_h__

// #include "dbg.c"

void* my_debug_malloc(size_t size, char* FILE, int LINE){
    fprintf(stderr, "%s:%d\n", FILE, LINE);
    return (malloc(size));
}

void my_debug_free(void *ptr, char* FILE, int LINE){
    fprintf(stderr, "%s:%d\n", FILE, LINE);
    free(ptr);
}

void my_debug_printf(void *ptr, void *arg, char* FILE, int LINE){
    fprintf(stderr, "[PRINT]}%s:%d ", FILE, LINE);
}

// #define  malloc(x) my_debug_malloc(x, __FILE__, __LINE__)
// #define  free(x)  my_debug_free(x, __FILE__, __LINE__)
// #define  printf(X, ...) fprintf(stderr, "[PRINT]}%s:%d:" X "\n", __FILE__, __LINE__, ##__VA_ARGS__)

// Cover printf
#define  printf(X, ...) printf("");

#endif