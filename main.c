/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wopark <wopark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:07:54 by wopark            #+#    #+#             */
/*   Updated: 2021/06/19 18:31:48 by wopark           ###   ########.fr       */
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


/*
history 규칙

1. command상에서 들어오는 input은 input_tmp에서 진행
2. 개행이 오면 히스토리 리스트의 끝에 저장된다.
3. 히스토리 리스트 탐색
	1. 해당 리스트의 값 수정가능
	2. 해당 리스트의 값을 수정한 채로 방향키를 움직인다면 수정된 채로 남아있음.
	3. 해당 리스트의 값을 수정한 채로 개행을 누른다면
		최초에 저장되었던 값으로 수정되고 바뀐 값은 수정된 채로 저장됨
4. 개행이 입력될 때 비어있는 값이면 리스트에 추가하지 않는다.

*/
int		get_input(char **input, t_dllist *h_list)
{
	struct	termios	term;
	struct	termios	term_backup;
	t_cursor		cursor;
	char			*pending;
	char			*finished;

	(void)input;
	term_init(&term, &term_backup);
	cursor_init(&cursor, h_list);
	pending = (char *)malloc(sizeof(char));
	*pending = 0;
	finished = NULL;
	ft_dll_addhisnode(h_list, pending, finished);
	cursor.cur = h_list->tail->prev;
	while (1)
	{
		cursor.buf = 0;
		cursor.r_nbr = read(STDIN_FILENO, &cursor.buf, sizeof(cursor.buf));
		if (!term_key_handler(&cursor, h_list))
		{
			ft_dll_viewlst(h_list);
			tcsetattr(STDIN_FILENO, TCSANOW, &term_backup);
			return (READ_SUC);
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &term_backup);
	return (READ_ERR);
}
// int		get_input(char **input, t_dllist *h_list)
// {
// 	t_cursor		cursor;
// 	struct	termios	term;
// 	struct	termios	term_backup;

// 	*input = malloc(1);
// 	if (input == NULL)
// 		return (READ_ERR);
// 	**input = 0;
// 	term_init(&term, &term_backup);
// 	cursor_init(&cursor, h_list);
// 	cursor.input_tmp = *input;
// 	while (1)
// 	{
// 		cursor.buf = 0;
// 		cursor.r_nbr = read(STDIN_FILENO, &cursor.buf, sizeof(cursor.buf));
// 		if (!term_key_handler(&cursor, input, h_list))
// 		{
// 			cursor_init(&cursor, h_list);
// 			tcsetattr(STDIN_FILENO, TCSANOW, &term_backup);
// 			return (READ_SUC);
// 		}
// 		*input = realloc_input(*input, cursor.len + 1);
// 	}
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term_backup);
// 	return (READ_ERR);
// }

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
		// if (parse_input(input) == ERROR)
		// 	parse_error_msg(SYNTAX_ERROR_MSG);
		// free(input);
	}
	return (0);
}



