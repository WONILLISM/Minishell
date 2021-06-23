#include "../includes/minish.h"

int		parse_envv_handler(t_data *data, char *input)
{
	t_list	*envlst;
	t_env	*env_content;
	char	*tmp;
	char	*buf_tmp;
	int		len;

	data->input_idx++;
	if (chk_question_mark(data, input))
		return (0);
	len = chk_var_name(data, input);
	if (!len)
		return (-1);
	tmp = ft_strndup(input + data->input_idx, len);
	data->input_idx += len - 1;
	envlst = get_curr_envv_lst(tmp);
	if (!envlst)
		return (-1);
	env_content = envlst->content;
	len = ft_strlen(env_content->value);
	if ((int)ft_strlen(tmp) < len)
		data->buf_size += len;
	buf_tmp = ft_strjoin(data->buf, env_content->value);
	free(data->buf);
	data->buf = buf_tmp;
	data->buf_idx = ft_strlen(buf_tmp);
	return (0);
}

void	parse_get_data2(char *input, t_data *data)
{
	if (data->cmd->quote && input[data->input_idx] == ' ')
		input[data->input_idx] = -1;
	if (data->cmd->quote != '\'' && input[data->input_idx] == '\\' && input[data->input_idx + 1])
	{
		if (data->cmd->quote == '\"' && ft_strchr("$`\"\\", input[data->input_idx + 1]))
			data->input_idx++;
		if (data->cmd->quote == 0)
			data->input_idx++;
		if (input[data->input_idx] == ' ')
			input[data->input_idx] = -1;
	}
	if (data->rd->sign && input[data->input_idx] != ' ')
		data->rd_buf[data->rd_buf_idx++] = input[data->input_idx];
	else
		data->buf[data->buf_idx++] = input[data->input_idx];
}

int		parse_get_data(char *input, t_data *data, t_list *cmd_root)
{
	if (data->cmd->quote == input[data->input_idx])
		data->cmd->quote = 0;
	else if (data->cmd->quote == 0 && *data->rd_buf && input[data->input_idx] == ' ')
		update_redir(data);
	else if (data->cmd->quote == 0 && input[data->input_idx] == '\"')
		data->cmd->quote = input[data->input_idx];
	else if (data->cmd->quote == 0 && input[data->input_idx] == '\'')
		data->cmd->quote = input[data->input_idx];
	else if (data->cmd->quote == 0 && input[data->input_idx] == ';')
		return (lst_add_cmd(data, cmd_root, input, 0));
	else if (data->cmd->quote == 0 && input[data->input_idx] == '|')
		return (lst_add_cmd(data, cmd_root, input, 1));
	else if (data->cmd->quote != '\'' && input[data->input_idx] == '$')
		return parse_envv_handler(data, input);
	else if (data->cmd->quote == 0 && ft_strchr("><", input[data->input_idx]))
		chk_redir_sign(input, data);
	else
		parse_get_data2(input, data);
	return (0);
}

int		free_rdlst(t_list *rd_lst)
{
	t_list	*tmp;
	t_redir	*rd;

	tmp = rd_lst->next;
	while (tmp)
	{
		rd = rd_lst->content;
		free(rd->file_name);
		tmp = tmp->next;
	}
	return (0);
}

int		free_cmd(t_cmd *cmd)
{
	int		i;

	i = 0;
	if (cmd->argv)
	{
		while (cmd->argv[i])
			free(cmd->argv[i++]);
	}
	free(cmd->argv);
	free_rdlst(cmd->rd_lst);
	free(cmd->rd_lst);
	return (0);
}

int		free_data(t_data *data, t_list *cmd_root)
{
	t_list	*cmdlst;

	free(data->buf);
	free_cmd(data->cmd);
	free(data->rd->file_name);
	free(data->rd);
	free(data->rd_buf);

	cmdlst = cmd_root->next;
	while (cmdlst)
	{
		free_cmd(cmdlst->content);
		cmdlst = cmdlst->next;
	}
	free(cmd_root);
	// free(cmdlst);
	return (0);
}
// ; 만왔을 때 에러처리
// " 따옴표 안닫혔을 때 에러처리
int		parse_input(char *input)
{
	t_data	data;
	t_list	*cmd_root;
	char	*input_tmp;

	g_archive.parse_error = 1;
	g_archive.buf = data.buf;
	if (input)
	{
		input_tmp = ft_strltrim(input, " ");
		parse_init(&data, cmd_root, ft_strlen(input));
		while (input_tmp[++data.input_idx])
		{
			g_archive.parse_error = parse_get_data(input_tmp, &data, cmd_root);
			if (g_archive.parse_error == -1)
				break;
		}
		free(input_tmp);
		if (*(data.buf))
			g_archive.parse_error = lst_add_cmd(&data, cmd_root, input, 0);
		// system("leaks minishell");
		if (data.rd->sign)
			g_archive.parse_error = lst_add_cmd(&data, cmd_root, input, 2);
		if (parse_error_check(&data) == ERROR)
			return (ERROR);
		// else
		// 	execute_builtin(cmd_root);

		// t_list	*tcmdl;

		free_data(&data, cmd_root);
		// tcmdl = cmd_root->next;
		// while (tcmdl)
		// {
		// 	t_cmd *tcmd = tcmdl->content;
		// 	t_list *trdl = tcmd->rd_lst;
		// 	for (int i = 0; tcmd->argv[i]; i++)
		// 		printf("argv[%d] : %s\n", i, tcmd->argv[i]);
		// 	redir_list_view(trdl);
		// 	tcmdl = tcmdl->next;
		// 	printf("--------------\n");
		// }
	}
	return (SUCCESS);
}
