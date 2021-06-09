#include "../includes/minish.h"

void	init_redir(t_redir *rd, t_data *data)
{
	rd = (t_redir *)malloc(sizeof(t_redir));
	data->rd->file_name = ft_calloc(data->buf_size, sizeof(char));
	rd->sign = 0;
}

void	chk_redir_sign(char *input, t_data *data)
{
	if (input[data->input_idx] == '>' && data->rd->sign >= 0 && data->rd->sign <= 1)
	{
		printf("!!!");
		data->rd->sign++;
	}
	else if (input[data->input_idx] == '<' && data->rd->sign == 0)
		data->rd->sign--;
	// if (input[data->input_idx + 1])
	// 	data->input_idx++;
}

void	chk_redir_filename(char *input, t_data *data)
{
	if (ft_strchr("><|; ", input[data->input_idx + 1]))
	{
		ft_lstadd_back(&data->cmd->rd_lst, ft_lstnew(data->rd));
		init_redir(data->rd, data);
	}
	data->rd->file_name[data->rd->idx++] = input[data->input_idx];
}
