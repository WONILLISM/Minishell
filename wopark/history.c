#include "../includes/minish.h"

void	term_del_line(t_cursor *cursor, t_dllist *h_list)
{
	int			len;

	tputs(tgetstr("le", NULL), 1, ft_putchar);
	tputs(tgetstr("dm", NULL), 1, ft_putchar);
	tputs(tgetstr("dl", NULL), 1, ft_putchar);
	tputs(tgetstr("ed", NULL), 1, ft_putchar);
	len = tgetnum("co");
	while (len--)
		tputs(tgetstr("le", NULL), 1, ft_putchar); // move left one space
	cursor_init(cursor, h_list);
}
int	find_prev_history(t_dllist *h_list, t_cursor *cursor, char **input)
{
	t_dlnode	*node;

	if (**input == 0)
		cursor->input_flag = 1;
	// else if (cursor->input_flag == 1 && **input)
	// 	ft_dll_add(h_list, *input);
	node = cursor->cur;
	if (node->prev)
	{
		if (node->prev->data)
		{
			term_del_line(cursor, h_list);
			cursor->cur = node->prev;
			write(1, "minish $> ", 10);
			free(*input);
			*input = ft_strdup(node->prev->data);
			cursor->key_pos = ft_strlen(*input);
			cursor->len = cursor->key_pos;
			write(1, *input, cursor->len);
		}
	}
	return (1);
}

int	find_next_history(t_dllist *h_list, t_cursor *cursor, char **input)
{
	t_dlnode	*node;

	node = cursor->cur;
	if (node->next)
	{
		if (node->next->data)
		{
			term_del_line(cursor, h_list);
			cursor->cur = node->next;
			write(1, "minish $> ", 10);
			free(*input);
			*input = ft_strdup(node->next->data);
			cursor->key_pos = ft_strlen(*input);
			cursor->len = cursor->key_pos;
			write(1, *input, cursor->len);
		}
		else
		{
			// printf("%d\n", cursor->input_flag);
			if (cursor->input_flag)
			{
				term_del_line(cursor, h_list);
				write(1, "minish $> ", 10);
				cursor->key_pos = 0;
				cursor->len = 0;
			}
		}
	}
	return (1);
}
