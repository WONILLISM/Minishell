#include "../includes/minish.h"

int			ft_strcmp(const char *s1, const char *s2)
{
	int		idx;

	idx = 0;
	while (s1[idx] || s2[idx])
	{
		if ((s1[idx] != s2[idx]) || (s1[idx] == '\0') || (s2[idx] == '\0'))
			return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
		idx++;
	}
	return (0);
}

void		ft_echo(char **str)
{
	int		idx;
	int		n_flag;

	idx = 1;
	n_flag = 0;
	while (!(ft_strcmp(str[idx], "-n")))
	{
		n_flag = 1;
		idx++;
	}
	while (str[idx])
	{
		printf("%s", str[idx]);
		idx++;
		if (str[idx])
			printf(" ");
		else if (!(str[idx]) && !n_flag)
			printf("\n");
	}
}
/*
**	junghwki
*/
int			main(void)
{
	char	**str;

	str[0] = "echo";
	str[1] = "-n";
	str[2] = "hi";
	str[3] = "hi_im_echo";
	str[4] = "fuck_you_minishellaasdasdasdasd";
	str[5] = NULL;
	ft_echo(str);
	return (0);
}