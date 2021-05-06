#include "../includes/minish.h"

t_list			*envv_lst_find(char *key_value)
{
	t_list		*temp;
	t_env		*temp_env;

	temp = g_envv_lst->next;
	temp_env = temp->content;
	while(temp)
	{
		if (ft_strcmp(temp_env->key, key_value) == 0)
			return (temp);
		temp = temp->next;
		if (temp)
			temp_env = temp->content;
	}
	return (NULL);
}

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
	g_envv_lst = ft_lstnew(0);
	while (envv[idx])
	{
		content = envv_sep(envv[idx]);
		ft_lstadd_back(&g_envv_lst, ft_lstnew(content));//free
		idx++;
	}
	t_env *a;
	t_list *temp;

	temp = g_envv_lst->next;
	while(temp)
	{
		a = (t_env *)(temp->content);
		printf("%s=%s\n", a->key, a->value);
		temp = temp->next;
	}
}

	int				main(int argc, char **argv, char **envv)
{
	char			*input;
	t_list			*temp;
	t_env			*a;

	envv_lst_make(envv);
	temp = envv_lst_find("aaa");
	a = temp->content;
	printf("%s\n",a->value);
	return (0);
}

