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

/*
** ************ wopark **************
*/

/*
** ************ parse.c *************
*/
int		parse_input(char *input);


#endif
