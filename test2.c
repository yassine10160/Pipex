/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassinefahfouhi <yassinefahfouhi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:07:50 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/02/01 20:50:02 by yassinefahf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int main(int ac, char **av)
{
	char *dest;
	char **split;

	if (ac == 5)
	{
		pid_t pid1;
		pid_t pid2;
		int fd[2];

		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		split = ft_split(av[1], ' ');
		dest = ft_strjoin("/bin/", split[0]);
		// printf("dest: %s\n", dest);
		pid1 = fork();
		if (pid1 == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid1 == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			char *args[] = {dest, split[1], av[2], NULL};
			char *env[] = {"PATH=/bin: /usr/bin", NULL};
			close(fd[1]);
			execve(dest, args, env);
		}
		pid2 = fork();
		if (pid2 == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid2 == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[1]);
			split = ft_split(av[3], ' ');
			dest = ft_strjoin("/bin/", split[0]);
			char *args[] = {dest, split[1], av[4], NULL};
			char *env[] = {"=PATH=/bin: /usr/bin", NULL};
			close(fd[0]);
			execve(dest, args, env);
		}
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	return (0);
}
