#include "../includes/minish.h"

// void	init_data(t_data *data, t_list **cmd_root, int input_size)
// {
// 	*cmd_root = ft_lstnew(NULL);
// 	data->buf_idx = 0;
// 	data->rd_buf_idx = 0;
// 	data->input_idx = -1;
// 	data->buf_size = input_size + 1;
// 	data->buf = ft_calloc(data->buf_size, sizeof(char));
// 	data->rd_buf = ft_calloc(data->buf_size, sizeof(char));
// 	data->last_node = ft_lstlast(*cmd_root);
// 	data->last_node->next = NULL;
// }

void	init_cmd(t_data *data)
{
	data->cmd.argv = NULL;
	data->cmd.flag = 0;
	data->cmd.quote = 0;
	data->cmd.fd[0] = 0;
	data->cmd.fd[1] = 0;
}

void	parse_init(t_data *data, t_list **cmd_root, int input_size)
{
	*cmd_root = ft_lstnew(NULL);
	data->buf_size = input_size + 1;
	data->buf = ft_calloc(data->buf_size, sizeof(char));
	data->rd_buf = ft_calloc(data->buf_size, sizeof(char));
	data->buf_idx = 0;
	data->rd_buf_idx = 0;
	data->input_idx = -1;
	data->last_node = ft_lstlast(*cmd_root);
	data->last_node->next = NULL;
	data->cmd.argv = NULL;
	data->cmd.flag = 0;
	data->cmd.quote = 0;
	data->rd.file_name = NULL;
	data->rd.sign = 0;
	data->rd_buf_idx = 0;
}

