/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghwki <junghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:24:40 by junghwki          #+#    #+#             */
/*   Updated: 2021/06/30 08:35:00 by junghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int			ft_strcmp(const char *s1, const char *s2)
{
	int		idx;

	idx = 0;
	while (s1[idx] || s2[idx])
	{
		if ((s1[idx] != s2[idx]) || (s1[idx] == '\0') || (s2[idx] == '\0'))
			return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
		idx++;
	}
	return (0);
}

void		envv_content_del(t_env *content)
{
	free(content->key);
	free(content->value);
	free(content);
}

t_list		*get_curr_envv_lst(char *key_value)
{
	t_list	*temp;
	t_env	*temp_env;

	temp = g_archive.envv_lst->next;
	while (temp)
	{
		temp_env = temp->content;
		if (ft_strcmp(temp_env->key, key_value) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void		free_array(char **array)
{
	int		idx;

	idx = 0;
	while (array[idx])
	{
		free(array[idx]);
		idx++;
	}
	free(array);
}

t_env		*env_dup(t_env *content)
{
	t_env	*ret;

	ret = (t_env *)malloc(sizeof(t_env));
	ret->key = ft_strdup(content->key);
	if (content->value)
		ret->value = ft_strdup(content->value);
	else
		ret->value = NULL;
	return (ret);
}


void		print_cmd(t_cmd *cmd)
{
	int		idx;
	t_list	*rd_lst;
	t_redir	*rd;

	idx = 0;
	write(2, "+=========================+\n\n", 29);
	while (cmd->argv[idx])
	{
		write(2, "      argv[", 11);
		write(2, ft_itoa(idx), ft_strlen(ft_itoa(idx)));
		write(2, "] : ", 4);
		write(2, cmd->argv[idx], ft_strlen(cmd->argv[idx]));
		write(2, "$\n", 2);
		idx++;
	}
	write(2, "         flag", 13);
	write(2, " : ", 3);
	write(2, ft_itoa(cmd->flag), ft_strlen(ft_itoa(cmd->flag)));
	write(2, "$\n\n", 3);
	if (cmd->rd_lst)
	{
		rd_lst = cmd->rd_lst->next;
		idx = 0;
		while (rd_lst)
		{
			rd = rd_lst->content;
			write(2, "    rd[", 7);
			write(2, ft_itoa(idx), ft_strlen(ft_itoa(idx)));
			write(2, "]sign : ", 8);
			write(2, ft_itoa(rd->sign), ft_strlen(ft_itoa(rd->sign)));
			write(2, "$\n", 2);
			write(2, "    rd[", 7);
			write(2, ft_itoa(idx), ft_strlen(ft_itoa(idx)));
			write(2, "]name : ", 8);
			write(2, rd->file_name, ft_strlen(rd->file_name));
			write(2, "$\n\n", 3);
			idx++;
			rd_lst = rd_lst->next;
		}
	}
	write(2, "+=========================+\n", 28);
}
