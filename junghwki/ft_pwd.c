#include "../includes/minish.h"

void		ft_pwd()
{
	char	*buff;
	char	*path;

	path = getcwd(buff, 1);
	printf("%s",path);
	free(path);
}
/*
**	junghwki
*/
int			main(void)
{
	ft_pwd();
	return (0);
}