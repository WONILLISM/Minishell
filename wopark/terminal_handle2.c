#include "../includes/minish.h"

void	term_init(struct termios *term, struct termios *backup)
{
	tgetent(NULL, "xterm");
	tcgetattr(STDIN_FILENO, term);
	tcgetattr(STDIN_FILENO, backup);
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}
void	set_backspace_key(t_cursor *cursor, char **input)
{
	char	*tmp;

	(void)input;
	tputs(tgetstr("le", NULL), 1, ft_putchar); // move left one space
	tputs(tgetstr("dm", NULL), 1, ft_putchar); // enter delete mode
	tputs(tgetstr("dc", NULL), 1, ft_putchar); // delete character (P*)
	tputs(tgetstr("ed", NULL), 1, ft_putchar); // end delete mode
	tmp = cursor->cur->data;
	if (*tmp)
	{
		tmp[cursor->key_pos] = 0;
		(cursor->key_pos)--;
		(cursor->len)--;
	}
}
void	input_term(int buf)
{
	tputs(tgetstr("im", NULL), 1, ft_putchar); // enter insert mode
	tputs(tgetstr("ic", NULL), 1, ft_putchar); // insert character
	ft_putchar(buf);
	tputs(tgetstr("ip", NULL), 1, ft_putchar); // insert padding after inserted character
	tputs(tgetstr("ei", NULL), 1, ft_putchar); // exit insert mode
}
int		set_printable_key(t_cursor *cursor, char **input)
{
	(void)input;
	char	*tmp;

	tmp = cursor->cur->data;
	input_term(cursor->buf);
	if (cursor->buf == '\n')
	{
		tmp[cursor->key_pos] = 0;
		return (1);
	}
	tmp[cursor->key_pos] = cursor->buf;
	(cursor->key_pos)++;
	(cursor->len)++;
	cursor->cur->data = realloc_input(cursor->cur->data, cursor->len + 1);
	return (0);
}

void	ft_freestr(void *str)
{
	free(str);
}

int		term_key_handler(t_cursor *cursor, char **input, t_dllist *h_list)
{
	char	*tmp_data;
	t_dlnode	*tmp_node;

	(void)input;
	if (cursor->buf == KEY_BACKSPACE && (cursor->key_pos) > 0)
		set_backspace_key(cursor, input);
	else if (cursor->buf == KEY_UP)
		return find_prev_history(h_list, cursor, input);
	else if (cursor->buf == KEY_DOWN)
		return find_next_history(h_list, cursor, input);
	else if (ft_isprint(cursor->buf) || cursor->buf == '\n')
	{
		if (set_printable_key(cursor, input))
		{
			tmp_node = h_list->tail->prev;
			tmp_data = tmp_node->data;
			if (*tmp_data == 0)
			{
				ft_dll_delnode(h_list, tmp_node, ft_freestr);
				cursor->cur = h_list->tail;
			}
			if (cursor->cur->idx != -1 && cursor->cur->idx != h_list->length -1)
				ft_dll_add(h_list, cursor->cur->data);
			return (0);
		}
	}
	else if (cursor->buf == CTRL_D)
		return (0);
	return (1);
}
