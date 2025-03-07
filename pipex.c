/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:13:28 by yafahfou          #+#    #+#             */
/*   Updated: 2025/03/07 18:25:23 by yafahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void exec_process(char **env, char *path, char **split)
{
	if (execve(path, split, env) == -1)
		exit_error("execve");
}

int	safe_open(char *file, int type)
{
	int	fd;

	if (type == INFILE)
	{
		if ((fd = open(file, O_RDONLY)) == -1)
			exit_error("open");
	}
	else
	{
		if ((fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777)) == -1)
			exit_error("open");
	}
	return (fd);
}

void	right_duplicate(t_process *process, int mode)
{
	if (mode == CHILD)
	{
		close(process->fd[0]);
		dup2(process->file, STDIN_FILENO);
		dup2(process->fd[1], STDOUT_FILENO);
		close(process->fd[1]);
		close(process->file);
	}
	else
	{
		dup2(process->fd[0], STDIN_FILENO);
		dup2(process->file, STDOUT_FILENO);
		close(process->fd[1]);
		close(process->file);
	}
}

void	free_tab_str(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
}

void	process_handle(t_process *process, char **env, char *av, int mode)
{
	char	**split;
	char	*path;

	split = ft_split(av, ' ');
	if (!split[0])
	{
		free_tab_str(split);
		return ;
	}
	path = get_right_path(env, split[0]);
	if (!path)
	{
		free_tab_str(split);
		return;
	}
	right_duplicate(process, mode);
	exec_process(env, path, split);
}

void	close_files(t_process *process)
{
	close(process->fd[0]);
	close(process->fd[1]);
	close(process->file);
}

void	wait_process(t_process *process)
{
	waitpid(process->pid[1], NULL, 0);
	waitpid(process->pid[0], NULL, 0);
}

void	main_handle(t_process *process, char **av, char **env)
{
	if ((process->pid[0] = fork()) == -1)
			exit_error("fork");
		if (process->pid[0] == 0)
		{
			process->file = safe_open(av[1], INFILE);
			process_handle(process, env, av[2], CHILD);
		}
		if ((process->pid[1] = fork()) == -1)
			exit_error("fork");
		if (process->pid[1] == 0)
		{
			process->file = safe_open(av[4], OUTFILE);
			process_handle(process, env, av[3], PARENT);
		}
		close_files(process);
		wait_process(process);
}

int	main(int ac, char **av, char **env)
{
	t_process	process;

	process.file = -1;
	if (ac == 5)
	{
		if (pipe(process.fd) == -1)
			exit_error("pipe");
		main_handle(&process, av, env);
	}
	else
		write(1, "argument error\n", 15);
	return (0);
}
