#include "minish.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int	idx;

	idx = 0;
	while (s1[idx] || s2[idx])
	{
		if ((s1[idx] != s2[idx]) || (s1[idx] == '\0') || (s2[idx] == '\0'))
			return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
		idx++;
	}
	return (0);
}

void	envv_lst_del(t_env *content)
{
	free(content->key);
	free(content->value);
	free(content);
}

//t_list			*envv_lst_find(char *key_value)
//{
//	t_list		*temp;
//	t_env		*temp_env;

//	temp = g_envv_lst->next;
//	while (temp)
//	{
//		temp_env = temp->content;
//		if (ft_strcmp(temp_env->key, key_value) == 0)
//			return (temp);
//		temp = temp->next;
//	}
//	return (NULL);
//}

t_list			*envv_lst_find(char *key_value)
{
	t_list		*ret;
	t_list		*temp;
	t_env		*temp_env;

	temp = g_envv_lst->next;
	ret = g_envv_lst;
	while (temp)
	{
		temp_env = temp->content;
		if (ft_strcmp(temp_env->key, key_value) == 0)
			return (ret);
		temp = temp->next;
		ret = ret->next;
	}
	return (NULL);
}
