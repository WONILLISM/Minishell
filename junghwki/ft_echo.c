#include "../includes/minish.h"

void		ft_echo(t_cmd *cmd)
{
	int		idx;
	int		n_flag;

	idx = 1;
	n_flag = 0;
	while (ft_strcmp(cmd->argv[idx], "-n") == 0)
	{
		n_flag = 1;
		idx++;
	}
	while (cmd->argv[idx])
	{
		printf("%s", cmd->argv[idx]);
		idx++;
		if (cmd->argv[idx])
			printf(" ");
		else if (!n_flag)
			printf("\n");
	}
}
int			main(void)
{
	char	**str;

	str[0] = "echo";
	str[1] = "-na";
	str[2] = "hi";
	str[3] = "hi_im_echo";
	str[4] = "fuck_you_minishell";
	str[5] = NULL;
	ft_echo(str);
	return (0);
}