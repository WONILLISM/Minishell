#include "../includes/minish.h"

t_list			*get_prev_envv_lst(char *key_value)
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

void	ft_unset(t_cmd *cmd)
{
	t_list	*temp;
	t_list	*del_lst;
	void	(*del)();
	int		idx;

	idx = 0;
	del = envv_lst_del;
	while(cmd->argv[idx])
	{
		temp = get_prev_envv_lst(cmd->argv[idx]);
		if (temp)
		{
			del_lst = temp->next;
			temp->next = del_lst->next;
			ft_lstdelone(del_lst, del);
		}
		idx++;
	}
}

