#include <stdio.h>
#include <stdlib.h>

void *aligned_malloc(size_t size, unsigned int align)
{
    void *head;
    void **addr;

    head = (void*)malloc(size + align - 1 + sizeof(void*));

    if (size == 0 || head == NULL)
        return NULL;

    unsigned int i = (unsigned int)head + sizeof(void*);

    while (i < (unsigned int)head + sizeof(void*) + align - 1) {
        if  (i % align == 0) {
            addr = i;
            break;
        }
        i++;
    }

    addr[-1] = head;

    return addr;
}

void *aligned_free(void *addr)
{
    void *ptr = ((void**)addr)[-1];
    free(ptr);
}

int main()
{
    int *p = aligned_malloc(16, 128);
    printf("Hex: %p\n", p);
    printf("Dec: %u\n", p);
    printf("p %% align: %u\n", (unsigned int)p % 128);
    aligned_free(p);

    return 0;
}
