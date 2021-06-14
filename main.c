/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wopark <wopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:07:54 by wopark            #+#    #+#             */
/*   Updated: 2021/06/14 22:26:17 by wopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minish.h"
#include <term.h>

char	*realloc_input(char *ptr, size_t size)
{
	char	*ret;

	ret = (char *)malloc(size);
	if (!ret)
		return (0);
	ft_memmove(ret, ptr, size);
	free(ptr);
	return (ret);
}

int		get_input(char **input, t_dllist *h_list)
{
	t_cursor		cursor;
	struct	termios	term;
	struct	termios	term_backup;

	*input = malloc(1);
	if (input == NULL)
		return (READ_ERR);
	term_init(&term, &term_backup);
	cursor_init(&cursor, h_list);
	while (1)
	{
		cursor.buf = 0;
		cursor.r_nbr = read(STDIN_FILENO, &cursor.buf, sizeof(cursor.buf));
		if (!term_key_handler(&cursor, input, h_list))
		{
			cursor_init(&cursor, h_list);
			tcsetattr(STDIN_FILENO, TCSANOW, &term_backup);
			return (READ_SUC);
		}
		*input = realloc_input(*input, cursor.key_pos + 2);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term_backup);
	return (READ_ERR);
}

int		main(int argc, char **argv, char **envv)
{
	t_dllist	history_lst;
	char		*input;

	ft_dll_init(&history_lst);
	signal_init(argc, argv);
	envv_lst_make(envv);
	while (1)
	{
		write(1, "minish $> ", 10);
		if (get_input(&input, &history_lst) == READ_ERR)
			printf("Error");
		if (parse_input(input) == ERROR)
			parse_error_msg(SYNTAX_ERROR_MSG);
		free(input);
	}
	return (0);
}



