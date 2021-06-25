#include "../includes/minish.h"

// 9223372036854775807
// int			exit_str_check(char *str)
// {
// 	int		idx;

// 	idx = 0;
// 	if (str[idx] == '-' || str[idx] == '+')
// 		idx++;
// 	if (ft_strlen(str[idx]) > 19)
// 		return (-1);
// 	return (0);
// }

// int			ft_error(int exit_stat)
// {
// 	g_archive.exit_stat = exit_stat;
// 	exit(exit_stat);
// }

void		ft_exit(t_cmd *cmd)
{
	int		idx;

	idx = 0;
	if (!(cmd->argv[1]))
	{
		if (!cmd->flag)
			write(2, "exit\n", 5);
		exit(g_archive.exit_stat);
	}
	if (cmd->argv[2])
	{
		g_archive.exit_stat = 1;
		write(2, "minish: exit: too many arguments\n", 33);
	}
	else
	{
		while (cmd->argv[1][idx])
		{
			if (!ft_isdigit(cmd->argv[1][idx]))
			{
				g_archive.exit_stat = 255;
				write(2, "minish: exit: ", 14);
				write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
				write(2, ": numeric argument required\n", 28);
				exit(g_archive.exit_stat);
			}
			idx++;
		}
		g_archive.exit_stat = ft_atoi(cmd->argv[1]);
		write(1, "exit\n", 5);
		exit(g_archive.exit_stat);
	}
}