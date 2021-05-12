#include "../includes/minish.h"

void		convert_env(char *s)
{
	t_list	*res;
	t_env	*tmp;

	res = envv_lst_find(s)->next;
	tmp = res->content;
	write(1, tmp->value,ft_strlen(tmp->value));
}

void		ft_echo(t_cmd *cmd)
{
	int		idx;
	int		n_flag;

	idx = 1;
	n_flag = 0;
	while (ft_strcmp(cmd->argv[idx], "-n") == 0)
	{
		n_flag = 1;
		idx++;
	}
	while (cmd->argv[idx])
	{
		if (cmd->argv[idx][0] == '$')
			convert_env(&cmd->argv[idx][1]);
		else
			write(1, cmd->argv[idx], ft_strlen(cmd->argv[idx]));
		idx++;
		if (cmd->argv[idx])
			write(1, " ", 1);
		else if (!n_flag)
			write(1, "\n", 1);
	}
}
