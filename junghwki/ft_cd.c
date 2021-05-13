#include "../includes/minish.h"

void		ft_cd(t_cmd *cmd)
{
	// char	*path;
	int		ret_value;
	// t_list	*temp;
	// t_env	*temp_env;

	ret_value = chdir(cmd->argv[1]);
	if (ret_value < 0)
	{
		write(1, "minishell: cd: ", 15);
		write(1, cmd->argv[1], ft_strlen(cmd->argv[1]));
		write(1, ": No such file or directory\n", 28);
	}
	// else
	// {
	// 	temp = get_curr_envv_lst("PWD");
	// 	if (temp)
	// 	{
	// 		path = NULL;
	// 		path = getcwd(NULL, 0);
	// 		if (path == NULL)
	// 			return;
	// 		else
	// 		{
	// 			temp_env = temp->content;
	// 			if (temp_env->value)
	// 				free(temp_env->value);
	// 			temp_env->value = path;
	// 		}
	// 		if (path)
	// 			free(path);
	// 	}
	// }
}
