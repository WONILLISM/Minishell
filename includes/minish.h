#ifndef MINISH_H
# define MINISH_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

typedef struct	s_env
{
	char		*key;
	char		*value;
}				t_env;

typedef struct	s_data
{
	t_list		*env_last;
	char		**cmdlines;		// 명령어, 내용, NULL
}				t_data;

#endif
