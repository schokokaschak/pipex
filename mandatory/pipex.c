/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:24:23 by akashets          #+#    #+#             */
/*   Updated: 2023/01/18 16:16:20 by akashets         ###   ########.fr       */
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
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		msg_err(ERR_INPUT);
	if (pipe(pipex.fd) < 0)
		msg_err(ERR_PIPE);
	if (*envp == NULL)
		pipex.paths = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:";
	else
		pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	if (pipex.pid2 > 0)
		second_child(pipex, argv, envp);
	parent_free(&pipex);
	ft_close(pipex);
	return (EXIT_SUCCESS);
}
