#include "includes/minish.h"

char	*realloc_input(char *ptr, size_t size)
{
	char	*ret;

	ret = (char *)malloc(size);
	if (!ret)
		return (0);
	ft_memmove(ret, ptr, size);
	free(ptr);
	return (ret);
}
void	get_input(char **input)
{
	int		r_nbr;
	int		idx;
	int		cnt;
	char	buf;

	idx = 0;
	cnt = 1;
	*input = malloc(1);

	while (1)
	{
		r_nbr = read(0, &buf, 1);
		if (r_nbr == 0 || buf == '\n')
			break;
		if (idx && *(*input + idx - 1) == ' ')
		{
			if (buf == ' ')
				continue ;
		}
		*(*input + idx) = buf;
		idx++;
		*input = realloc_input(*input, cnt + 1);
		cnt++;
	}
}

int		main(int argc, char **argv, char **envv)
{
	char	*input;

	while (1)
	{
		get_input(&input);
		parse_line(input);
	}
	return (0);
}
