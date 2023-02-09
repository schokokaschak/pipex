/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:16:27 by akashets          #+#    #+#             */
/*   Updated: 2023/01/20 17:39:46 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/pipex_bonus.h"

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
