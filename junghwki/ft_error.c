/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghwki <junghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:24:31 by junghwki          #+#    #+#             */
/*   Updated: 2021/06/29 19:10:09 by junghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void		ft_error(int err_nbr, int exit_status)
{
	char	*err_str;

	err_str = strerror(err_nbr);
	g_archive.exit_stat = exit_status;
	write(2, ": ", 2);
	write(2, err_str, ft_strlen(err_str));
	write(2, "\n", 1);
}

void		err_msg_print(char *str, int exit_stat)
{
	g_archive.exit_stat = exit_stat;
	write(2, str, ft_strlen(str));
}