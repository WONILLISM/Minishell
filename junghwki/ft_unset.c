/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghwki <junghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:24:21 by junghwki          #+#    #+#             */
/*   Updated: 2021/06/29 18:24:22 by junghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

t_list		*get_prev_envv_lst(char *key_value)
{
	t_list	*ret;
	t_list	*temp;
	t_env	*temp_env;

	temp = g_archive.envv_lst->next;
	ret = g_archive.envv_lst;
	while (temp)
	{
		temp_env = temp->content;
		if (ft_strcmp(temp_env->key, key_value) == 0)
			return (ret);
		temp = temp->next;
		ret = ret->next;
	}
	return (NULL);
}

void		ft_unset(t_cmd *cmd)
{
	t_list	*temp;
	t_list	*del_lst;
	void	(*del)();
	int		idx;

	idx = 0;
	del = envv_content_del;
	while (cmd->argv[idx])
	{
		if (env_key_check(cmd->argv[idx]) < 0)
		{
			g_archive.exit_stat = 1;
			write(2, "minish: unset: `", 16);
			write(2, cmd->argv[idx], ft_strlen(cmd->argv[idx]));
			write(2, "': not a valid identifier\n", 26);
		}
		else
		{
			temp = get_prev_envv_lst(cmd->argv[idx]);
			if (temp)
			{
				del_lst = temp->next;
				temp->next = del_lst->next;
				ft_lstdelone(del_lst, del);
			}
		}
		idx++;
	}
}
