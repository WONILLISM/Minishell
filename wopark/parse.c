#include "../includes/minish.h"

void	parse_init(char *input, t_data *d, t_list **root)
{
	*root = ft_lstnew(NULL);
	d->last_node = *root;
	d->cmd = ft_calloc(1, sizeof(t_cmd));
	d->buf = ft_calloc(ft_strlen(input)+ 1, sizeof(char));

	d->input_idx = -1;
	d->cmd_idx = 0;
	d->buf_idx = 0;
}

int		parse_line(char *input)
{
	t_data	data;
	t_list	*root;
	char	*line;

	parse_init(input, &data, &root);
	int i = 0;
	while (data.cmd->argv[i])
	{
		printf("%s\n", data.cmd->argv[i]);
		i++;
	}
	return (0);
}
