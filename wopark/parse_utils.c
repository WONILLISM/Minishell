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
	data->buf = ft_calloc(data->buf_size, sizeof(char));
}


int		clensing_data_buf(t_data *data, t_list **cmd_root, int flag)
{
	t_cmd	*tmp_cmd;
	char	*tmp;

	(void)cmd_root;
	tmp_cmd = data->last_node->content;
	tmp = ft_strltrim(data->buf, " ");
	free(data->buf);
	tmp_cmd->argv = ft_split(tmp, ' ');
	free(tmp);
	chk_space_flag(tmp_cmd->argv);
	if (flag == -1)
		flag = 0;
	tmp_cmd->flag = flag;
	tmp_cmd->fd[0] = 0;
	tmp_cmd->fd[1] = 0;
	tmp_cmd->rd_fd[0] = 0;
	tmp_cmd->rd_fd[1] = 0;
	data->cmd.flag = flag;
	init_cmd(data);
	return (0);
}


/*
** 초기 상태 : cmd 리스트에 빈 cmd 컨텐츠 추가
** 만약 ; | 개행이 오면 cmd 리스트에 새로운 빈 cmd 추가
*/
void	new_cmdlst_addback(t_data *data, t_list **cmd_root)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	ft_lstadd_back(cmd_root, ft_lstnew(tmp_cmd));
	tmp_cmd->rd_lst = ft_lstnew(NULL);
	data->last_node = ft_lstlast(*cmd_root);
	data->last_node->next = NULL;
}

int		lst_add_cmd(t_data *data, t_list **cmd_root, int flag)
{
	// 만약 ; | 일 때
	if (flag == 0 || flag == 1 || flag == -1)
	{
		if (data->rd.sign)
			update_redir(data, cmd_root);
		clensing_data_buf(data, cmd_root, flag);
		if (flag == 0 || flag == 1)
		{
			new_cmdlst_addback(data, cmd_root);
			data->buf = ft_calloc(data->buf_size, sizeof(char));
			data->buf_idx = 0;
		}
		else
			free(data->rd_buf);
		init_cmd(data);
	}
	return (SUCCESS);
}
