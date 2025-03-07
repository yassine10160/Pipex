/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:08:36 by yafahfou          #+#    #+#             */
/*   Updated: 2025/03/07 18:29:03 by yafahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_right_path(char **env, char *cmd)
{
	int		i;
	char	**split;
	char	*path;
	char	*right_path;

	i = -1;
	cmd = ft_strjoin("/", cmd);
	if (!cmd)
		return (NULL);
	path = get_path(env);
	if (!path)
		exit_error("command not found");
	split = ft_split(path, ':');
	if (!split)
	{
		free_tab_str(split);
		
	}
	while (split[++i])
	{
		right_path = ft_strjoin(split[i], cmd);
		if (access(right_path, F_OK) == 0)
			return(right_path);
	}
	return (NULL);
}
