/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@42wolfsburg.de>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:25:15 by akashets          #+#    #+#             */
/*   Updated: 2023/01/19 16:41:07 by akashets         ###   ########.fr       */
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

# define ERR_INFILE "pipex: input"
# define ERR_OUTFILE "pipex: output"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_CMD "command not found\n"
# define STDERR 2

typedef struct s_parsing {
	int		len;
	int		i;
	int		j;
	int		count;
}	t_parsing;

typedef struct s_pipex {
	pid_t	pid;
	int		ncmd;
	int		fd[2];
	int		infile;
	int		outfile;
	int		argc;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}		t_pipex;

void	start_the_show(t_pipex pipex, char **argv, char **envp);
void	split_pro(char *argv, char **envp, t_pipex pipex, int fin);
void	the_child(t_pipex pipex, char *argv, char **envp);
void	last_child(t_pipex pipex, char *argv, char **envp, char **arg);
void	ft_putname_fd(char const *s, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	parent_free(t_pipex *pipex);
void	msg_err(char *err);
void	child_free(t_pipex *pipex);
void	first_child(t_pipex pipex, char **argv, char **envp);
void	second_child(t_pipex pipex, char **argv, char **envp);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *src);
char	**ft_split(const char *s, char c);
char	*find_path(char **envp);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_get_cmd(char **paths, char *cmd);
void	ft_close(t_pipex pipex);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	single_quota(char *str, char **res, t_parsing *tab);
void	double_quota(char *str, char **res, t_parsing *tab);
void	space_case(char *str, char **res, t_parsing *tab);
int		ft_tab_len(char const *s, char c, int i);
char	**parsing_str(const char *str);

#endif
