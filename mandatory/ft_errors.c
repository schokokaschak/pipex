/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:34:48 by akashets          #+#    #+#             */
/*   Updated: 2023/01/18 13:43:32 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/pipex.h"

void	msg_err(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}

void	ft_print_err(char *s1, char *s2)
{
	ft_putname_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(ERR_CMD, 2);
}
