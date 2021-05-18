#include "../includes/minish.h"

void	execute_builtin(t_list *cmd_root)
{
	t_list	*temp;
	t_cmd	*temp_cmd;

	temp = cmd_root->next;
	while (temp)
	{
		temp_cmd = temp->content;
		if (ft_strcmp(temp_cmd->argv[0], "cd") == 0)
		{
			ft_cd(temp_cmd);
		}
		else if (ft_strcmp(temp_cmd->argv[0], "echo") == 0)
		{
			ft_echo(temp_cmd);
		}
		else if (ft_strcmp(temp_cmd->argv[0], "pwd") == 0)
		{
			ft_pwd();
		}
		else if (ft_strcmp(temp_cmd->argv[0], "export") == 0)
		{
			if (!temp_cmd->argv[1])
				export_lst_print();
			else
				export_add(temp_cmd);
		}
		else if (ft_strcmp(temp_cmd->argv[0], "unset") == 0)
		{
			ft_unset(temp_cmd);
		}
		else if (ft_strcmp(temp_cmd->argv[0], "env") == 0)
		{
			env_lst_print();
		}
		else if (ft_strcmp(temp_cmd->argv[0], "exit") == 0)
		{
			exit(0);
		}
		else
		{
			ft_execve(temp_cmd);
			// write(1, temp_cmd->argv[0], ft_strlen(temp_cmd->argv[0]));
			// write(1, ": command not found\n", 20);
		}
		temp = temp->next;
	}
}
