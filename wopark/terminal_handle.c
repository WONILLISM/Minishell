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
	tputs(tgetstr("le", NULL), 1, ft_putchar); // move left one space
	tputs(tgetstr("dm", NULL), 1, ft_putchar); // enter delete mode
	tputs(tgetstr("dc", NULL), 1, ft_putchar); // delete character (P*)
	tputs(tgetstr("ed", NULL), 1, ft_putchar); // end delete mode
	if (*input)
	{
		*(*input + cursor->key_pos) = 0;
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
	input_term(cursor->buf);
	if (cursor->buf == '\n')
	{
		*(*input + cursor->key_pos) = 0;
		return (1);
	}
	*(*input + cursor->key_pos) = cursor->buf;
	(cursor->key_pos)++;
	(cursor->len)++;
	return (0);
}
int		term_key_handler(t_cursor *cursor, char **input, t_dllist *h_list)
{
	if (cursor->buf == KEY_BACKSPACE && (cursor->key_pos) > 0)
		set_backspace_key(cursor, input);
	else if (cursor->buf == KEY_UP)
		return find_prev_history(h_list, cursor);
	else if (cursor->buf == KEY_DOWN)
		return find_next_history(h_list, cursor, input);
	else if (ft_isprint(cursor->buf) || cursor->buf == '\n')
	{
		if (set_printable_key(cursor, input))
		{
			if (**input)
				ft_dll_add(h_list, *input);
			return (0);
		}
	}
	else if (cursor->buf == CTRL_D)
		return (0);
	return (1);
}
