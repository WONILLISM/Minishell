#include "../includes/minish.h"

t_dlnode	*ft_dll_newnode(void	*data)
{
	t_dlnode	*node;

	node = (t_dlnode *)malloc(sizeof(t_dlnode));
	node->data = data;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void		ft_dll_init(t_dllist *list)
{
	list->head = ft_dll_newnode(NULL);
	list->tail = ft_dll_newnode(NULL);
	list->head->next = list->tail;
	list->tail->prev = list->head;
	list->length = 0;
}

void		ft_dll_add(t_dllist *list, void *data)
{
	t_dlnode	*node;

	node = ft_dll_newnode(data);
	node->prev = list->tail->prev;
	node->next = list->tail;
	list->tail->prev->next = node;
	list->tail->prev = node;
	list->length++;
}

void		ft_dll_delnode(t_dllist *list, t_dlnode *node, void (*del)(void *))
{
	del(node->data);
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
	list->length--;
}

t_dlnode	*ft_dll_find(t_dllist *list, void *data)
{
	t_dlnode	*ret;

	ret = list->head->next;
	while (ret != list->tail)
	{
		if (ret->data == data)
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

void		ft_dll_viewlst(t_dllist *list)
{
	t_dlnode	*node;
	char		*tmp;

	node = list->head->next;
	while (node != list->tail)
	{
		tmp = node->data;
		printf("%s\n", tmp);
		node = node->next;
	}
}

void		ft_dll_clear(t_dllist *list, void (*del)(void *))
{
	t_dlnode	*node;

	node = list->head->next;
	while (node != list->tail)
	{
		ft_dll_delnode(list, node, del);
		node = list->head->next;
	}
}
