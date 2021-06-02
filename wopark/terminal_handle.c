#include "../includes/minish.h"

void	term_init(struct termios *term, struct termios *backup, t_input_var *ip)
{
	ip->buf = 0;
	ip->idx = 0;
	ip->len = 0;
	ip->key_pos = 0;
	tgetent(NULL, "xterm");
	tcgetattr(STDIN_FILENO, term);
	tcgetattr(STDIN_FILENO, backup);
	term->c_lflag &= ~(ICANON | ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}

int		term_key_handler(t_input_var *ip_var, char **input)
{
	if (ip_var->buf == KEY_LEFT && (ip_var->key_pos) > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		(ip_var->key_pos)--;
	}
	else if (ip_var->buf == KEY_RIGHT && (ip_var->key_pos) < ip_var->len)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
		(ip_var->key_pos)++;
	}
	else if (ip_var->buf == KEY_BACKSPACE && (ip_var->key_pos) > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		tputs(tgetstr("dm", NULL), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
		tputs(tgetstr("ed", NULL), 1, ft_putchar);
		(ip_var->key_pos)--;
		(ip_var->idx)--;
		(ip_var->len)--;
	}
	else if (ft_isprint(ip_var->buf) || ip_var->buf == '\n')
	{
		tputs(tgetstr("im", NULL), 1, ft_putchar);
		tputs(tgetstr("ic", NULL), 1, ft_putchar);
		ft_putchar(ip_var->buf);
		tputs(tgetstr("ip", NULL), 1, ft_putchar);
		tputs(tgetstr("ei", NULL), 1, ft_putchar);
		if (ip_var->buf == '\n')
			return (0);
		*(*input + ip_var->idx) = ip_var->buf;
		(ip_var->key_pos)++;
		(ip_var->idx)++;
		(ip_var->len)++;
	}
	else if (ip_var->buf == CTRL_D)
		return (0);
	return (1);
}
