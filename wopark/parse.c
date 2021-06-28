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
	if (data->cmd.quote && input[data->input_idx] == ' ')
		input[data->input_idx] = -1;
	if (data->cmd.quote != '\'' && input[data->input_idx] == '\\' && input[data->input_idx + 1])
	{
		if (data->cmd.quote == '\"' && ft_strchr("$`\"\\", input[data->input_idx + 1]))
			data->input_idx++;
		if (data->cmd.quote == 0)
			data->input_idx++;
		if (input[data->input_idx] == ' ')
			input[data->input_idx] = -1;
	}
	if (data->rd.sign && input[data->input_idx] != ' ')
		data->rd_buf[data->rd_buf_idx++] = input[data->input_idx];
	else
		data->buf[data->buf_idx++] = input[data->input_idx];
}

int		parse_get_data(char *input, t_data *data, t_list **cmd_root)
{
	if (data->cmd.quote == input[data->input_idx])
		data->cmd.quote = 0;
	else if (data->cmd.quote == 0 && data->rd.sign && input[data->input_idx] == ' ')
		update_redir(data, cmd_root);
	else if (data->cmd.quote == 0 && input[data->input_idx] == '\"')
		data->cmd.quote = input[data->input_idx];
	else if (data->cmd.quote == 0 && input[data->input_idx] == '\'')
		data->cmd.quote = input[data->input_idx];
	else if (data->cmd.quote == 0 && input[data->input_idx] == ';')
		return (lst_add_cmd(data, cmd_root, 0));
	else if (data->cmd.quote == 0 && input[data->input_idx] == '|')
		return (lst_add_cmd(data, cmd_root, 1));
	else if (data->cmd.quote != '\'' && input[data->input_idx] == '$')
		return parse_envv_handler(data, input);
	else if (data->cmd.quote == 0 && ft_strchr("><", input[data->input_idx]))
		chk_redir_sign(input, data, cmd_root);
	else
		parse_get_data2(input, data);
	return (0);
}

void	free_rd_lst(t_list *rdlst)
{
	t_list	*tmp1;
	t_list	*tmp2;
	t_redir	*tmp_rd;

	tmp1 = rdlst->next;
	tmp2 = rdlst->next;
	while (tmp1)
	{
		tmp_rd = tmp1->content;
		free(tmp_rd->file_name);
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		free(tmp_rd);
		free(tmp2);
	}
	free(rdlst);
}

void	free_cmd_lst(t_list *cmd_root)
{
	t_list	*tmp1;
	t_list	*tmp2;
	t_cmd	*tmp_cmd;
	int		i;

	tmp1 = cmd_root->next;
	while (tmp1)
	{
		tmp_cmd = tmp1->content;
		i = 0;
		if (tmp_cmd->argv)
		{
			while (tmp_cmd->argv[i])
			{
				free(tmp_cmd->argv[i]);
				i++;
			}
			free(tmp_cmd->argv);
		}
		free_rd_lst(tmp_cmd->rd_lst);
		free(tmp_cmd);
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		free(tmp2);
	}
	free(cmd_root);
}

void	print_data_address(t_data *data, t_list *cmd_root)
{
	t_cmd	*cmd = &data->cmd;

	printf("\n==============================\n");
	printf("buf : %p\n",data->buf);
	printf("rd_buf : %p\n",data->rd_buf);
	printf("\n");
	printf("cmd argv : %p\n", cmd->argv);
	printf("rd_lst : %p\n", cmd->rd_lst);
	printf("\n");
	printf("cmd_root : %p\n", cmd_root);
	printf("\n==============================\n");
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
		parse_init(&data, &cmd_root, ft_strlen(input));
		while (input_tmp[++data.input_idx])
		{
			g_archive.parse_error = parse_get_data(input_tmp, &data, &cmd_root);
			if (g_archive.parse_error == -1)
				break;
		}
		free(input_tmp);
		g_archive.parse_error = lst_add_cmd(&data, &cmd_root, -1);
		if (parse_error_check(&data) == ERROR)
			return (ERROR);
		else
			execute_builtin(cmd_root);

		// t_list	*tcmdl;
		// int	j;

		// tcmdl = cmd_root->next;
		// j = 0;
		// while (tcmdl)
		// {
		// 	t_cmd *tcmd = tcmdl->content;
		// 	t_list *trdl = tcmd->rd_lst;
		// 	if (tcmd->argv){
		// 		printf("-------idx %d-------\n", j);
		// 		printf("flag : %d\n", tcmd->flag);
		// 		for (int i = 0; tcmd->argv[i]; i++)
		// 			printf("argv[%d] : %s\n", i, tcmd->argv[i]);
		// 	}
		// 	redir_list_view(trdl);
		// 	j++;
		// 	tcmdl = tcmdl->next;
		// }
		free_cmd_lst(cmd_root);
		// system("leaks minishell");
	}
	return (SUCCESS);
}
