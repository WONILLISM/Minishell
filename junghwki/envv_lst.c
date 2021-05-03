#include "../includes/minish.h"

void			envv_lst_del(t_env *content)
{
	free(content->key);
	free(content->value);
	free(content);
}

static t_env	*envv_sep(char *envv)
{
	int			idx;
	t_env		*ret;

	idx = 0;
	ret = (t_env *)malloc(sizeof(t_env));//free
	while (envv[idx])
	{
		if (envv[idx] == '=')
		{
			ret->key = ft_substr(envv, 0, idx);//free
			ret->value = ft_strdup(&envv[idx + 1]);//free
			break;
		}
		idx++;
	}
	return (ret);
}

void			envv_lst_make(char **envv)
{
	int			idx;
	t_list		*head;
	t_env		*content;

	idx = 0;
	head = ft_lstnew(0);
	while (envv[idx])
	{
		content = envv_sep(envv[idx]);
		ft_lstadd_back(&head, ft_lstnew(content));//free
		idx++;
	}
}
	// t_env *a;
	// t_list *tail;

	// tail = head->next;
	// while(tail)
	// {
	// 	a = (t_env *)(tail->content);
	// 	printf("%s=%s\n", a->key, a->value);
	// 	tail = tail->next;
	// }
