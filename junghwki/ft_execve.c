#include "../includes/minish.h"
#define READ 0
#define WRITE 1

void	run_in_current_path(t_cmd *cmd)
{
	char	*path;
	char	*free_me;

	path = getcwd(NULL, 0);
	free_me = path;
	path = ft_strjoin(path, "/");
	free(free_me);
	free_me = path;
	path = ft_strjoin(path, cmd->argv[0]);
	free(free_me);
	execve(path, cmd->argv, NULL);
}

void	child_process(t_cmd *cmd)
{
	int		idx;
	t_list	*temp;
	t_env	*temp_env;
	char	**path;
	char	*free_me;

	idx = 0;
	temp = get_curr_envv_lst("PATH");
	if (temp)
	{
		temp_env = temp->content;
		path = ft_split(temp_env->value, ':');
		while (path[idx])
		{
			free_me = path[idx];
			path[idx] = ft_strjoin(path[idx], "/");
			free(free_me);
			free_me = path[idx];
			path[idx] = ft_strjoin(path[idx], cmd->argv[0]);
			free(free_me);
			execve(path[idx], cmd->argv, NULL);
			idx++;
		}
	}
	run_in_current_path(cmd);
}

int ft_execve(t_cmd *cmd)
{
	pid_t	pid;

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
		waitpid(pid, &g_archive.exit_stat, 0);
		// wait(NULL);
	}
	return (0);
}
