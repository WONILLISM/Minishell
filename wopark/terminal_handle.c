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

int		term_key_handler(int *key_pos, int *buf, int *len)
{
	if (*buf == KEY_LEFT && (*key_pos) > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		(*key_pos)--;
	}
	else if (*buf == KEY_RIGHT && (*key_pos) < *len)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		(*key_pos)++;
	}
	else if (*buf == KEY_BACKSPACE && (*key_pos) > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		tputs(tgetstr("dm", NULL), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
		tputs(tgetstr("ed", NULL), 1, ft_putchar);
		(*key_pos)--;
		(*len)--;
	}
	else if (ft_isprint(*buf) || *buf == '\n')
	{
		tputs(tgetstr("im", NULL), 1, ft_putchar);
		tputs(tgetstr("ic", NULL), 1, ft_putchar);
		ft_putchar(*buf);
		tputs(tgetstr("ip", NULL), 1, ft_putchar);
		tputs(tgetstr("ei", NULL), 1, ft_putchar);
		(*key_pos)++;
		(*len)++;
		if (*buf == '\n')
		{
			*key_pos = 0;
			*len = 0;
			return (0);
		}
	}
	else if (*buf == CTRL_D)
		return (0);
	return (1);
}
