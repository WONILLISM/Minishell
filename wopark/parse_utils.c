#include "../includes/minish.h"

void	chk_space_flag(char **strs)
{
	int i;
	int j;

	i = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == -1)
				strs[i][j] = ' ';
			j++;
		}
		i++;
	}
}

int		chk_question_mark(t_data *data, char *input)
{
	char	*buf_tmp;
	char	*tmp;

	if (input[data->input_idx] != '?')
		return (0);
	tmp = ft_itoa(g_archive.exit_stat);
	buf_tmp = ft_strjoin(data->buf, tmp);
	free(tmp);
	free(data->buf);
	data->buf = buf_tmp;
	data->buf_idx = ft_strlen(buf_tmp);
	return (1);
}

int		chk_var_name(t_data *data, char *input)
{
	int		ret;
	char	c;

	ret = 0;
	c = *(input + data->input_idx);
	if (ret == 0 && ft_isdigit(c))
		return (1);
	while (c == '_' || ft_isalnum(c))
	{
		ret++;
		c = *(input + data->input_idx + ret);
	}
	return (ret);
}

void	update_data(t_data *data, t_list *cmd_root)
{
	data->last_node = ft_lstlast(cmd_root);
	data->last_node->next = NULL;
	data->buf_idx = 0;
	free(data->buf);
	// 구조체 free
	data->buf = ft_calloc(data->buf_size, sizeof(char));
}


int		clensing_data_buf(t_data *data, t_list *cmd_root, int flag)
{
	t_cmd	*tmp_cmd;
	char	*tmp;

	tmp_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	tmp = ft_strltrim(data->buf, " ");
	ft_lstadd_back(&cmd_root, ft_lstnew(tmp_cmd));
	data->last_node = ft_lstlast(cmd_root);
	tmp_cmd->rd_lst = ft_lstnew(NULL);
	tmp_cmd->argv = ft_split(tmp, ' ');
	free(tmp);
	chk_space_flag(tmp_cmd->argv);
	tmp_cmd->flag = flag;
	tmp_cmd->fd[0] = 0;
	tmp_cmd->fd[1] = 0;
	tmp_cmd->rd_fd[0] = 0;
	tmp_cmd->rd_fd[1] = 0;
	data->cmd.flag = flag;
	return (0);
}

int		lst_add_cmd(t_data *data, t_list *cmd_root, char *input, int flag)
{
	(void)input;
	clensing_data_buf(data, cmd_root, flag);
	free(data->buf);
	data->buf = NULL;
	if (flag == 2 || data->rd.sign)
		update_redir(data);
	free(data->rd_buf);
	data->rd_buf = NULL;
	if (flag == 1 || flag == 0)
	{
		data->buf = ft_calloc(data->buf_size, sizeof(char));
		data->rd_buf = ft_calloc(data->buf_size, sizeof(char));
	}
	// system("leaks minishell");
	// if (flag != -1)
	// 	data->buf = ft_calloc(data->buf_size, sizeof(char));
	data->buf_idx = 0;
	// tmp = ft_strltrim(data->buf, " ");
	// free(data->buf);
	// data->buf = tmp;
	// data->cmd->argv = ft_split(data->buf, ' ');
	// chk_space_flag(data->cmd->argv);
	// data->cmd->flag = flag;
	// ft_lstadd_back(&cmd_root, ft_lstnew(data->cmd));
	// system("leaks minishell");
	// init_cmd(data);
	// update_data(data, cmd_root);
	return (SUCCESS);
}
