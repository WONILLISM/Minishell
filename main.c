#include "includes/minish.h"

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
		*(*input + idx) = buf;
		idx++;
		*input = realloc(*input, cnt + 1);
		cnt++;
	}
}

int		main(int argc, char **argv, char **envv)
{
	char	*input;

	while (1)
	{
		get_input(&input);
	}
	return (0);
}
