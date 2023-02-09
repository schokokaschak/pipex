/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@student.42wolfsbur      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:31:21 by akashets          #+#    #+#             */
/*   Updated: 2023/01/18 14:13:17 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/pipex.h"

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
