#include "../includes/minish.h"

void	print_prompt(void)
{
	tputs(tgetstr("im", NULL), 1, ft_putchar); // enter insert mode
	tputs(tgetstr("ic", NULL), 1, ft_putchar); // insert character
	ft_putchar('m');
	ft_putchar('i');
	ft_putchar('n');
	ft_putchar('i');
	ft_putchar('s');
	ft_putchar('h');
	ft_putchar(' ');
	ft_putchar('$');
	ft_putchar('>');
	ft_putchar(' ');
	tputs(tgetstr("ip", NULL), 1, ft_putchar); // insert padding after inserted character
	tputs(tgetstr("ei", NULL), 1, ft_putchar); // exit insert mode
}

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

int	find_prev_history(t_dllist *h_list, t_cursor *cursor)
{
	t_hisnode	*node;
	char		*tmp;

	node = cursor->cur;
	if (node->prev)
	{
		if (node->prev->finished)
		{
			tmp = node->prev->pending;
			if (node->prev->pending == NULL)
				node->prev->pending = ft_strdup(node->prev->finished);
			term_del_line(cursor, h_list);
			cursor->cur = node->prev;
			print_prompt();
			cursor->key_pos = ft_strlen(cursor->cur->pending);
			cursor->len = cursor->key_pos;
			write(1, cursor->cur->pending, cursor->len);
		}
	}
	return (1);
}

 int	find_next_history(t_dllist *h_list, t_cursor *cursor)
 {
 	t_hisnode	*node;

	node = cursor->cur;
	if (node->next)
	{
		if (node->next->finished || node->next->pending)
		{
			term_del_line(cursor, h_list);
			cursor->cur = node->next;
			print_prompt();
			if (!node->next->finished)
			{
				if (node->next->pending)
					write(1, cursor->cur->pending, ft_strlen(cursor->cur->pending));
				else
				{
					cursor->key_pos = 0;
					cursor->len = 0;
				}
			}
			else
			{
				cursor->key_pos = ft_strlen(cursor->cur->pending);
				cursor->len = cursor->key_pos;
				write(1, cursor->cur->pending, cursor->len);
			}
		}
	}
 	return (1);
 }
