/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghwki <junghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:24:26 by junghwki          #+#    #+#             */
/*   Updated: 2021/06/29 19:29:03 by junghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void		print_cmd(t_cmd *cmd)
{
	int		idx;
	t_list	*rd_lst;
	t_redir	*rd;

	idx = 0;
	write(2, "+=========================+\n\n", 29);
	while (cmd->argv[idx])
	{
		write(2, "      argv[", 11);
		write(2, ft_itoa(idx), ft_strlen(ft_itoa(idx)));
		write(2, "] : ", 4);
		write(2, cmd->argv[idx], ft_strlen(cmd->argv[idx]));
		write(2, "$\n", 2);
		idx++;
	}
	write(2, "         flag", 13);
	write(2, " : ", 3);
	write(2, ft_itoa(cmd->flag), ft_strlen(ft_itoa(cmd->flag)));
	write(2, "$\n\n", 3);
	if (cmd->rd_lst)
	{
		rd_lst = cmd->rd_lst->next;
		idx = 0;
		while (rd_lst)
		{
			rd = rd_lst->content;
			write(2, "    rd[", 7);
			write(2, ft_itoa(idx), ft_strlen(ft_itoa(idx)));
			write(2, "]sign : ", 8);
			write(2, ft_itoa(rd->sign), ft_strlen(ft_itoa(rd->sign)));
			write(2, "$\n", 2);
			write(2, "    rd[", 7);
			write(2, ft_itoa(idx), ft_strlen(ft_itoa(idx)));
			write(2, "]name : ", 8);
			write(2, rd->file_name, ft_strlen(rd->file_name));
			write(2, "$\n\n", 3);
			idx++;
			rd_lst = rd_lst->next;
		}
	}
	write(2, "+=========================+\n", 28);
}

int			count_pipe(t_list *list)
{
	t_cmd	*cmd;
	int		ret;

	ret = 0;
	while (list)
	{
		cmd = list->content;
		if (cmd->flag == 1)
			ret++;
		else
			return (ret);
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
		ft_exit(cmd);
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
				write(2, "minish: ", 8);
				write(2, rd->file_name, ft_strlen(rd->file_name));
				err_msg_print(": No such file or directory\n", 1);
				break ;
			}
		}
		else if (rd->sign == 1 || rd->sign == 2)
		{
			if (cmd->rd_fd[1] > 0)
				close(cmd->rd_fd[1]);
			if (rd->sign == 1)
				cmd->rd_fd[1] = open(rd->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
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
	if (*(cmd->argv) && cmd->rd_fd[0] >= 0)
		ft_execve(cmd, pipe_flag);
	if (cmd->rd_lst)
	{
		if (cmd->rd_fd[1])
			dup2(temp_fd[1], 1);
		if (cmd->rd_fd[0])
			dup2(temp_fd[0], 0);
	}
}

void		lets_fork(pid_t *pid, t_cmd *cmd, t_cmd *next_cmd, int idx)
{
	*pid = fork();
	if (*pid < 0)
		write(2, "\n", 6);
	else if (*pid == 0)
	{
		if (cmd->flag == 1)
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

void		execute_cmd(t_list *cmd_root)
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
		if (cmd->flag == 1)
		{
			pipe_cnt = count_pipe(temp);
			pid = (int *)malloc(sizeof(pid_t) * (pipe_cnt + 1));
			while (cmd->flag == 1)
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
				lets_fork(&pid[idx], cmd, next_cmd, idx);
				temp = temp->next;
				cmd = temp->content;
			}
			if (cmd->flag == 0)
			{
				idx++;
				lets_fork(&pid[idx], cmd, next_cmd, idx);
				while (idx >= 0)
				{
					waitpid(pid[pipe_cnt - idx], &g_archive.exit_stat, 0);
					idx--;
				}
			}
			free(pid);
		}
		else
			builtin(cmd, 0);
		temp = temp->next;
	}
}
