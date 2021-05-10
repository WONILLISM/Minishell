#include "../includes/minish.h"

void		ft_cd(t_cmd *cmd)
{
	int		ret_value;

	ret_value = chdir(cmd->argv[1]);
	if (ret_value < 0)
	{
		write(1, "minishell: cd: ", 15);
		write(1, cmd->argv[1], ft_strlen(cmd->argv[1]));
		write(1, ": No such file or directory\n", 28);
	}
}
