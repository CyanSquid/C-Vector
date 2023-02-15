# C-Vector

Very basic vector implementation in C. 

Only supports creating a vector, pushing elements, and deleting a vector.

I will add pop, insert and remove support at a later date. 

```C
    vector(int) items = vector_create();

    for (int i = 0; i < 10; i++)
    {
        vector_push(items, i);
    }

    for (size_t i = 0; i < vector_size(items); i++)
    {
        printf("item[%zu] %i\n", i, items[i]);
    }

    vector_delete(items);
```
