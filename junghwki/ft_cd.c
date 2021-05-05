#include "../includes/minish.h"

void		ft_pwd()
{
	char	buf[4096];

	getcwd(buf, 4096);
	printf("%s\n",buf);
}

// void		ft_pwd()
// {
	// char	*buff;
	// char	*path;

	// path = getcwd(buff, 1);
	// printf("%s\n",path);
	// free(path);
// }

void		ft_cd(char *path)
{
	chdir(path);
}

int			main(void)
{
	ft_pwd();
	// write(1, "\n", 1);
	ft_cd("abc/");
	return (0);
}