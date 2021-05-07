#include "../includes/minish.h"

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
		write(1, cmd->argv[idx], ft_strlen(cmd->argv[idx]));
		idx++;
		if (cmd->argv[idx])
			write(1, " ", 1);
		else if (!n_flag)
			write(1, "\n", 1);
	}
}