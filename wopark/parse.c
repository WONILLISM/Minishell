#include "../includes/minish.h"

void	init_data(t_data *data, t_list **cmd_root, int input_size)
{
	*cmd_root = ft_lstnew(NULL);
	data->buf_idx = 0;
	data->cmd_idx = 0;
	data->rd_buf_idx = 0;
	data->input_idx = -1;
	data->buf_size = input_size + 1;
	data->buf = ft_calloc(data->buf_size, sizeof(char));
	data->rd_buf = ft_calloc(data->buf_size, sizeof(char));
	data->last_node = ft_lstlast(*cmd_root);
	data->last_node->next = NULL;
}

void	init_cmd(t_data *data)
{
	data->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	data->cmd->argv = 0;
	data->cmd->flag = 0;
	data->cmd->quote = 0;
	data->cmd->fd[0] = 0;
	data->cmd->fd[1] = 0;
	data->cmd->rd_lst = ft_lstnew(NULL);
	init_redir(data);
}

void	parse_envv_handler(t_data *data, char *input)
{
	t_list	*envlst;
	t_env	*env_content;
	char	*tmp;
	char	*buf_tmp;
	int		len;

	data->input_idx++;
	if (chk_question_mark(data, input))
		return ;
	len = chk_var_name(data, input);
	if (!len)
		return ;
	tmp = ft_strndup(input + data->input_idx, len);
	data->input_idx += len - 1;
	envlst = get_curr_envv_lst(tmp);
	if (!envlst)
		return ;
	env_content = envlst->content;
	len = ft_strlen(env_content->value);
	if ((int)ft_strlen(tmp) < len)
		data->buf_size += len;
	buf_tmp = ft_strjoin(data->buf, env_content->value);
	free(data->buf);
	data->buf = buf_tmp;
	data->buf_idx = ft_strlen(buf_tmp);
}

void	parse_get_data2(char *input, t_data *data)
{
	if (data->cmd->quote == 0 && ft_strchr("><", input[data->input_idx]))
	{
		chk_redir_sign(input, data);
		return ;
	}
	else if (data->rd->sign)
	{
		printf("!!!!\n");
		chk_redir_filename(input, data);
		return ;
	}
	else if (data->cmd->quote != '\''
	&& input[data->input_idx] == '\\' && input[data->input_idx + 1])
	{
		if (data->cmd->quote == '\"'
		&& ft_strchr("$`\"\\", input[data->input_idx + 1]))
			data->input_idx++;
		if (input[data->input_idx] == ' ')
			input[data->input_idx] = -1;
		if (data->cmd->quote == 0)
			data->input_idx++;
	}
	data->buf[data->buf_idx++] = input[data->input_idx];
}

void	parse_get_data(char *input, t_data *data, t_list *cmd_root)
{
	if (data->cmd->quote == input[data->input_idx])
		data->cmd->quote = 0;
	else if (data->cmd->quote == 0 && input[data->input_idx] == '\"')
		data->cmd->quote = input[data->input_idx];
	else if (data->cmd->quote == 0 && input[data->input_idx] == '\'')
		data->cmd->quote = input[data->input_idx];
	else if (data->cmd->quote == 0 && input[data->input_idx] == ';')
		g_archive.parse_error = lst_add_cmd(data, cmd_root, 0);
	else if (data->cmd->quote == 0 && input[data->input_idx] == '|')
		g_archive.parse_error = lst_add_cmd(data, cmd_root, 1);
	else if (data->cmd->quote != '\'' && input[data->input_idx] == '$')
		parse_envv_handler(data, input);
	else if (!data->rd->sign && data->cmd->quote && input[data->input_idx] == ' ')
	{
		input[data->input_idx] = -1;
		data->buf[data->buf_idx++] = input[data->input_idx];
	}
	else
		parse_get_data2(input, data);
}

int		parse_input(char *input)
{
	t_data	data;
	t_list	*cmd_root;
	char	*input_tmp;

	g_archive.parse_error = 1;
	g_archive.buf = data.buf;
	if (*input)
	{
		input_tmp = ft_strltrim(input, " ");
		init_data(&data, &cmd_root, ft_strlen(input));
		init_cmd(&data);
		while (input_tmp[++data.input_idx])
		{
			parse_get_data(input_tmp, &data, cmd_root);
			if (g_archive.parse_error == -1)
				break;
		}
		free(input_tmp);
		if (*(data.buf))
			g_archive.parse_error = lst_add_cmd(&data, cmd_root, 0);
		if (data.rd->sign)
			g_archive.parse_error = lst_add_cmd(&data, cmd_root, 2);
		if (parse_error_check(&data) == ERROR)
			return (ERROR);
		// else
		// 	execute_builtin(cmd_root);
		t_list	*tcmdl;

		tcmdl = cmd_root->next;
		while (tcmdl)
		{
			t_cmd *tcmd = tcmdl->content;
			t_list *trdl = tcmd->rd_lst;
			redir_list_view(trdl);
			tcmdl = tcmdl->next;
			printf("--------------\n");
		}
	}
	return (SUCCESS);
}
