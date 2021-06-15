#include "../includes/minish.h"

int		parse_error_check(t_data *data)
{
	t_cmd	*tmp;

	tmp = data->last_node->content;
	if (!tmp)
		return (SUCCESS);
	if (data->cmd->quote || tmp->flag == 1)
		return (ERROR);
	if (g_archive.parse_error == ERROR)
		return (ERROR);
	return (SUCCESS);
}
int		parse_error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	g_archive.exit_stat = 1;
	return (0);
}

