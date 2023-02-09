/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 10:11:33 by akashets          #+#    #+#             */
/*   Updated: 2023/01/27 00:02:41 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/pipex_bonus.h"

void	get_infile(char **argv, t_pipex *pipex)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
	{
		pipex->argc = 0;
		here_doc(argv[2], pipex);
	}
	else
	{
		pipex->argc = 0;
		pipex->infile = open(argv[1], O_RDONLY);
		if (pipex->infile < 0)
		{
			pipex->argc = 1;
			write(2, ERR_INFILE, ft_strlen(ERR_INFILE));
		}
	}
}

void	get_outfile(char *argv, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->outfile = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		pipex->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (pipex->outfile < 0)
	{
		msg_err(ERR_OUTFILE);
	}
}

void	here_doc(char *argv, t_pipex *pipex)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		msg_err(ERR_HEREDOC);
	while (1)
	{
		write(1, "heredoc> ", 9);
		if (get_next_line(0, &buf) < 0)
			exit(1);
		if (!ft_strncmp(argv, buf, ft_strlen(argv) + 1))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	pipex->infile = open(".heredoc_tmp", O_RDONLY);
	if (pipex->infile < 0)
	{
		unlink(".heredoc_tmp");
		msg_err(ERR_HEREDOC);
	}
}
