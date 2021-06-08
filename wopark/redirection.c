#include "../includes/minish.h"

void	init_redir(t_redir *rd)
{
	rd = (t_redir *)malloc(sizeof(t_redir));
	rd->sign = 0;
	rd->file_name = 0;
}

// void	check_redirection(char *input, t_data *data)
// {
// 	if (input[data->input_idx] == '>')

// }
