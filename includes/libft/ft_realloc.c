#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*ret;
	size_t	cursize;

	if (!ptr)
		return (malloc(size));
	cursize = sizeof(ptr);
	if (size <= cursize)
		return (ptr);
	ret = malloc(size);
	if (!ret)
		return (NULL);
	ft_memmove(ptr, ret, size);
	free(ptr);
	return (ret);
}
