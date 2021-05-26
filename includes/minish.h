/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghwki <junghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:09:44 by wopark            #+#    #+#             */
/*   Updated: 2021/05/26 15:04:19 by junghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISH_H
# define MINISH_H
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft/libft.h"

# define SEMICOLON			0
# define PIPE				1
# define ERROR				-1
# define SUCCESS			1
# define STDIN				0
# define STDOUT				1
# define STDERR				2
# define READ_ERR			-1
# define READ_SUC			0
# define SYNTAX_ERROR_MSG	"Syntax Error"

typedef struct	s_env
{
	char		*key;
	char		*value;
}				t_env;

typedef struct	s_cmd
{
	char		**argv;		// 명령어 내용 NULL
	int			flag;		// 0: ; or NULL	1: pipe
	int			redir;
	char		quote;		// stack for ' or "
	int			fd[2];
}				t_cmd;

typedef struct	s_data
{
	t_list		*last_node;
	t_cmd		*cmd;
	char		*buf;
	int			buf_size;
	int			input_idx;
	int			buf_idx;
	int			cmd_idx;
}				t_data;

typedef struct	s_archive
{
	t_list		*envv_lst;
	int			exit_stat;
	int			parse_error;
}				t_archive;

t_archive	g_archive;
/*
** ************ wopark **************
*/

/*
** ************ parse_utils.c*************
*/
void	chk_space_flag(char **strs);
int		chk_var_name(t_data *data, char *input);
int		lst_add_cmd(t_data *data, t_list *cmd_root, int flag);

int		parse_error_msg(char *msg);

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
void			free_array(char **array);
void			child_process(t_cmd *cmd);
#endif
