/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:21:39 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/03/07 18:26:10 by yafahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# define CHILD 0
# define PARENT 1
# define INFILE 2
# define OUTFILE 3
typedef struct s_process
{
	int		fd[2];
	pid_t	pid[2];
	char	**env;
	int		file;
} t_process;

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_right_path(char **env, char *cmd);
void	exit_error(char *s);
void	exec_process(char **env, char *path, char **split);
void	free_tab_str(char **s);

#endif