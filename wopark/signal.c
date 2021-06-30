#include "../includes/minish.h"

int			new_line(void)
{
	t_cursor	*cursor;

	tputs(tgetstr("do", NULL), 1, ft_putchar);
	tputs(tgetstr("ll", NULL), 1, ft_putchar);
	cursor = get_cursor();
	cursor->key_pos = 0;
	cursor->len = cursor->key_pos;
	ft_putstr_fd("minish $> ", STDOUT);
	return (SUCCESS);
}

void		signal_handler(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, 0);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			new_line();
			g_archive.exit_stat = 1;
		}
		else
		{
			ft_putchar_fd('\n', STDOUT);
			if ((status & 0xff) == 0)
				g_archive.exit_stat = ((status >> 8) & 0xff);
			else
				g_archive.exit_stat = (status & 0xff) + 128;
		}
	}
	else if (signo == SIGQUIT)
	{
		// if (pid == -1)
			// ft_putstr_fd("\b\b  \b\b\n", STDOUT);
		// else
		if (pid != -1)
		{
			ft_putstr_fd("Quit: 3\n", STDOUT);
			if ((status & 0xff) == 0)
				g_archive.exit_stat = ((status >> 8) & 0xff);
			else
				g_archive.exit_stat = (status & 0xff) + 128;
		}
	}
}

void		signal_init(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
