#include <stdbool.h>
#include <stdlib.h>

#include "vector.h"

struct vector_header
{
    size_t size_allocated;
    size_t size_used;
};

static struct vector_header* vector_internal_get_header(void* self)
{
    return &(((struct vector_header*)self)[-1]);
}

static void* vector_internal_get_data(struct vector_header* self)
{
    return &self[1];
}

static bool vector_internal_has_space(struct vector_header* self, size_t type_size)
{
    if (self->size_used >= self->size_allocated)
    {
        return false;
    }

    return (self->size_allocated - self->size_used) >= type_size;
}

static struct vector_header* vector_internal_grow(struct vector_header* self, size_t type_size)
{
    const size_t new_size_allocated = (self->size_allocated == 0) ? type_size : (self->size_allocated * 2);
    struct vector_header* new_self = realloc(self, sizeof(*self) + new_size_allocated);
    new_self->size_allocated = new_size_allocated;
    return new_self;
}

void* vector_create(void)
{
    struct vector_header* header = malloc(sizeof(*header));
    header->size_allocated = 0;
    header->size_used = 0;
    return vector_internal_get_data(header);
}

void vector_internal_delete(void** self)
{
    free(vector_internal_get_header(*self));
    *self = NULL;
}

void vector_internal_push(void** self, size_t type_size)
{
    struct vector_header* header = vector_internal_get_header(*self);

    if (!vector_internal_has_space(header, type_size))
    {
        header = vector_internal_grow(header, type_size);
        *self = vector_internal_get_data(header);
    }

    header->size_used += type_size;
}

size_t vector_internal_size(void** self, size_t type_size)
{
    return vector_internal_get_header(*self)->size_used / type_size;
}

size_t vector_internal_capacity(void** self, size_t type_size)
{
    return vector_internal_get_header(*self)->size_allocated / type_size;
}