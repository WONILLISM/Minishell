/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wopark <wopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:07:54 by wopark            #+#    #+#             */
/*   Updated: 2021/05/28 21:15:42 by wopark           ###   ########.fr       */
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

int		get_input(char **input)
{
	t_input_var	ip;

	ip.idx = 0;
	*input = malloc(1);
	if (*input == NULL)
		return (READ_ERR);
	while (1)
	{
		ip.buf = 0;
		ip.r_nbr = read(STDIN_FILENO, &ip.buf, sizeof(ip.buf));
		if (!term_key_handler(&ip, *input))
		{
			*(*input + ip.idx) = 0;
			return (READ_SUC);
		}
		*(*input + ip.idx) = ip.buf;
		ip.idx++;
		*input = realloc_input(*input, ip.idx + 2);
	}
	return (READ_ERR);
}

int		main(int argc, char **argv, char **envv)
{
	struct	termios term;
	struct	termios term_backup;
	char	*input;

	g_archive.buf = 0;
	signal_init(argc, argv);
	envv_lst_make(envv);
	while (1)
	{
		write(1, "minish $> ", 10);
		term_init(&term, &term_backup);
		if (get_input(&input) == READ_ERR)
			printf("Error");
		if (parse_input(input) == ERROR)
			parse_error_msg(SYNTAX_ERROR_MSG);
		tcsetattr(STDIN_FILENO, TCSANOW, &term_backup);
		free(input);
	}
	return (0);
}
