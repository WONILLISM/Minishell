#include "../includes/minish.h"

int		argv_is_empty(char *s)
{
	if (!s)
	{
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

void		ft_echo(t_cmd *cmd)
{
	int		idx;
	int		n_flag;

	idx = 1;
	if (argv_is_empty(cmd->argv[idx]))
		return ;
	n_flag = 0;
	while (ft_strcmp(cmd->argv[idx], "-n") == 0)
	{
		n_flag = 1;
		idx++;
	}
	if (argv_is_empty(cmd->argv[idx]))
		return ;
	while (cmd->argv[idx])
	{
		write(1, cmd->argv[idx], ft_strlen(cmd->argv[idx]));
		idx++;
		if (cmd->argv[idx])
			write(1, " ", 1);
		else if (!n_flag)
			write(1, "\n", 1);
	}
}
