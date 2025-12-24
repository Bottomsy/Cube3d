#include "../cub3d.h"

int lst_new(t_pointers **ptrs, void *ptr)
{
    t_pointers	*new;

    new = malloc(sizeof(t_pointers));
    if (!new)
    {
        free(ptr);
        return (0);
    }
    new->ptr = ptr;
    new->next = *ptrs;
    *ptrs = new;
    return (1);
}

void lst_free(t_pointers **ptrs)
{
    t_pointers	*temp;
    t_pointers	*current;

    current = *ptrs;
    while (current)
    {
        temp = current;
        current = current->next;
        if (temp->ptr)
            free(temp->ptr);
        free(temp);
    }
    *ptrs = NULL;
}

void	*ft_malloc(t_pointers **ptrs, size_t size)
{
    void	*ptr;

    ptr = malloc(size);
    if (!ptr)
    {
        lst_free(ptrs);
        exit(0);
    }
    if (!lst_new(ptrs, ptr))
    {
        lst_free(ptrs);
        exit(0);
    }
    return (ptr);
}
