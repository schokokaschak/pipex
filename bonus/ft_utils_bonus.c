/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:34:48 by akashets          #+#    #+#             */
/*   Updated: 2023/01/24 17:23:29 by akashets         ###   ########.fr       */
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

int	arg_check(char *arg, t_pipex *pipex)
{
	if (arg && !ft_strncmp("here_doc", arg, 9))
	{
		pipex->here_doc = 1;
		return (6);
	}
	else
	{
		pipex->here_doc = 0;
		return (5);
	}
}

void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->ncmd - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			parent_free(pipex);
		i++;
	}
}

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
