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

	(void)input;
	node = cursor->cur;
	if (node->prev)
	{
		if (node->prev->data)
		{
			term_del_line(cursor, h_list);
			cursor->cur = node->prev;
			write(1, "minish $> ", 10);
			cursor->key_pos = ft_strlen(cursor->cur->data);
			cursor->len = cursor->key_pos;
			write(1, cursor->cur->data, cursor->len);
		}
	}
	return (1);
}

int	find_next_history(t_dllist *h_list, t_cursor *cursor, char **input)
{
	t_dlnode	*node;

	(void)input;
	node = cursor->cur;
	if (node->next)
	{
		if (node->next->data)
		{
			term_del_line(cursor, h_list);
			cursor->cur = node->next;
			write(1, "minish $> ", 10);
			cursor->key_pos = ft_strlen(cursor->cur->data);
			cursor->len = cursor->key_pos;
			write(1, cursor->cur->data, cursor->len);
		}
	}
	return (1);
}
