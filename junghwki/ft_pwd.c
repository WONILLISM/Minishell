#include "../includes/minish.h"

void		ft_pwd()
{
	char	buf[4096];

	getcwd(buf, 4096);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
}
