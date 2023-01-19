/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:16:27 by akashets          #+#    #+#             */
/*   Updated: 2023/01/19 12:14:59 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/pipex_bonus.h"

void	parent_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
	close(pipex->infile);
	close(pipex->outfile);
}

void	child_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd);
	free(pipex->cmd_args);
	close(pipex->infile);
	close(pipex->outfile);
}

void	msg_err(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}

void	ft_close(t_pipex pipex)
{
	close(pipex.fd[0]);
	close(pipex.fd[1]);
}
