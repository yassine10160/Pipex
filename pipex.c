/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassinefahfouhi <yassinefahfouhi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:06:27 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/02/03 13:01:16 by yassinefahf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void exit_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
void fill_args_for_exec(char **args, char *dest, char **split, char av)
{
	args[0] = dest;
	args[1] = split[1];
	args[2] = av;
	args[3] = NULL;
}
void fills_env_for_exec(char **env, char *dest, char **split, char av)
{
	env[0] = "PATH=/bin :/usr/bin";
	env[1] = NULL;
}
void exec_process(char **av, char *dest, char **split)
{
	char **args;
	char **env;

	args = malloc(4 * sizeof(char *));
	env = malloc(4 * sizeof(char *));
	fill_args_for_exec(args, dest, split, av[1]);
	fill_env_for_exec(env, dest, split, av[4]);
	if (execve(dest, args, env) == -1)
		exit_error("execve");
}
void child_handle(int *fd, char **av)
{
	int fd_o;
	char **split;
	char *dest;

	split = ft_split(av[2], ' ');
	if (!split[0])
		return;
	dest = ft_strjoin("/bin/", split[0]);
	if (!dest)
		return;
	fd_o = open(av[1], O_RDONLY, O_WRONLY);
	if (fd_o == -1)
		exit_error("open");
	dup2(fd_o, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	exec_process(av, dest, split);
}
int main(int ac, char **av)
{
	int fd[2];
	pid_t pid;

	if (ac == 5)
	{
		if (pipe(fd) == -1)
			exit_error("pipe");
		pid = fork();
		if (pid == -1)
			exit_error("fork");
		if (pid == 0)
			child_handle(fd, av);
		// else
		// main_handle(fd, av);
		waitpid(pid, NULL, 0);
	}
	else
		write(1, "argument error\n", 15);
	return (0);
}
