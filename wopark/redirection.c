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

void	update_redir(t_data *data, t_list **cmd_root)
{
	t_cmd	*tmp_cmd;
	t_redir	*tmp_rd;
	int		i;

	(void)cmd_root;
	tmp_cmd = data->last_node->content;
	tmp_rd = (t_redir *)malloc(sizeof(t_redir));
	tmp_rd->sign = data->rd.sign;
	// if (data->rd.sign && data->rd_buf[0] == 0)
	// {
	// 	g_archive.parse_error = ERROR;
	// 	return ;
	// }
	tmp_rd->file_name = ft_strtrim(data->rd_buf, " ");
	free(data->rd_buf);
	i = 0;
	while (tmp_rd->file_name[i])
	{
		if (tmp_rd->file_name[i] == -1)
			tmp_rd->file_name[i] = ' ';
		i++;
	}
	data->rd_buf = ft_calloc(sizeof(char), data->buf_size);
	data->rd_buf_idx = 0;
	data->rd.sign = 0;
	ft_lstadd_back(&tmp_cmd->rd_lst, ft_lstnew(tmp_rd));
	data->rd.file_name = 0;
	data->rd.sign = 0;
}

void	chk_redir_sign(char *input, t_data *data, t_list **cmd_root)
{
	if (input[data->input_idx] == '>')
	{
		if (data->rd.sign == 0 || (data->rd.sign == 1 && !*data->rd_buf))
			data->rd.sign++;
		else if ((data->rd.sign == 2 || data->rd.sign == 1) && *data->rd_buf)
		{
			update_redir(data, cmd_root);
			data->input_idx--;
		}
		else if (data->rd.sign == -1 && *data->rd_buf)
		{
			update_redir(data, cmd_root);
			data->input_idx--;
		}
		else
			printf("ERROR\n");
	}
	else if (input[data->input_idx] == '<')
	{
		if (data->rd.sign == 0)
			data->rd.sign--;
		else if ((data->rd.sign == 2 || data->rd.sign == 1) && *data->rd_buf)
		{
			update_redir(data, cmd_root);
			data->input_idx--;
		}
		else if (data->rd.sign == -1 && *data->rd_buf)
		{
			update_redir(data, cmd_root);
			data->input_idx--;
		}
		else
			printf("ERROR\n");
	}
	else
		printf("error\n");
}
