#include "../includes/minish.h"

int			count_pipe(t_list *list)
{
	t_cmd	*cmd;
	int		ret;

	ret = 0;
	while (list)
	{
		cmd = list->content;
		if (cmd->flag)
		{
			cmd->pipe_nbr = ret;
			ret++;
		}
		else
		{
			cmd->pipe_nbr = ret;
			return (ret);
		}
		list = list->next;
	}
	write(2, "Error\n", 6);
	return (-1);
}

void		ft_execve(t_cmd *cmd, int pipe_flag)
{
	char	**envp;

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

void		redirection(t_cmd *cmd)
{
	t_list	*rd_lst;
	t_redir	*rd;

	rd_lst = cmd->rd_lst->next;
	cmd->rd_fd[0] = 0;
	cmd->rd_fd[1] = 0;
	while (rd_lst)
	{
		rd = rd_lst->content;
		if (rd->sign == -1)
		{
			if (cmd->rd_fd[0] > 0)
				close(cmd->rd_fd[0]);
			cmd->rd_fd[0] = open(rd->file_name, O_RDONLY, 0644);
			if (cmd->rd_fd[0] < 0)
			{
				write(2, "Error\n", 6);
				return ;
			}
		}
		else if (rd->sign == 1)
		{
			if (cmd->rd_fd[1] > 0)
				close(cmd->rd_fd[1]);
			cmd->rd_fd[1] = open(rd->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else if (rd->sign == 2)
		{
			if (cmd->rd_fd[1] > 0)
				close(cmd->rd_fd[1]);
			cmd->rd_fd[1] = open(rd->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		rd_lst = rd_lst->next;
	}
}

void		builtin(t_cmd *cmd, int pipe_flag)
{
	int		temp_fd[2];

	pipe(temp_fd);
	if (cmd->rd_lst)
	{
		redirection(cmd);
		if (cmd->rd_fd[0])
		{
			dup2(0, temp_fd[0]);
			dup2(cmd->rd_fd[0], 0);
		}
		if (cmd->rd_fd[1])
		{
			dup2(1, temp_fd[1]);
			dup2(cmd->rd_fd[1], 1);
		}
	}
	if (*(cmd->argv))
		ft_execve(cmd, pipe_flag);
	if (cmd->rd_lst)
	{
		if (cmd->rd_fd[1])
			dup2(temp_fd[1], 1);
		if (cmd->rd_fd[0])
			dup2(temp_fd[0], 0);
	}
}

void		lets_fork(pid_t *pid, t_cmd *cmd, t_cmd *next_cmd)
{
	*pid = fork();
	if (*pid < 0)
		write(2, "Error\n", 6);
	else if (*pid == 0)
	{
		if (cmd->flag)
		{
			close(next_cmd->fd[0]);
			if (cmd->pipe_nbr != 0)
				dup2(cmd->fd[0], 0);
			dup2(next_cmd->fd[1], 1);
		}
		else
		{
			dup2(cmd->fd[0], 0);
		}
		builtin(cmd, 1);
		exit(0);
	}
	else
	{
		close(cmd->fd[0]);
		close(next_cmd->fd[1]);
	}
}

void		execute_builtin(t_list *cmd_root)
{
	t_list	*temp;
	t_cmd	*cmd;
	t_cmd	*next_cmd;
	int		idx;
	int		pipe_cnt;
	pid_t	*pid;

	idx = -1;
	temp = cmd_root->next;
	while (temp)
	{
		cmd = temp->content;
		if (cmd->flag)
		{
			pipe_cnt = count_pipe(temp);
			pid = (int *)malloc(sizeof(pid_t) * (pipe_cnt + 1));
			while (cmd->flag)
			{
				if (idx == -1)
				{
					pipe(cmd->fd);
					close(cmd->fd[1]);
				}
				if (temp->next)
				{
					next_cmd = temp->next->content;
					pipe(next_cmd->fd);
				}
				idx++;
				lets_fork(&pid[idx], cmd, next_cmd);
				temp = temp->next;
				cmd = temp->content;
			}
			if (cmd->flag == 0)
			{
				idx++;
				lets_fork(&pid[idx], cmd, next_cmd);
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
			builtin(cmd, 0);
		}
		temp = temp->next;
	}
}
