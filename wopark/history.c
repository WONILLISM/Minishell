#include "../includes/minish.h"

int	find_prev_history(t_dllist *h_list, t_cursor *cursor, char **input)
{
	t_dlnode	*node;
	char		*tmp;

	node = cursor->cur;
	tmp = node->prev->data;
	if (tmp)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar); // move left one space
		tputs(tgetstr("dm", NULL), 1, ft_putchar); // enter de
		tputs(tgetstr("dl", NULL), 1, ft_putchar);
		tputs(tgetstr("ed", NULL), 1, ft_putchar); // end delete mode
		int lines = tgetnum("co");
		while (lines--)
			tputs(tgetstr("le", NULL), 1, ft_putchar); // move left one space
		cursor_init(cursor, h_list);
		cursor->cur = node->prev;
		write(1, "minish $> ", 10);
		free(*input);
		*input = ft_strdup(tmp);
		cursor->key_pos = ft_strlen(*input);
		cursor->len = cursor->key_pos;
		write(1, *input, cursor->len);
	}
	return (1);
}

int	find_next_history(t_dllist *h_list, t_cursor *cursor, char **input)
{
	t_dlnode	*node;
	char		*tmp;

	node = cursor->cur;
	tmp = node->next->data;
	if (tmp)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar); // move left one space
		tputs(tgetstr("dm", NULL), 1, ft_putchar); // enter de
		tputs(tgetstr("dl", NULL), 1, ft_putchar);
		tputs(tgetstr("ed", NULL), 1, ft_putchar); // end delete mode
		int lines = tgetnum("co");
		while (lines--)
			tputs(tgetstr("le", NULL), 1, ft_putchar); // move left one space
		cursor_init(cursor, h_list);
		cursor->cur = node->next;
		write(1, "minish $> ", 10);
		free(*input);
		*input = ft_strdup(tmp);
		cursor->key_pos = ft_strlen(*input);
		cursor->len = cursor->key_pos;
		write(1, *input, cursor->len);
	}
	return (1);
}
