#include "../includes/minish.h"

int		chk_question_mark(t_data *data, char *input)
{
	char	*buf_tmp;
	char	*tmp;

	if (input[data->input_idx] != '?')
		return (0);
	tmp = ft_itoa(g_archive.exit_stat);
	buf_tmp = ft_strjoin(data->buf, tmp);
	free(tmp);
	free(data->buf);
	data->buf = buf_tmp;
	data->buf_idx = ft_strlen(buf_tmp);
	return (1);
}

int		chk_var_name(t_data *data, char *input, int *len)
{
	char	c;

	*len = 0;
	c = *(input + data->input_idx);
	if (*len == 0 && ft_isdigit(c))
		return (1);
	while (c == '_' || ft_isalnum(c))
	{
		(*len)++;
		c = *(input + data->input_idx + *len);
	}
	if (*len == 0)
		return (0);
	return (1);
}

// t_list	*tcmdl;
		// int	j;

		// tcmdl = cmd_root->next;
		// j = 0;
		// while (tcmdl)
		// {
		// 	t_cmd *tcmd = tcmdl->content;
		// 	t_list *trdl = tcmd->rd_lst;
		// 	if (tcmd->argv){
		// 		printf("-------idx %d-------\n", j);
		// 		printf("flag : %d\n", tcmd->flag);
		// 		for (int i = 0; tcmd->argv[i]; i++)
		// 			printf("argv[%d] : %s\n", i, tcmd->argv[i]);
		// 	}
		// 	redir_list_view(trdl);
		// 	j++;
		// 	tcmdl = tcmdl->next;
		// }
