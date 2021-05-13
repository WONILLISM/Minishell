#include "../includes/minish.h"

void	child_process(t_cmd *cmd)
{
	t_list	*temp;
	t_env	*temp_env;
	char	**path;
	int		idx;

	idx = 0;
	temp = get_curr_envv_lst("PATH");
	if (temp)
	{
		temp_env = temp->content;
		path = ft_split(temp_env->value, ':');
		while (path[idx])
		{
			path[idx] = ft_strjoin(path[idx], "/");
			path[idx] = ft_strjoin(path[idx], cmd->argv[0]);
			execve(path[idx], cmd->argv, NULL);
			idx++;
		}
	}
}

int ft_execve(t_cmd *cmd)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		return (-1);
	}
	else if (pid == 0)
	{
		child_process(cmd);
	}
	else
	{
		wait(NULL);
	}
	return (0);
}
