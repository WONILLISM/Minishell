#include "../includes/minish.h"

int		parse_error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	g_archive.exit_stat = 1;
	return (0);
}

