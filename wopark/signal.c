#include "../includes/minish.h"

void		signal_handler(int signo)
{
	pid_t	pid;

	pid = waitpid(-1, &g_archive.exit_stat, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			// ft_putstr_fd("minish $> ", STDOUT);
			// ft_putstr_fd("\b\b  \b\b\n", STDOUT);
			write(1,"\n",1);
			write(1, "minish $> ", 10);
			// if (g_archive.buf)
			// 	free(g_archive.buf);
			g_archive.buf = 0;
			g_archive.exit_stat = 1;
		}
		else
		{
			g_archive.exit_stat = 130;
			ft_putchar_fd('\n', STDOUT);
		}
	}
	else if (signo == SIGQUIT)
	{
		// if (pid == -1)
		// 	ft_putstr_fd("\b\b  \b\b\n", STDOUT);
		// else
		// {
		g_archive.exit_stat = 131;
		ft_putstr_fd("Quit: 3\n", STDOUT);
		// }
	}
}

void		signal_init(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}
