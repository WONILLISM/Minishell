#include "../includes/minish.h"

void		ft_cd(t_cmd *cmd)
{
	int		ret_value;

	ret_value = chdir(cmd->argv[1]);
	if (ret_value < 0)
		printf("minishell: cd: %s: No such file or directory\n",cmd->argv[1]);
}
