#include "../includes/minish.h"

void	free_rd_lst(t_list *rdlst)
{
	t_list	*tmp1;
	t_list	*tmp2;
	t_redir	*tmp_rd;

	tmp1 = rdlst->next;
	tmp2 = rdlst->next;
	while (tmp1)
	{
		tmp_rd = tmp1->content;
		free(tmp_rd->file_name);
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		free(tmp_rd);
		free(tmp2);
	}
	free(rdlst);
}

void	free_cmd_lst(t_list *cmd_root)
{
	t_list	*tmp1;
	t_list	*tmp2;
	t_cmd	*tmp_cmd;
	int		i;

	tmp1 = cmd_root->next;
	while (tmp1)
	{
		tmp_cmd = tmp1->content;
		i = 0;
		if (tmp_cmd->argv)
		{
			while (tmp_cmd->argv[i])
			{
				free(tmp_cmd->argv[i]);
				i++;
			}
			free(tmp_cmd->argv);
		}
		free_rd_lst(tmp_cmd->rd_lst);
		free(tmp_cmd);
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		free(tmp2);
	}
	free(cmd_root);
}
