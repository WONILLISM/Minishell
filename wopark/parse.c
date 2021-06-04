#include "../includes/minish.h"

void	parse_init(char *input, t_data *data, t_list **cmd_root)
{
	*cmd_root = ft_lstnew(NULL);
	data->last_node = *cmd_root;
	data->cmd = malloc(sizeof(t_cmd));
	data->cmd->argv = 0;
	data->cmd->flag = 0;
	data->cmd->quote = 0;
	data->cmd->fd[0] = 0;
	data->cmd->fd[1] = 0;
	data->buf_size = ft_strlen(input) + 1;
	data->buf = ft_calloc(data->buf_size, sizeof(char));
	data->input_idx = -1;
	data->cmd_idx = 0;
	data->buf_idx = 0;
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
		data->cmd->redir = 1;
	else if (data->cmd->quote != '\''
	&& input[data->input_idx] == '\\' && input[data->input_idx + 1])
	{
		if (data->cmd->quote == '\"'
		&& ft_strchr("$`\"\\", input[data->input_idx + 1]))
			data->input_idx++;
		if (data->cmd->quote == 0)
			data->input_idx++;
		if (input[data->input_idx] == ' ')
			input[data->input_idx] = -1;
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
	else if (data->cmd->quote != 0 && input[data->input_idx] == ' ')
		data->buf[data->buf_idx++] = -1;
	else if (data->cmd->quote == 0 && input[data->input_idx] == ';')
		g_archive.parse_error = lst_add_cmd(data, cmd_root, 0);
	else if (data->cmd->quote == 0 && input[data->input_idx] == '|')
		g_archive.parse_error = lst_add_cmd(data, cmd_root, 1);
	else if (data->cmd->quote != '\'' && input[data->input_idx] == '$')
		parse_envv_handler(data, input);
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
	input_tmp = NULL;
	if (input)
		input_tmp = ft_strltrim(input, " ");
	parse_init(input_tmp, &data, &cmd_root);
	while (input_tmp[++data.input_idx])
	{
		parse_get_data(input_tmp, &data, cmd_root);
		if (g_archive.parse_error < 1)
		{
			free(input_tmp);
			return (ERROR);
		}
	}
	free(input_tmp);
	if (*(data.buf))
		g_archive.parse_error = lst_add_cmd(&data, cmd_root, 0);
	// system("leaks minish");
	if (g_archive.parse_error == 1)
	{
		execute_builtin(cmd_root);
		// system("leaks minish");
	}
	else if (g_archive.parse_error < 0)
		return (ERROR);
	return (SUCCESS);
}
