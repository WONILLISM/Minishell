/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wopark <wopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:07:54 by wopark            #+#    #+#             */
/*   Updated: 2021/06/02 12:23:08 by wopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minish.h"

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

int	nbr_length(int n)
{
	int	i = 0;

	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	get_cursor_position(int *col, int *rows)
{
	int		a = 0;
	int		i = 1;
	char	buf[255];
	int		ret;
	int		temp;

	write(0, "\033[6n", 4);  //report cursor location
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				*rows = atoi(&buf[i]) - 1;
			else
			{
				temp = atoi(&buf[i]);
				*col = temp - 1;
			}
			a++;
			i += nbr_length(temp) - 1;
		}
		i++;
	}
}

int		get_input(char **input)
{
	t_cursor		cursor;
	struct	termios	term;
	struct	termios	term_backup;

	*input = malloc(1);
	if (input == NULL)
		return (READ_ERR);
	term_init(&term, &term_backup, &cursor);
	while (1)
	{
		cursor.buf = 0;
		cursor.r_nbr = read(STDIN_FILENO, &cursor.buf, sizeof(cursor.buf));
		if (!term_key_handler(&cursor, input))
		{
			*(*input + cursor.key_pos) = 0;
			// printf("input : %s\n", *input);
			cursor.idx = 0;
			cursor.key_pos = 0;
			cursor.len = 0;
			// tcsetattr(STDIN_FILENO, TCSANOW, &term_backup);
			get_cursor_position(&cursor.col, &cursor.row);
			printf("%d %d\n", cursor.col, cursor.row);
			return (READ_SUC);
		}
		*input = realloc_input(*input, cursor.key_pos + 2);
	}
	// tcsetattr(STDIN_FILENO, TCSANOW, &term_backup);
	return (READ_ERR);
}

int		main(int argc, char **argv, char **envv)
{
	char	*input;

	g_archive.buf = 0;
	signal_init(argc, argv);
	envv_lst_make(envv);
	while (1)
	{
		write(1, "minish $> ", 10);
		if (get_input(&input) == READ_ERR)
			printf("Error");
		if (parse_input(input) == ERROR)
			parse_error_msg(SYNTAX_ERROR_MSG);
		free(input);
	}
	return (0);
}


// int		get_input(char **input)
// {
// 	int		r_nbr;
// 	int		idx;
// 	int		cnt;
// 	char	buf;

// 	idx = 0;
// 	cnt = 1;
// 	*input = malloc(1);
// 	if (*input == NULL)
// 		return (READ_ERR);
// 	while (1)
// 	{
// 		r_nbr = read(0, &buf, 1);
// 		if (r_nbr == 0 || buf == '\n')
// 		{
// 			*(*input + idx) = 0;
// 			return (READ_SUC);
// 		}
// 		*(*input + idx) = buf;
// 		idx++;
// 		*input = realloc_input(*input, cnt + 1);
// 		cnt++;
// 	}
// 	return (READ_ERR);
// }
