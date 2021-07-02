/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wopark <wopark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 16:31:32 by wopark            #+#    #+#             */
/*   Updated: 2021/07/02 16:36:13 by wopark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

int		parse_error_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
	g_archive.exit_stat = 1;
	return (0);
}
