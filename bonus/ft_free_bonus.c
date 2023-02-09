/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 17:16:27 by akashets          #+#    #+#             */
/*   Updated: 2023/01/20 17:39:46 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/pipex_bonus.h"

void	parent_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->infile);
	close(pipex->outfile);
	if (pipex->here_doc)
		unlink(".heredoc_tmp");
	while (pipex->cmd_paths[i])
	{
		free(pipex->cmd_paths[i]);
		i++;
	}
	free(pipex->cmd_paths);
	free(pipex->pipe);
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
}

void	ft_close(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_n))
	{
		close(pipex->pipe[i]);
		i++;
	}
}
