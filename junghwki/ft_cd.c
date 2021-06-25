#include "../includes/minish.h"

void		ft_cd(t_cmd *cmd)
{
	int		ret_value;
	char	*path;
	t_list	*temp;
	t_env	*temp_env;

	ret_value = chdir(cmd->argv[1]);
	if (ret_value < 0)
	{
		g_archive.exit_stat = 1;
		write(2, "minish: cd: ", 12);
		if (cmd->argv[1])
			write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
		write(2, ": No such file or directory\n", 28);
	}
	else
	{
		temp = get_curr_envv_lst("PWD");
		if (temp)
		{
			path = NULL;
			path = getcwd(NULL, 0);
			if (path == NULL)
				printf("ft_cd path Error\n");
			else
			{
				temp_env = temp->content;
				if (temp_env->value)
					free(temp_env->value);
				temp_env->value = ft_strdup(path);
			}
			if (path)
				free(path);
		}
		g_archive.exit_stat = 0;
	}
}
