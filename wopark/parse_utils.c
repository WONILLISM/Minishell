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

void	view_cmd_list(t_list *lst)
{
	t_list	*tmp;

	tmp = lst->next;
	while (tmp)
	{
		t_cmd	*tmpc = tmp->content;
		printf("%s\n", tmpc->argv[0]);
		tmp = tmp->next;
	}
}

void	view_rd_list(t_list *lst)
{
	t_list	*tmp;

	tmp = lst->next;
	while (tmp)
	{
		t_redir	*tmpr = tmp->content;
		printf("%s\n", tmpr->file_name);
		tmp = tmp->next;
	}
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

int		lst_add_cmd(t_data *data, t_list *cmd_root, int flag)
{
	char	*tmp;

	if (flag == 2 || data->rd->sign)
		update_redir(data);
	tmp = ft_strltrim(data->buf, " ");
	free(data->buf);
	data->buf = tmp;
	data->cmd->argv = ft_split(data->buf, ' ');
	chk_space_flag(data->cmd->argv);
	data->cmd->flag = flag;
	ft_lstadd_back(&cmd_root, ft_lstnew(data->cmd));
	// free(data->cmd);
	init_cmd(data);
	update_data(data, cmd_root);
	return (SUCCESS);
}

