#pragma once

#include <stddef.h>

#define vector(TYPE) TYPE*

#define vector_delete(VECTOR) \
    vector_internal_delete(&(VECTOR))

#define vector_push(VECTOR, DATA) \
    (vector_internal_push(&(VECTOR), sizeof(*(VECTOR))), (VECTOR)[vector_internal_size(&(VECTOR), sizeof(*(VECTOR))) - 1] = (DATA))

#define vector_size(VECTOR) \
    vector_internal_size(&(VECTOR), sizeof(*(VECTOR)))

#define vector_capacity(VECTOR) \
    vector_internal_capacity(&(VECTOR), sizeof(*(VECTOR)))


void* vector_create(void);

void vector_internal_delete(void** self);

void vector_internal_push(void** self, size_t type_size);

size_t vector_internal_size(void** self, size_t type_size);
size_t vector_internal_capacity(void** self, size_t type_size);
