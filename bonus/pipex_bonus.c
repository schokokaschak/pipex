/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:24:23 by akashets          #+#    #+#             */
/*   Updated: 2023/02/09 22:12:36 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/pipex_bonus.h"

static void	sub_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

char	*find_path(char **envp, t_pipex *pipex)
{
	pipex->epath = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:";
	if (*envp == NULL)
		return (pipex->epath);
	while (ft_strncmp(*envp, "PATH", 4))
		envp++;
	return (*envp + 5);
}

void	start_the_show(t_pipex p, char **argv, char **envp)
{
	p.pid = fork();
	if (p.pid == 0 && p.idd != p.ncmd - 1)
	{
		if (p.idd == 0)
			sub_dup2(p.infile, p.pipe[1]);
		else
			sub_dup2(p.pipe[2 * p.idd - 2], p.pipe[2 * p.idd + 1]);
		ft_close(&p);
		p.cmd_args = ft_split2(argv[2 + p.here_doc + p.idd]);
		p.cmd = ft_get_cmd(p.cmd_paths, p.cmd_args[0]);
		if (!p.cmd)
		{
			ft_print_err(argv[0], p.cmd_args[0]);
			child_free(&p);
			parent_free(&p);
			exit(127);
		}
		if (execve(p.cmd, p.cmd_args, envp) < 0)
		{
			p.err = 1;
			exit(EXIT_FAILURE);
		}
	}	
	if (p.pid > 0 && p.idd == p.ncmd - 1)
	{
		sub_dup2(p.pipe[2 * p.idd - 2], p.outfile);
		ft_close(&p);
		p.cmd_args = ft_split2(argv[2 + p.here_doc + p.idd]);
		p.cmd = ft_get_cmd(p.cmd_paths, p.cmd_args[0]);
		if (!p.cmd)
		{
			ft_print_err(argv[0], p.cmd_args[0]);
			child_free(&p);
			parent_free(&p);
			exit(127);
		}
		if (execve(p.cmd, p.cmd_args, envp) < 0)
		{
			exit(EXIT_FAILURE);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < arg_check(argv[1], &pipex))
	{
		write(2, ERR_INPUT, ft_strlen(ERR_INPUT));
		return (1);
	}
	get_infile(argv, &pipex);
	get_outfile(argv[argc - 1], &pipex);
	pipex.ncmd = argc - 3 - pipex.here_doc;
	pipex.pipe_n = 2 * (pipex.ncmd - 1);
	pipex.pipe = (int *)malloc(sizeof(int) * pipex.pipe_n);
	if (!pipex.pipe)
		msg_err(ERR_PIPE);
	pipex.paths = find_path(envp, &pipex);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	create_pipes(&pipex);
	pipex.err = 0;
	pipex.idd = -1 + pipex.argc;
	while (++(pipex.idd) < pipex.ncmd)
		start_the_show(pipex, argv, envp);
	ft_close(&pipex);
	waitpid(-1, NULL, 0);
	parent_free(&pipex);
	return (0);
}
