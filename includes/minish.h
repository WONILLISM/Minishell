/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minish.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wopark <wopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:09:44 by wopark            #+#    #+#             */
/*   Updated: 2021/06/28 19:05:38 by wopark           ###   ########.fr       */
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
# include <termios.h>
# include <termcap.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft/libft.h"

# define KEY_LEFT			4479771
# define KEY_RIGHT			4414235
# define KEY_UP				4283163
# define KEY_DOWN			4348699
# define KEY_BACKSPACE		127
# define CTRL_D				4

# define SEMICOLON			0
# define PIPE				1
# define ERROR				-1
# define SUCCESS			1
# define STDIN				0
# define STDOUT				1
# define STDERR				2
# define READ_ERR			-1
# define READ_SUC			0
# define SYNTAX_ERROR_MSG	"bash: syntax error near unexpected token"

/*
**	double linked list
*/
typedef struct	s_hisnode
{
	void				*pending;
	void				*finished;
	int					idx;
	struct s_hisnode	*prev;
	struct s_hisnode	*next;
}				t_hisnode;

typedef struct	s_dllist
{
	t_hisnode	*head;
	t_hisnode	*tail;
	int			length;
}				t_dllist;

t_hisnode	*ft_dll_newhisnode(void *pending, void *finished);
void		ft_dll_init(t_dllist *list);
void		ft_dll_addhisnode(t_dllist *list, void *pending, void *finished);
void		ft_dll_delhisnode(t_dllist *list, t_hisnode *node, void (*del)(void *, void *));
// t_hisnode	*ft_dll_find_idx(t_dllist *list, int idx);
void		ft_dll_viewlst(t_dllist *list);
// void		ft_dll_clear(t_dllist *list, void (*del)(void *));

typedef struct	s_cursor
{
	int		r_nbr;
	int		idx;
	int		buf;
	int		key_pos;
	int		len;
	t_hisnode	*cur;
}				t_cursor;

typedef struct	s_redir
{
	int		sign;
	char	*file_name;
}				t_redir;

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
	int			fd[2];
	int			rd_fd[2];
	t_list		*rd_lst;
}				t_cmd;

typedef struct	s_data
{
	t_list		*last_node;
	char		*buf;
	char		*rd_buf;
	t_cmd		cmd;
	t_redir		rd;
	int			buf_size;
	int			input_idx;
	int			buf_idx;
	int			rd_buf_idx;
}				t_data;

typedef struct	s_archive
{
	t_list	*envv_lst;
	char	*buf;
	int		exit_stat;
	int		parse_error;
}				t_archive;

t_archive	g_archive;
/*
** ************ wopark **************
*/

/*
** ************ cursor.c ***********
*/
void	cursor_init(t_cursor *cursor, t_dllist *h_list);

// history
int		find_prev_history(t_dllist *h_list, t_cursor *cursor);
int		find_next_history(t_dllist *h_list, t_cursor *cursor);
/*
** ************ parse_utils.c*************
*/
void	chk_space_flag(char **strs);
int		chk_var_name(t_data *data, char *input);
int		lst_add_cmd(t_data *data, t_list **cmd_root, int flag);

int		parse_error_check(t_data *data);
int		parse_error_msg(char *msg);
int		chk_question_mark(t_data *data, char *input);

void	signal_init(int argc, char **argv);

/*
** ************ terminal_handle.c ******************
*/
void	ft_freehistory(void *pending, void *finished);
void	get_cursor_position(int *col, int *rows);
void	term_init(struct termios *term, struct termios *backup);
int		term_key_handler(t_cursor *cursor, t_dllist *h_list, char **input);
// int		term_key_handler(t_cursor *cursor, t_dllist *h_list);

/*
** ************ parse.c *************
*/
void	parse_init(t_data *data, t_list **cmd_root, int input_size);
int		parse_input(char *input);

void	chk_redir_sign(char *input, t_data *data, t_list **cmd_root);
void	init_redir(t_data *data);
void	update_redir(t_data *data, t_list **cmd_root);
void	init_cmd(t_data *data);
void	init_data(t_data *data, t_list **cmd_root, int input_size);
void	init_redir(t_data *data);
void	redir_list_view(t_list *lst);
char	*realloc_input(char *ptr, size_t size);




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
void			other_command(t_cmd *cmd, char **envp);
void			free_array(char **array);
void			child_process(t_cmd *cmd, char **envp);
char			**make_envp(void);
#endif
