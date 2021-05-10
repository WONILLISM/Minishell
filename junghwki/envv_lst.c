#include "../includes/minish.h"

void		env_swap(t_env *a, t_env *b)
{
	t_env	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

t_env		*envv_sep(char *envv)
{
	int		idx;
	t_env	*ret;

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
	if (envv[idx] == '\0')
	{
		ret->key = ft_substr(envv, 0, idx);
		ret->value = NULL;
	}
	return (ret);
}

void		envv_lst_make(char **envv)
{
	int		idx;
	t_env	*content;

	idx = 0;
	g_envv_lst = ft_lstnew(0);
	while (envv[idx])
	{
		content = envv_sep(envv[idx]);
		ft_lstadd_back(&g_envv_lst, ft_lstnew(content));//free
		idx++;
	}
}

void		env_lst_print()
{
	t_list	*temp;
	t_env	*temp_env;

	temp = g_envv_lst->next;
	while (temp)
	{
		temp_env = temp->content;
		if (temp_env->value)
		{
			write(1, temp_env->key, ft_strlen(temp_env->key));
			write(1, "=", 1);
			write(1, temp_env->value, ft_strlen(temp_env->value));
			write(1, "\n", 1);
		}
		temp = temp->next;
	}
}
