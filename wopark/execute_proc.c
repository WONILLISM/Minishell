// #include "../includes/minish.h"

// int		check_builtin(char **argv)
// {
// 	if (!ft_strcmp(argv[0], "cd") || !ft_strcmp(argv[0], "echo") ||
// 	!ft_strcmp(argv[0], "pwd") || !ft_strcmp(argv[0], "export") ||
// 	!ft_strcmp(argv[0], "unset") || !ft_strcmp(argv[0], "env") ||
// 	!ft_strcmp(argv[0], "exit"))
// 		return (1);
// 	return (0);
// }

// void	execute_proc(t_list *cmd_root)
// {
// 	t_list	*cur_cmdlst;
// 	t_cmd	*tmp_cmd;

// 	cur_cmdlst = cmd_root->next;
// 	while (cur_cmdlst)
// 	{
// 		tmp_cmd = cur_cmdlst->content;
// 		if (tmp_cmd->argv[0])
// 		{
// 			if (tmp_cmd->redir == 1 && tmp_cmd->flag == 0)
// 			{
// 				// 리다이렉션 처리
// 				break ;
// 			}
// 			if ((check_builtin(tmp_cmd->argv) == 1) && tmp_cmd->flag == 0)
// 				execute_builtin(tmp_cmd);
// 			else
// 				execute_pipe();
// 		}
// 		cur_cmdlst = cur_cmdlst->next;
// 	}
// 	// free cmd_root
// }
