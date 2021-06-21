#include "../includes/minish.h"

void		ft_pwd(void)
{
	char	*path;

	path = NULL;
	path = getcwd(NULL, 0);
	if (path == NULL)
		printf("error");
	else
	{
		write(1, path, ft_strlen(path));
		write(1, "\n", 1);
	}
	if (path)
		free(path);
}
