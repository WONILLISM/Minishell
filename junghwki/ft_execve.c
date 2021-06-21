#include "../includes/minish.h"

char		**make_envp(void)
{
	t_list	*temp;
	t_env	*temp_env;
	char	**envp;
	int		idx;
	char	*free_me;

	idx = 0;
	temp = g_archive.envv_lst->next;
	envp = (char **)malloc(sizeof(char *) * (ft_lstsize(temp) + 1));
	while (temp)
	{
		temp_env = temp->content;
		free_me = ft_strjoin(temp_env->key, "=");
		envp[idx] = ft_strjoin(free_me, temp_env->value);
		free(free_me);
		temp = temp->next;
		idx++;
	}
	envp[idx] = NULL;
	return (envp);
}

void		run_in_current_path(t_cmd *cmd, char **envp)
{
	char	*path;
	char	*free_me;

	path = getcwd(NULL, 0);
	if (path == NULL)
		printf("path Error\n");
	else
	{
		free_me = path;
		path = ft_strjoin(path, "/");
		free(free_me);
		free_me = path;
		path = ft_strjoin(path, cmd->argv[0]);
		free(free_me);
		execve(path, cmd->argv, envp);
	}
}

void		child_process(t_cmd *cmd, char **envp)
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
			execve(path[idx], cmd->argv, envp);
			idx++;
		}
		free_array(path);
	}
	else
		g_archive.exit_stat = 127;
	run_in_current_path(cmd, envp);
	write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
	write(2, ": command not found\n", 20);
	exit(0);
}

void		other_command(t_cmd *cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		write(2, "Error\n", 6);
	}
	else if (pid == 0)
	{
		child_process(cmd, envp);
	}
	else
	{
		waitpid(pid, &g_archive.exit_stat, 0);
	}
}
