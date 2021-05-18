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
	int		*fd_p;
	int		*fd_c;

	fd_p = malloc(sizeof(int) * 2);
	fd_c = malloc(sizeof(int) * 2);
	if (pipe(fd_p) < 0 || pipe(fd_c) < 0)
		write(1, "Error\n", 6);
	pid = fork();
	if (pid < 0)
	{
		return (-1);
	}
	else if (pid == 0)
	{
		close(fd_p[WRITE]);
		close(fd_c[READ]);
		child_process(cmd);
	}
	else
	{
		close(fd_p[READ]);
		close(fd_c[WRITE]);
		wait(NULL);
	}
	free(fd_p);
	free(fd_c);
	return (0);
}
