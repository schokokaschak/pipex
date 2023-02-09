/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:25:15 by akashets          #+#    #+#             */
/*   Updated: 2023/02/09 21:45:29 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include	<fcntl.h>
# include	<stdio.h>
# include	<unistd.h>
# include	<sys/wait.h>
# include	<sys/types.h>
# include	<stdlib.h>
# include	<sys/uio.h>
# include	<string.h>
# include	"get_next_line.h"

# define ERR_INFILE "pipex: input: No such file or directory\n"
# define ERR_OUTFILE "pipex: output"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "command not found\n"
# define ERR_HEREDOC "pipex: here_doc"

typedef struct s_split {
	int		len;
	int		i;
	int		j;
	int		count;
}	t_split;

typedef struct s_pipex {
	pid_t	pid;
	char	*epath;
	int		ncmd;
	int		argc;
	int		pipe_n;
	int		*pipe;
	int		idd;
	int		infile;
	int		err;
	int		outfile;
	char	*paths;
	int		here_doc;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}		t_pipex;

void	create_pipes(t_pipex *pipex);
void	ft_print_err(char *s1, char *s2);
void	get_infile(char **argv, t_pipex *pipex);
void	get_outfile(char *argv, t_pipex *pipex);
void	here_doc(char *argv, t_pipex *pipex);
int		arg_check(char *arg, t_pipex *pipex);
void	start_the_show(t_pipex pipex, char **argv, char **envp);
void	ft_putname_fd(char const *s, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	parent_free(t_pipex *pipex);
void	msg_err(char *err);
void	child_free(t_pipex *pipex);
size_t	ft_strlen(char *s);
char	*ft_strdup(char *src);
char	**ft_split(char *s, char c);
char	*find_path(char **envp, t_pipex *pipex);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_get_cmd(char **paths, char *cmd);
void	ft_close(t_pipex *pipex);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	single_quota(char *str, char **res, t_split *tab);
void	double_quota(char *str, char **res, t_split *tab);
void	space_case(char *str, char **res, t_split *tab);
int		ft_tab_len(char const *s, char c, int i);
char	**ft_split2(const char *str);
void	child(t_pipex *pipex, char **argv, char **envp);

#endif
