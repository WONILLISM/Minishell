#include "../includes/minish.h"

void	ft_unset(t_cmd *cmd)
{
	t_list	*temp;
	t_list	*del_lst;
	// t_env	*temp_env;
	void	(*del)();
	int		idx;

	idx = 0;
	del = envv_lst_del;
	while(cmd->argv[idx])
	{
		temp = envv_lst_find(cmd->argv[idx]);
		if (temp)
		{
			del_lst = temp->next;
			temp->next = del_lst->next;
			ft_lstdelone(del_lst, del);
		}
		idx++;
	}
}

