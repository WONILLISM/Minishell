/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghwki <junghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:09:44 by wopark            #+#    #+#             */
/*   Updated: 2021/05/13 16:39:55 by junghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"

# define SEMICOLON	0
# define PIPE		1
# define READ_ERR	-1
# define READ_SUC	0

typedef struct	s_env
{
	char		*key;
	char		*value;
}				t_env;

typedef struct	s_cmd
{
	char		**argv;		// 명령어 내용 NULL
	int			flag;		// 0: ; or NULL	1: pipe
	char		quote;		// stack for ' or "
}				t_cmd;

typedef struct	s_data
{
	t_list		*last_node;
	t_cmd		*cmd;
	char		*buf;
	int			input_idx;
	int			buf_idx;
	int			cmd_idx;
}				t_data;

t_list	*g_envv_lst;
/*
** ************ wopark **************
*/

/*
** ************ parse.c *************
*/
int		parse_input(char *input);

int		ft_strcmp(const char *s1, const char *s2);

void			ft_pwd();
void			ft_cd(t_cmd *cmd);
void			ft_echo(t_cmd *cmd);
void			envv_lst_make(char **envv);
/*				utils			*/
int				ft_strcmp(const char *s1, const char *s2);
void			env_swap(t_env *a, t_env *b);
t_list			*get_curr_envv_lst(char *key_value);
t_list			*get_prev_envv_lst(char *key_value);
t_env			*envv_sep(char *envv);
/*				utils			*/
void			envv_lst_del(t_env *content);
void			execute_builtin(t_list *cmd_root);
void			export_lst_print();
void			export_add(t_cmd *cmd);
void			env_lst_print();
void			ft_unset(t_cmd *cmd);
int				ft_execve(t_cmd *cmd);
#endif
