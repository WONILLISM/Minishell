/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghwki <junghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:24:35 by junghwki          #+#    #+#             */
/*   Updated: 2021/06/29 18:24:36 by junghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void		env_value_print(char *str)
{
	int		idx;

	idx = 0;
	while (str[idx])
	{
		if (ft_strchr("$`\\\"", str[idx]))
			write(1, "\\", 1);
		write(1, &str[idx], 1);
		idx++;
	}
}

int			env_key_check(char *key)
{
	int		idx;

	idx = 0;
	if (!key[idx] || ft_isdigit(key[idx]))
		return (-1);
	while (key[idx])
	{
		if (key[idx] == '_' || ft_isalnum(key[idx]))
			idx++;
		else
			return (-1);
	}
	return (0);
}

int			env_lst_cmp(char *s1, char *s2)
{
	int		idx;

	idx = 0;
	while (s1[idx])
	{
		if (s1[idx] != s2[idx])
			return (s1[idx] - s2[idx]);
		idx++;
	}
	return (-1);
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

void		export_lst_sort(t_list **lst)
{
	t_list	*temp;
	t_env	*temp_env;
	t_list	*next_temp;
	t_env	*next_temp_env;

	temp = (*lst)->next;
	while (temp)
	{
		temp_env = temp->content;
		next_temp = temp->next;
		while (next_temp)
		{
			next_temp_env = next_temp->content;
			if (env_lst_cmp(temp_env->key, next_temp_env->key) > 0)
				env_swap(temp_env, next_temp_env);
			next_temp = next_temp->next;
		}
		temp = temp->next;
	}
}

t_list		*export_lst_make(void)
{
	t_env	*content;
	t_list	*export_head;
	t_list	*temp;

	export_head = ft_lstnew(NULL);
	temp = g_archive.envv_lst->next;
	while (temp)
	{
		content = env_dup(temp->content);
		ft_lstadd_back(&export_head, ft_lstnew(content));
		temp = temp->next;
	}
	return (export_head);
}

void		export_lst_print(void)
{
	void	(*del)();
	t_list	*head;
	t_list	*temp;
	t_env	*temp_env;

	del = envv_content_del;
	head = export_lst_make();
	export_lst_sort(&head);
	temp = head->next;
	while (temp)
	{
		temp_env = temp->content;
		write(1, "declare -x ", 11);
		write(1, temp_env->key, ft_strlen(temp_env->key));
		if (temp_env->value)
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			env_value_print(temp_env->value);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		temp = temp->next;
	}
	ft_lstclear(&head->next, del);
	free(head);
}

void		export_add(t_cmd *cmd)
{
	t_list	*temp;
	t_env	*content;
	int		idx;

	idx = 1;
	while (cmd->argv[idx])
	{
		content = envv_sep(cmd->argv[idx]);
		if (env_key_check(content->key) < 0)
		{
			g_archive.exit_stat = 1;
			write(2, "minish: export: `", 17);
			write(2, content->key, ft_strlen(content->key));
			if (content->value)
			{
				write(2, "=", 1);
				write(2, content->value, ft_strlen(content->value));
			}
			write(2, "': not a valid identifier\n", 26);
		}
		else
		{
			temp = get_curr_envv_lst(content->key);
			if (temp)
				temp->content = content;
			else
				ft_lstadd_back(&g_archive.envv_lst, ft_lstnew(content));
		}
		idx++;
	}
}
