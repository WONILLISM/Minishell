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

int		chk_var_name(t_data *data, char *input)
{
	char	c;
	int		len;

	len = 0;
	c = *(input + data->input_idx);
	if (len == 0 && ft_isdigit(c))
		return (0);
	while (c == '_' || ft_isalnum(c))
	{
		(len)++;
		c = *(input + data->input_idx + len);
	}
	if (len == 0)
	{
		data->buf[data->buf_idx++] = input[data->input_idx - 1];
		return (-1);
	}
	return (len);
}

int		clensing_env_name(t_data *data, char *input, int len)
{
	t_list	*envlst;
	t_env	*env_content;
	char	*buf_tmp;
	char	*tmp;

	tmp = ft_strndup(input + data->input_idx, len);
	data->input_idx += len - 1;
	envlst = get_curr_envv_lst(tmp);
	if (!envlst)
	{
		free(tmp);
		return (0);
	}
	env_content = envlst->content;
	len = ft_strlen(env_content->value);
	if ((int)ft_strlen(tmp) < len)
		data->buf_size += len;
	free(tmp);
	buf_tmp = ft_strjoin(data->buf, env_content->value);
	free(data->buf);
	data->buf = buf_tmp;
	data->buf_idx = ft_strlen(buf_tmp);
	return (0);
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
