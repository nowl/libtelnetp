#ifndef __UTILS_H__
#define __UTILS_H__

#include <memory.h>
#include <stdlib.h>

void *memory_grow_to_size(void *mem_p, size_t *mem_cap_ip, size_t mem_size_i);

#endif  /* __UTILS_H__ */
