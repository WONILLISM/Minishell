#include "../includes/minish.h"

t_cursor	*get_cursor(void)
{
	static t_cursor	cursor;

	return (&cursor);
}

void	cursor_init(t_cursor *cursor, t_dllist *h_list)
{
	cursor->buf = 0;
	cursor->idx = 0;
	cursor->len = 0;
	cursor->key_pos = 0;
	cursor->cur = h_list->tail;
	(void)h_list;
}
