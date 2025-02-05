/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 19:06:27 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/02/05 15:50:18 by yafahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void exit_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
void fill_args_for_exec(char **args, char *path, char **split, char *av)
{
	args[0] = path;
	args[1] = split[1];
	args[2] = av;
	args[3] = NULL;
}
void fill_env_for_exec(char **env)
{
	env[0] = "PATH=/bin :/usr/bin";
	env[1] = NULL;
}
void exec_process(char *av, char *path, char **split)
{
	char **args;
	char **env;

	args = malloc(4 * sizeof(char *));
	env = malloc(2 * sizeof(char *));
	fill_args_for_exec(args, path, split, av);
	fill_env_for_exec(env);

	if (execve(path, args , env) == -1)
		exit_error("execve");
}
void child_handle(int fd[2], char **av, int infile)
{
	char **split;
	char *path;

	split = ft_split(av[2], ' ');
	if (!split[0])
		return;
	path = ft_strjoin("/bin/", split[0]);
	if (!path)
		return;
	// fd_o = open(av[1], O_RDONLY);
	// if (fd_o == -1)
		// exit_error("open");
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	printf("ici\n");
	close(fd[1]);
	exec_process(av[1], path, split);
}

void main_handle(int *fd, char **av)
{
	int fd_o;
	char **split;
	char *path;
	int	pid;

	fd_o = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	// printf("open value: %d\n", fd_o);
	if (fd_o == -1)
		exit_error("open");
	split = ft_split(av[3], ' ');
	if (!split[0])
		return;
	path = ft_strjoin("/bin/", split[0]);
	if (!path)
		return;
	dup2(fd[0], STDIN_FILENO);
	dup2(fd_o, STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
		exec_process(av[4], path, split);
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		close(fd[0]);
		close(fd_o);
	}
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
		{
			int	infile;
			
			infile = open(av[1], O_RDONLY);
			if (infile == -1)
				exit_error("open");
			child_handle(fd, av, infile);
			close(infile);
		}
		else
		{
			waitpid(pid, NULL, 0);
			main_handle(fd, av);
		}
	}
	else
		write(1, "argument error\n", 15);
	return (0);
}
