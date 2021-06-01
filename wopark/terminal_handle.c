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
void	set_left_key(t_cursor *cursor)
{
	tputs(tgetstr("le", NULL), 1, ft_putchar);
	(cursor->key_pos)--;
}
void	set_right_key(t_cursor *cursor)
{
	tputs(tgetstr("nd", NULL), 1, ft_putchar);
	(cursor->key_pos)++;
}
void	set_backspace_key(t_cursor *cursor)
{
	tputs(tgetstr("le", NULL), 1, ft_putchar); // move left one space
	tputs(tgetstr("dm", NULL), 2, ft_putchar); // enter delete mode
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
	if (cursor->buf == KEY_LEFT && (cursor->key_pos) > 0)
		set_left_key(cursor);
	else if (cursor->buf == KEY_RIGHT && (cursor->key_pos) < cursor->len)
		set_right_key(cursor);
	else if (cursor->buf == KEY_BACKSPACE && (cursor->key_pos) > 0)
		set_backspace_key(cursor);
	else if (ft_isprint(cursor->buf) || cursor->buf == '\n')
	{
		set_printable_key(cursor);
		if (cursor->buf == '\n')
			return (0);
		*(*input + cursor->key_pos) = cursor->buf;
		(cursor->key_pos)++;
		(cursor->len)++;
		// printf("key_pos :  %d len :  %d\n", ip_var->key_pos, ip_var->len);
	}
	// else if (ip_var->buf == CTRL_D)
	// 	return (0);
	// else
	// {

	// 	// int lines = tgetnum("sc");
	// 	// printf("%d\n", lines);
	// 	// lines = tgetnum("co");
	// 	// printf("%d\n", lines);
	// 	// lines = tgetnum("ws");
	// 	// printf("%d\n", lines);
	// 	// write(1, &ip_var->buf, sizeof(ip_var->buf));
	// }

	return (1);
}
