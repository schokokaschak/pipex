/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:24:23 by akashets          #+#    #+#             */
/*   Updated: 2023/01/19 16:49:09 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/pipex_bonus.h"

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

void	split_pro(char *argv, char **envp, t_pipex pipex, int fin)
{
	if (pipe(pipex.fd) < 0)
		msg_err(ERR_PIPE);
	pipex.pid = fork();
	if (pipex.pid > 0)
	{
		close(pipex.fd[1]);
		dup2(pipex.fd[0], 0);
		waitpid(pipex.pid, NULL, WNOWAIT);
	}
	else
	{
		close(pipex.fd[0]);
		dup2(pipex.fd[1], 1);
		if (fin == 0)
			exit(1);
		else
			the_child(pipex, argv, envp);
	}	
}

void	start_the_show(t_pipex pipex, char **argv, char **envp)
{
	int	fin;

	pipex.ncmd = 2;
	fin = open(argv[1], O_RDONLY);
	if (fin < 0)
		msg_err(ERR_INFILE);
	dup2(fin, 0);
	split_pro(argv[2], envp, pipex, fin);
	while (++pipex.ncmd < pipex.argc - 2)
		split_pro(argv[pipex.ncmd], envp, pipex, 1);
	last_child(pipex, argv[pipex.ncmd], envp, argv);
}	

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		msg_err(ERR_INPUT);
	if (*envp == NULL)
		pipex.paths = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:";
	else
		pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.argc = argc;
	start_the_show(pipex, argv, envp);
	parent_free(&pipex);
	ft_close(pipex);
	return (EXIT_SUCCESS);
}
