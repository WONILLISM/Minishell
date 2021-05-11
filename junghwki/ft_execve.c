#include "../includes/minish.h"

void	ft_execve(t_cmd *cmd)
{
	execve("/bin/ls", cmd->argv, NULL);
}
// execve(const char *path, char *const argv[], char *const envp[])