#include "../includes/minish.h"

void		ft_error(int err_nbr, int exit_status)
{
	char	*err_str;

	err_str = strerror(err_nbr);
	g_archive.exit_stat = exit_status;
	write(2, ": ", 2);
	write(2, err_str, ft_strlen(err_str));
	write(2, "\n", 1);
}