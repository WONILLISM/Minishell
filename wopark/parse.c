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
				strs[i][j] = '!';
			j++;
		}
		i++;
	}
}

void	lst_add_cmd(t_data *data, t_list *cmd_root, int flag)
{
	char	*buf_tmp;

	buf_tmp = ft_strtrim(data->buf, " ");
	while (*(data->buf))
		*(data->buf)++ = 0;
	data->cmd->argv = ft_split(buf_tmp, ' ');
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
	free(buf_tmp);
}

// "" 안에서 살아야할 기능\`'"$
// '' 모두 문자열로 치환
// 따옴표 없을때 \뒤의 문자만 출력
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
	else
	{
		if (data->cmd->quote != '\'' && input[data->input_idx] == '\\' && input[data->input_idx + 1])
		{
			if (input[data->input_idx + 1] == ' ')
				input[data->input_idx + 1] = -1;
			data->input_idx++;
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
		lst_add_cmd(&data, cmd_root, 0);
	execute_builtin(cmd_root);
	return (0);
}
