#include "../includes/minish.h"

void	redir_list_view(t_list *lst)
{
	t_redir *tmp;

	lst = lst->next;
	while (lst)
	{
		tmp = lst->content;
		printf("sign : %d, filename: %s\n", tmp->sign, tmp->file_name);
		lst = lst->next;
	}
}

void	init_redir(t_data *data)
{
	char	*tmp;

	data->rd = (t_redir *)malloc(sizeof(t_redir));
	data->rd->sign = data->cmd->rd_flag;
	data->rd_buf[data->rd_buf_idx + 1] = 0;
	tmp = ft_strdup(data->rd_buf);
	data->rd->file_name = ft_strtrim(tmp, " ");
	free(tmp);
	free(data->rd_buf);
	ft_lstadd_back(&data->cmd->rd_lst, ft_lstnew(data->rd));
	ft_lstlast(data->cmd->rd_lst)->next = 0;
	data->cmd->rd_flag = 0;
	data->rd_buf = ft_calloc(data->buf_size, sizeof(char));
	data->rd_buf_idx = 0;
	data->input_idx--;
	// redir_list_view(data->cmd->rd_lst);
}

void	chk_redir_sign(char *input, t_data *data)
{
	if (input[data->input_idx] == '>')
	{
		if (data->cmd->rd_flag == 0 || (data->cmd->rd_flag == 1 && !*data->rd_buf))
			data->cmd->rd_flag++;
		else if ((data->cmd->rd_flag == 2 || data->cmd->rd_flag == 1) && *data->rd_buf)
			init_redir(data);
		else if (data->cmd->rd_flag == -1 && *data->rd_buf)
			init_redir(data);
		else
			printf("ERROR\n");
	}
	else if (input[data->input_idx] == '<')
	{
		if (data->cmd->rd_flag == 0)
			data->cmd->rd_flag--;
		else if (data->cmd->rd_flag == -1 && *data->rd_buf)
			init_redir(data);
		else if ((data->cmd->rd_flag == 2 || data->cmd->rd_flag == 1) && *data->rd_buf)
			init_redir(data);
		else
			printf("ERROR\n");
	}
	else
		printf("error\n");
}

void	chk_redir_filename(char *input, t_data *data)
{
	if (*data->rd_buf && data->cmd->quote == 0 && input[data->input_idx] == ' ')
	{
		init_redir(data);
		data->input_idx++;
	}
	else
		data->rd_buf[data->rd_buf_idx++] = input[data->input_idx];
}
