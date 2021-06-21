#include "../includes/minish.h"

t_hisnode	*ft_dll_newhisnode(void *pending, void *finished)
{
	t_hisnode	*node;

	node = (t_hisnode *)malloc(sizeof(t_hisnode));
	node->pending = ft_strdup(pending);
	node->finished = ft_strdup(finished);
	node->idx = -1;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void		ft_dll_init(t_dllist *list)
{
	list->head = ft_dll_newhisnode(NULL, NULL);
	list->tail = ft_dll_newhisnode(NULL, NULL);
	list->head->next = list->tail;
	list->tail->prev = list->head;
	list->length = 0;
}

void		ft_dll_addhisnode(t_dllist *list, void *pending, void *finished)
{
	t_hisnode	*node;

	node = ft_dll_newhisnode(pending, finished);
	node->prev = list->tail->prev;
	node->next = list->tail;
	list->tail->prev->next = node;
	list->tail->prev = node;
	list->length++;
	node->idx = node->prev->idx + 1;
}

void		ft_dll_delhisnode(t_dllist *list, t_hisnode *node, void (*del)(void *, void *))
{
	del(node->pending, node->finished);
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node);
	list->length--;
}

// t_hisnode	*ft_dll_find_idx(t_dllist *list, int idx)
// {
// 	t_hisnode	*ret;

// 	ret = list->head->next;
// 	while (ret != list->tail)
// 	{
// 		if (ret->idx == idx)
// 			return (ret);
// 		ret = ret->next;
// 	}
// 	return (NULL);
// }

void		ft_dll_viewlst(t_dllist *list)
{
	t_hisnode	*node;
	char		*tmp1;
	char		*tmp2;

	node = list->head->next;
	while (node != list->tail)
	{
		tmp1 = node->pending;
		tmp2 = node->finished;
		printf("----------- node %d -----------\n", node->idx);
		printf("pending : %s\n", tmp1);
		printf("finished : %s\n", tmp2);
		printf("------- list length %d --------\n", list->length);
		node = node->next;
	}
	printf("\n");
}

// void		ft_dll_clear(t_dllist *list, void (*del)(void *))
// {
// 	t_hisnode	*node;

// 	node = list->head->next;
// 	while (node != list->tail)
// 	{
// 		ft_dll_delnode(list, node, del);
// 		node = list->head->next;
// 	}
// }
