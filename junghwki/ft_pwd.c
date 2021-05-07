#include "../includes/minish.h"

void		ft_pwd()
{
	char	buf[4096];

	getcwd(buf, 4096);
	printf("%s\n",buf);
}

// void		ft_pwd()
// {
// 	char	*buff;
// 	char	*path;

// 	path = getcwd(buff, 1);
// 	printf("%s",path);
// 	free(path);
// }

// int			main(void)
// {
// 	ft_pwd();
// 	return (0);
// }