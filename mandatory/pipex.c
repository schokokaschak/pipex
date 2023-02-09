/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:24:23 by akashets          #+#    #+#             */
/*   Updated: 2023/01/26 22:19:03 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && (n > 0))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

char	*find_path(char **envp)
{
	if (*envp == NULL)
		return ("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:");
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
	{
		write(2, ERR_INPUT, ft_strlen(ERR_INPUT));
		return (1);
	}
	if (pipe(pipex.fd) < 0)
		msg_err(ERR_PIPE);
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	if (pipex.pid1 > 0)
		second_child(pipex, argv, envp);
	ft_close(pipex);
	parent_free(&pipex);
	return (0);
}
