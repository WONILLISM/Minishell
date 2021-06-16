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
	data->rd = (t_redir *)malloc(sizeof(t_redir));
	data->rd->file_name = 0;
	data->rd->sign = 0;
	data->rd_buf_idx = 0;
}

void	update_redir(t_data *data)
{
	int		i;

	i = 0;
	data->rd->file_name = ft_strtrim(data->rd_buf, " ");
	while (data->rd->file_name[i])
	{
		if (data->rd->file_name[i] == -1)
			data->rd->file_name[i] = ' ';
		i++;
	}
	free(data->rd_buf);
	data->rd_buf = ft_calloc(sizeof(char), data->buf_size);
	data->rd_buf_idx = 0;
	ft_lstadd_back(&data->cmd->rd_lst, ft_lstnew(data->rd));
	ft_lstlast(data->cmd->rd_lst)->next = NULL;
	init_redir(data);
}

void	chk_redir_sign(char *input, t_data *data)
{
	if (input[data->input_idx] == '>')
	{
		if (data->rd->sign == 0 || (data->rd->sign == 1 && !*data->rd_buf))
			data->rd->sign++;
		else if ((data->rd->sign == 2 || data->rd->sign == 1) && *data->rd_buf)
		{
			update_redir(data);
			data->input_idx--;
		}
		else if (data->rd->sign == -1 && *data->rd_buf)
		{
			update_redir(data);
			data->input_idx--;
		}
		else
			printf("ERROR\n");
	}
	else if (input[data->input_idx] == '<')
	{
		if (data->rd->sign == 0)
			data->rd->sign--;
		else if (data->rd->sign == -1 && *data->rd_buf)
			update_redir(data);
		else if ((data->rd->sign == 2 || data->rd->sign == 1) && *data->rd_buf)
			update_redir(data);
		else
			printf("ERROR\n");
	}
	else
		printf("error\n");
}
