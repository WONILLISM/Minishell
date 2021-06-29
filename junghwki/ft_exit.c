/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghwki <junghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:24:17 by junghwki          #+#    #+#             */
/*   Updated: 2021/06/29 19:29:52 by junghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

long long		ft_atoll(const char *str)
{
	int			sign;
	long long	ret;

	sign = 1;
	ret = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		ret = ret * 10 + sign * (*str - '0');
		str++;
	}
	return (ret);
}

int				char_cmp(char a, char b)
{
	if (a == b)
		return (1);
	else if (a > b)
		return (0);
	else
		return (-1);
}

int				arg_check(char *str)
{
	char		*long_long_max;
	int			str_idx;
	int			idx;
	int			check_ret;

	long_long_max = "9223372036854775807";
	str_idx = 0;
	idx = 0;
	if (str[str_idx] == '+' || str[str_idx] == '-')
		str_idx++;
	if (ft_strlen(&str[str_idx]) > 19)
		return (-1);
	else if (ft_strlen(&str[str_idx]) == 19)
		while (str[str_idx])
		{
			check_ret = char_cmp(long_long_max[idx], str[str_idx]);
			if (check_ret == -1)
				return (-1);
			else if (check_ret == 0)
				return (1);
			else if (check_ret == 1)
			{
				idx++;
				str_idx++;
			}
		}
	return (1);
}

void			ft_exit(t_cmd *cmd)
{
	int			idx;

	idx = 0;
	if (!(cmd->argv[1]))
	{
		if (!cmd->flag)
			write(2, "exit\n", 5);
		exit(g_archive.exit_stat);
	}
	if (cmd->argv[2])
		err_msg_print("minish: exit: too many arguments\n", 1);
	else
	{
		if (cmd->argv[1][idx] == '+' || cmd->argv[1][idx] == '-')
			idx++;
		while (cmd->argv[1][idx])
		{
			if (!ft_isdigit(cmd->argv[1][idx]) || (arg_check(cmd->argv[1]) < 0))
			{
				g_archive.exit_stat = 255;
				write(2, "minish: exit: ", 14);
				write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
				err_msg_print(": numeric argument required\n", 255);
				exit(g_archive.exit_stat);
			}
			idx++;
		}
		g_archive.exit_stat = ft_atoll(cmd->argv[1]);
		write(1, "exit\n", 5);
		exit(g_archive.exit_stat);
	}
}
