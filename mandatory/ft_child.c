/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:34:48 by akashets          #+#    #+#             */
/*   Updated: 2023/01/27 00:13:35 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/pipex.h"

char	*ft_get_cmd(char **paths, char *cmd)
{
	char	*buf;
	char	*com;
	int		i;

	i = 0;
	if (!strncmp(cmd, "/", 1))
		return (cmd);
	while (paths[i])
	{
		buf = ft_strjoin(paths[i], "/");
		com = ft_strjoin(buf, cmd);
		free(buf);
		if (access(com, 0) == 0)
			return (com);
		free(com);
		i++;
	}
	return (0);
}

void	first_child(t_pipex pipex, char **argv, char **envp)
{
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
	{	
		parent_free(&pipex);
		msg_err(ERR_INFILE);
	}
	close(pipex.fd[0]);
	dup2(pipex.fd[1], STDOUT_FILENO);
	close(pipex.fd[1]);
	dup2(pipex.infile, STDIN_FILENO);
	pipex.cmd_args = ft_split2(argv[2]);
	pipex.cmd = ft_get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		ft_print_err(argv[0], pipex.cmd_args[0]);
		child_free(&pipex);
		parent_free(&pipex);
		exit(127);
	}
	if (execve(pipex.cmd, pipex.cmd_args, envp) < 0)
		exit(EXIT_FAILURE);
}

void	second_child(t_pipex pipex, char **argv, char **envp)
{
	waitpid(pipex.pid1, NULL, WNOWAIT);
	pipex.outfile = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0000664);
	if (pipex.outfile < 0)
		msg_err(ERR_OUTFILE);
	close(pipex.fd[1]);
	dup2(pipex.fd[0], STDIN_FILENO);
	close(pipex.fd[0]);
	dup2(pipex.outfile, STDOUT_FILENO);
	pipex.cmd_args = ft_split2(argv[3]);
	pipex.cmd = ft_get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		ft_print_err(argv[0], pipex.cmd_args[0]);
		child_free(&pipex);
		parent_free(&pipex);
		exit(127);
	}
	if (execve(pipex.cmd, pipex.cmd_args, envp) < 0)
		exit(EXIT_FAILURE);
}
