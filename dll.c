#include <dll.h>

DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *))
        {
        DLL *items = malloc(sizeof(DLL));
        assert(items != 0);
        items->head = 0;
        items->tail = 0;
        items->size = 0;
        items->display = d;
        items->free = f;
        return items;
		}
