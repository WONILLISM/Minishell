#include "../includes/minish.h"

t_dllist	*ft_dllistnew(void	*data)
{
	t_dllist	*node;

	if (!(node = (t_dllist *)malloc(sizeof(t_dllist))))
		return (NULL);
	node->prev = NULL;
	node->data = data;
	node->next = NULL;
}
