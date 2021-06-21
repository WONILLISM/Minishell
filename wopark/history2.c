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
int	find_prev_history(t_dllist *h_list, t_cursor *cursor)
{
	t_hisnode	*node;
	//char		*tmp;

	node = cursor->cur;
	if (node->prev)
	{
		if (node->prev->finished)
		{
			//tmp = node->prev->pending;
			////if (node->prev->pending == NULL)
			////{
			////	node->prev->pending = ft_strdup(node->prev->finished);
			////	tmp = node->prev->pending;
			////}
			term_del_line(cursor, h_list);
			cursor->cur = node->prev;
			write(1, "minish $> ", 10);
			cursor->key_pos = ft_strlen(cursor->cur->finished);
			cursor->len = cursor->key_pos;
			write(1, cursor->cur->finished, cursor->len);
		}
	}
	return (1);
}

 int	find_next_history(t_dllist *h_list, t_cursor *cursor)
 {
 	t_hisnode	*node;
	//char		*tmp;

	node = cursor->cur;
	if (node->next)
	{
		if (node->next->finished || node->next->pending)
		{
			//tmp = node->next->pending;
			//if (node->next->pending == NULL)
			//{
			//	node->next->pending = ft_strdup(node->next->finished);
			//	tmp = node->next->pending;
			//}
			term_del_line(cursor, h_list);
			cursor->cur = node->next;
			write(1, "minish $> ", 10);
			if (!node->next->finished)
			{
				cursor->key_pos = 0;
				cursor->len = 0;
			}
			else
			{
				cursor->key_pos = ft_strlen(cursor->cur->finished);
				cursor->len = cursor->key_pos;
				write(1, cursor->cur->finished, cursor->len);

			}
		}
	}
 	return (1);
 }
