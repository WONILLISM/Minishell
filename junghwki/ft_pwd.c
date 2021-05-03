#include "../includes/minish.h"
#include <limits.h>

// char *getcwd(char *buf, size_t size);

void		ft_pwd()
{
	char buff[1000];

	getcwd(buff, 1000);
	printf("%s",buff);
}

int			main(void)
{
	ft_pwd();
	return (0);
}
