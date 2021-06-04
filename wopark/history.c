#include "../includes/minish.h"

void	history(t_dllist *list, char *input)
{
	//t_dllist	list;

	//ft_dll_init(&list);
	ft_dll_add(list, input);
	ft_dll_viewlst(list);
}
