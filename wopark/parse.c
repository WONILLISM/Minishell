#include "../includes/minish.h"

void	parse_init(char *input, t_data *data, t_list **cmd_root)
{
	*cmd_root = ft_lstnew(NULL);
	data->last_node = *cmd_root;
	data->cmd = malloc(sizeof(t_cmd));
	data->cmd->argv = 0;
	data->cmd->flag = 0;
	data->cmd->quote = 0;
	data->buf = ft_calloc(ft_strlen(input)+ 1, sizeof(char));

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

void	lst_add_cmd(t_data *data, t_list *cmd_root, int flag, char *input)
{
	if (data->buf[0] == ' ')
		data->buf++;
	data->cmd->argv = ft_split(data->buf, ' ');
	chk_space_flag(data->cmd->argv);
	data->cmd->flag = flag;
	if (!(data->cmd->argv)[0] && flag >= 0)
		write(1,"error\n", 1);
	else
	{
		ft_lstadd_back(&cmd_root, ft_lstnew(data->cmd));
		data->cmd = ft_calloc(1, sizeof(t_cmd));
		data->last_node = ft_lstlast(cmd_root);
		data->last_node->next = 0;
	}
	data->buf_idx = 0;
	free(data->buf);
	data->buf = ft_calloc(ft_strlen(input), sizeof(char));
}

int		chk_val_name(char c)
{
	if (c == '_')
		return (1);
	return ft_isalnum((int)c);
}

void	envv_handler(t_data *data, char *input)
{
	char	*tmp;
	int		idx;
	int		len;

	idx = data->input_idx + 1;
	len = 0;
	while (chk_val_name(input[idx]))
	{
		printf("%d: %c\n", len, input[idx]);
		idx++;
		len++;
	}
	printf("len: %d\n", len);
	tmp = ft_strndup(input + data->input_idx + 1, len - 1);
	tmp[len] = 0;
	printf("!!!%s!!!\n", tmp);
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
		lst_add_cmd(data, cmd_root, 0, input);
	else if (data->cmd->quote == 0 && input[data->input_idx] == '|')
		lst_add_cmd(data, cmd_root, 1, input);
	else if (data->cmd->quote != '\'' && input[data->input_idx] == '$')
		envv_handler(data, input);
	else
	{
		if (data->cmd->quote != '\'' && input[data->input_idx] == '\\' && input[data->input_idx + 1])
		{
			if (data->cmd->quote == '\"' && ft_strchr("$`\"\\", input[data->input_idx + 1]))
				data->input_idx++;
			if (data->cmd->quote == 0 && ft_strchr("$`\"\\\'", input[data->input_idx + 1]))
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

	input_tmp = ft_strtrim(input, " ");
	parse_init(input_tmp, &data, &cmd_root);
	while (input_tmp[++data.input_idx])
	{
		get_parse_data(input_tmp, &data, cmd_root);
	}
	free(input_tmp);
	if (*(data.buf))
		lst_add_cmd(&data, cmd_root, 0, input_tmp);
	execute_builtin(cmd_root);
	return (0);
}
