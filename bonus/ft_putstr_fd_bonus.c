/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@student.42wolfsbur      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:31:21 by akashets          #+#    #+#             */
/*   Updated: 2023/01/19 12:15:07 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/pipex_bonus.h"

void	ft_putstr_fd(char const *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{	
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putname_fd(char const *s, int fd)
{
	int	i;

	i = 2;
	while (s[i] != '\0')
	{	
		write(fd, &s[i], 1);
		i++;
	}
}
