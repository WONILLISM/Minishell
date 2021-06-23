#include "../includes/minish.h"

int			ft_error(int exit_stat)
{
	g_archive.exit_stat = exit_stat;
	exit(exit_stat);
}

void		ft_exit(t_cmd *cmd)
{
	int		idx;

	idx = 0;
	if (!(cmd->argv[1]))
	{
		g_archive.exit_stat = 0;
		exit(g_archive.exit_stat);
	}
	if (cmd->argv[2])
		write(2, "minish: exit: too many arguments\n", 33);
	while (cmd->argv[1][idx])
	{
		if (!ft_isdigit(cmd->argv[1][idx]))
		{
			write(2, "minish: exit: abc: numeric argument required\n", 45);
			g_archive.exit_stat = 255;
			exit(g_archive.exit_stat);
		}
		idx++;
	}
	g_archive.exit_stat = ft_atoi(cmd->argv[1]);
	exit(g_archive.exit_stat);
}