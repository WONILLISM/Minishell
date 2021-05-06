#include "../includes/minish.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int	idx;

	idx = 0;
	while (s1[idx] || s2[idx])
	{
		if ((s1[idx] != s2[idx]) || (s1[idx] == '\0') || (s2[idx] == '\0'))
			return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
		idx++;
	}
	return (0);
}