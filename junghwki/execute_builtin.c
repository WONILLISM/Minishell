#include "../includes/minish.h"

void		builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
	{
		ft_cd(cmd);
	}
	else if (ft_strcmp(cmd->argv[0], "echo") == 0)
	{
		ft_echo(cmd);
	}
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
	{
		ft_pwd();
	}
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
	{
		if (!cmd->argv[1])
			export_lst_print();
		else
			export_add(cmd);
	}
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
	{
		ft_unset(cmd);
	}
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
	{
		env_lst_print();
	}
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
	{
		exit(0);
	}
	else
	{
		ft_execve(cmd);
		// write(1, temp_cmd->argv[0], ft_strlen(temp_cmd->argv[0]));
		// write(1, ": command not found\n", 20);
	}
}

void		execute_builtin(t_list *cmd_root)
{
	t_list	*temp;
	t_cmd	*temp_cmd;
	t_cmd	*temp_next_cmd;
	int		pid;
	int		pipe_flag;
	int		start;
	int		status;

	pid = 1;
	start = 0;
	pipe_flag = 0;
	temp = cmd_root->next;
	while (temp)
	{
		temp_cmd = temp->content;
		if (temp_cmd->flag || pipe_flag)
		{
			pipe_flag = 1;
			if (!start)
			{
				pipe(temp_cmd->fd);
				start = 1;
			}
			if (temp_cmd->flag)
			{
				temp_next_cmd = temp->next->content;
				pipe(temp_next_cmd->fd);
			}
			pid = fork();
			if (pid < 0)
				write(1, "Error\n", 6);
			else if (pid == 0)
			{
				if (temp_cmd->flag)
				{
					close(temp_next_cmd->fd[0]);
					dup2(temp_cmd->fd[0], 0);
					dup2(temp_next_cmd->fd[1], 1);
				}
				else
				{
					dup2(temp_cmd->fd[0], 0);
				}
				builtin(temp_cmd);
				exit(1);
			}
			else
			{
				close(temp_cmd->fd[0]);
				close(temp_next_cmd->fd[1]);
				waitpid(pid, &status ,WNOHANG);
			}
		}
		else
			builtin(temp_cmd);
		temp = temp->next;
	}
}