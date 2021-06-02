#include "../includes/minish.h"

void	term_init(struct termios *term, struct termios *backup, t_cursor *cursor)
{
	cursor->buf = 0;
	cursor->idx = 0;
	cursor->len = 0;
	cursor->key_pos = 0;
	tgetent(NULL, "xterm");
	tcgetattr(STDIN_FILENO, term);
	tcgetattr(STDIN_FILENO, backup);
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}
void	set_backspace_key(t_cursor *cursor)
{
	tputs(tgetstr("le", NULL), 1, ft_putchar); // move left one space
	tputs(tgetstr("dm", NULL), 1, ft_putchar); // enter delete mode
	tputs(tgetstr("dc", NULL), 1, ft_putchar); // delete character (P*)
	tputs(tgetstr("ed", NULL), 1, ft_putchar); // end delete mode
	(cursor->key_pos)--;
	(cursor->len)--;
}
void	set_printable_key(t_cursor *cursor)
{
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	tputs(tgetstr("ic", NULL), 1, ft_putchar);
	ft_putchar(cursor->buf);
	tputs(tgetstr("ip", NULL), 1, ft_putchar);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
}
int		term_key_handler(t_cursor *cursor, char **input)
{
	if (cursor->buf == KEY_BACKSPACE && (cursor->key_pos) > 0)
		set_backspace_key(cursor);
	else if (ft_isprint(cursor->buf) || cursor->buf == '\n')
	{
		set_printable_key(cursor);
		if (cursor->buf == '\n')
			return (0);
		*(*input + cursor->key_pos) = cursor->buf;
		(cursor->key_pos)++;
		(cursor->len)++;
	}
	else if (cursor->buf == CTRL_D)
		return (0);
	return (1);
}
