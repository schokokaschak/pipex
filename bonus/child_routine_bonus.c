/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:34:48 by akashets          #+#    #+#             */
/*   Updated: 2023/01/19 16:56:26 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/pipex_bonus.h"

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

static void	ft_print_err(char *s1, char *s2)
{
	ft_putname_fd(s1, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(s2, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(ERR_CMD, STDERR);
}

void	the_child(t_pipex pipex, char *argv, char **envp)
{
	int	ex;

	pipex.cmd_args = parsing_str(argv);
	pipex.cmd = ft_get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	ex = execve(pipex.cmd, pipex.cmd_args, envp);
	if (ex < 0)
	{
		ft_print_err("pipipex", pipex.cmd_args[0]);
		child_free(&pipex);
		exit(127);
	}
}

void	last_child(t_pipex pipex, char *argv, char **envp, char **arg)
{
	int	ex;
	int	fout;

	waitpid(pipex.pid, NULL, WNOWAIT);
	fout = open(arg[pipex.argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000664);
	if (fout < 0)
		msg_err(ERR_OUTFILE);
	close(pipex.fd[1]);
	dup2(pipex.fd[0], 0);
	close(pipex.fd[0]);
	dup2(fout, STDOUT_FILENO);
	pipex.cmd_args = parsing_str(argv);
	pipex.cmd = ft_get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	ex = execve(pipex.cmd, pipex.cmd_args, envp);
	if (ex < 0)
	{
		ft_print_err("pipipex", pipex.cmd_args[0]);
		child_free(&pipex);
		exit(127);
	}
}
