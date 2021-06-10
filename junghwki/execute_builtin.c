#include "../includes/minish.h"


int			*redirection(t_cmd *cmd)
{
	int		fd[2];
	int		*temp_fd;
	t_list	*temp;
	t_redir	*temp_rd;

	fd[0] = 0;
	fd[1] = 1;
	temp_fd = (int *)malloc(sizeof(int) * 2);
	temp = cmd->rd_lst->next;
	while (temp)
	{
		temp_rd = temp->content;
		if (temp_rd->sign == 1)
		{
			fd[1] = open(temp_rd->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else if (temp_rd->sign == 2)
		{
			fd[1] = open(temp_rd->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else if (temp_rd->sign == -1)
		{
			fd[0] = open(temp_rd->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		temp = temp->next;
	}
	dup2(1, temp_fd[1]);
	dup2(fd[1], 1);
	dup2(0, temp_fd[0]);
	dup2(fd[0], 0);
	return (temp_fd);
}

void		builtin(t_cmd *cmd, int pipe_flag)
{
	char	**envp;
	int		*fd;

	if (cmd->rd_lst)
		fd = redirection(cmd);
	if (cmd->argv)
	{
		if (ft_strcmp(cmd->argv[0], "cd") == 0)
			ft_cd(cmd);
		else if (ft_strcmp(cmd->argv[0], "echo") == 0)
			ft_echo(cmd);
		else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(cmd->argv[0], "export") == 0)
			if (!cmd->argv[1])
				export_lst_print();
			else
				export_add(cmd);
		else if (ft_strcmp(cmd->argv[0], "unset") == 0)
			ft_unset(cmd);
		else if (ft_strcmp(cmd->argv[0], "env") == 0)
			env_lst_print();
		else if (ft_strcmp(cmd->argv[0], "exit") == 0)
			exit(0);
		else
		{
			envp = make_envp();
			if (pipe_flag)
				child_process(cmd, envp);
			else
				other_command(cmd, envp);
			free_array(envp);
		}
	}
	dup2(fd[1], 1);
	dup2(fd[0], 0);
}
void		lets_fork(pid_t *pid, t_cmd *cmd, t_cmd *next_cmd, int idx)
{
	*pid = fork();
	if (*pid < 0)
		write(2, "Error\n", 6);
	else if (*pid == 0)
	{
		if (cmd->flag)
		{
			close(next_cmd->fd[0]);
			if (idx != 0)
				dup2(cmd->fd[0], 0);
			dup2(next_cmd->fd[1], 1);
		}
		else
			dup2(cmd->fd[0], 0);
		builtin(cmd, 1);
		exit(0);
	}
	else
	{
		close(cmd->fd[0]);
		close(next_cmd->fd[1]);
	}
}

int		count_pipe(t_list *list)
{
	t_cmd	*cmd;
	int		ret;

	ret = 0;
	while (list)
	{
		cmd = list->content;
		if (cmd->flag)
			ret++;
		else
			return (ret);
		list = list->next;
	}
	write(2, "Error\n", 6);
	return (-1);
}

void		execute_builtin(t_list *cmd_root)
{
	t_list	*temp;
	t_cmd	*temp_cmd;
	t_cmd	*temp_next_cmd;
	int		idx;
	int		pipe_cnt;
	pid_t	*pid;

	idx = -1;
	temp = cmd_root->next;
	while (temp)
	{
		temp_cmd = temp->content;
		if (temp_cmd->flag)
		{
			pipe_cnt = count_pipe(temp);
			pid = (int *)malloc(sizeof(pid_t) * (pipe_cnt + 1));
			while (temp_cmd->flag)
			{
				if (idx == -1)
				{
					pipe(temp_cmd->fd);
					close(temp_cmd->fd[1]);
				}
				if (temp->next)
				{
					temp_next_cmd = temp->next->content;
					pipe(temp_next_cmd->fd);
				}
				idx++;
				lets_fork(&pid[idx], temp_cmd, temp_next_cmd, idx);
				temp = temp->next;
				temp_cmd = temp->content;
			}
			if (temp_cmd->flag == 0)
			{
				idx++;
				lets_fork(&pid[idx], temp_cmd, temp_next_cmd, idx);
				while (idx >= 0)
				{
					waitpid(pid[pipe_cnt - idx], &g_archive.exit_stat, 0);
					idx--;
				}
			}
			free(pid);
		}
		else
		{
			builtin(temp_cmd, 0);
		}
		temp = temp->next;
	}
}

// void		execute_builtin(t_list *cmd_root)
// {
// 	t_list	*temp;
// 	t_cmd	*temp_cmd;
// 	t_cmd	*temp_next_cmd;
// 	// int		*pid;
// 	int		pid[10];
// 	int		idx;

// 	// pid = (int *)malloc(sizeof(int) * pipe_cnt);
// 	idx = -1;
// 	temp = cmd_root->next;
// 	while (temp)
// 	{
// 		temp_cmd = temp->content;
// 		if (temp_cmd->flag)
// 		{
// 			if (idx == -1)
// 			{
// 				pipe(temp_cmd->fd);
// 				close(temp_cmd->fd[1]);
// 			}
// 			if (temp->next)
// 			{
// 				temp_next_cmd = temp->next->content;
// 				pipe(temp_next_cmd->fd);
// 			}
// 			else
// 				write(1, "Error\n", 6);
// 			idx++;
// 			pid[idx] = fork();
// 			if (pid[idx] < 0)
// 				write(1, "Error\n", 6);
// 			else if (pid[idx] == 0)
// 			{
// 				if (temp_cmd->flag)
// 				{
// 					close(temp_next_cmd->fd[0]);
// 					if (idx != 0)
// 					{
// 						dup2(temp_cmd->fd[0], 0);
// 					}
// 					dup2(temp_next_cmd->fd[1], 1);
// 				}
// 				else
// 				{
// 					dup2(temp_cmd->fd[0], 0);
// 				}
// 				builtin(temp_cmd, 0);
// 				exit(0);
// 			}
// 			else
// 			{
// 				close(temp_cmd->fd[0]);
// 				close(temp_next_cmd->fd[1]);
// 			}
// 		}
// 		else
// 		{
// 			builtin(temp_cmd, 1);
// 		}
// 		temp = temp->next;
// 		if (temp_cmd->flag == 0)
// 		{
// 			while (idx >= 0)
// 			{
// 				waitpid(pid[idx], &g_archive.exit_stat, 0);
// 				idx--;
// 			}
// 		}
// 	}
// }
