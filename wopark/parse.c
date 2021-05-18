#include "../includes/minish.h"

void	parse_init(char *input, t_data *data, t_list **cmd_root)
{
	*cmd_root = ft_lstnew(NULL);
	data->last_node = *cmd_root;
	data->cmd = malloc(sizeof(t_cmd));
	data->cmd->argv = 0;
	data->cmd->flag = 0;
	data->cmd->quote = 0;
	data->buf_size = ft_strlen(input) + 1;
	data->buf = ft_calloc(data->buf_size, sizeof(char));
	data->input_idx = -1;
	data->cmd_idx = 0;
	data->buf_idx = 0;
}

void	chk_space_flag(char **strs)
{
	int		i;
	int		j;

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

void	lst_add_cmd(t_data *data, t_list *cmd_root, int flag)
{
	char	*tmp;

	tmp = ft_strltrim(data->buf, " ");
	free(data->buf);
	data->buf = tmp;
	data->cmd->argv = ft_split(data->buf, ' ');
	chk_space_flag(data->cmd->argv);
	data->cmd->flag = flag;
	if (!(data->cmd->argv)[0] && flag >= 0)
		write(1,"error\n", 1);
	else
	{
		ft_lstadd_back(&cmd_root, ft_lstnew(data->cmd));
		if (data->cmd->quote)
			printf("ERROR\n");
		data->cmd = ft_calloc(1, sizeof(t_cmd));
		data->last_node = ft_lstlast(cmd_root);
		data->last_node->next = 0;
	}
	data->buf_idx = 0;
	free(data->buf);
	data->buf = ft_calloc(data->buf_size, sizeof(char));
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

void	parse_envv_handler(t_data *data, char *input)
{
	t_list	*envlst;
	t_env	*env_content;
	char	*tmp;
	char	*buf_tmp;
	int		len;

	data->input_idx++;
	len = chk_var_name(data, input);
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

void	get_parse_data(char *input, t_data *data, t_list *cmd_root)
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
		lst_add_cmd(data, cmd_root, 0);
	else if (data->cmd->quote == 0 && input[data->input_idx] == '|')
		lst_add_cmd(data, cmd_root, 1);
	else if (data->cmd->quote != '\'' && input[data->input_idx] == '$')
		parse_envv_handler(data, input);
	else
	{
		if (data->cmd->quote != '\'' && input[data->input_idx] == '\\' && input[data->input_idx + 1])
		{
			if (data->cmd->quote == '\"' && ft_strchr("$`\"\\", input[data->input_idx + 1]))
				data->input_idx++;
			if (data->cmd->quote == 0)
				data->input_idx++;
			if (input[data->input_idx + 1] == ' ')
				input[data->input_idx + 1] = -1;
		}
		data->buf[data->buf_idx++] = input[data->input_idx];
	}
}

int		parse_input(char *input)
{
	t_data	data;
	t_list	*cmd_root;
	char	*input_tmp;

	input_tmp = ft_strltrim(input, " ");
	parse_init(input_tmp, &data, &cmd_root);
	while (input_tmp[++data.input_idx])
	{
		get_parse_data(input_tmp, &data, cmd_root);
	}
	free(input_tmp);
	if (*(data.buf))
		lst_add_cmd(&data, cmd_root, 0);
	execute_builtin(cmd_root);
	return (0);
}
