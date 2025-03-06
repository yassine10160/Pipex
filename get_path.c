/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yafahfou <yafahfou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 18:08:36 by yafahfou          #+#    #+#             */
/*   Updated: 2025/03/06 18:51:17 by yafahfou         ###   ########.fr       */
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

char	*check_right_path(char **env, char *cmd)
{
	int		i;
	char	**split;
	char	*path;
	char	*right_path;

	i = 0;
	cmd = ft_strjoin("/", cmd);
	path = get_path(env);
	split = ft_split(path, ':');
	while (split[i])
	{
		right_path = ft_strjoin(split[i], cmd);
		if (access(right_path, F_OK) == 0)
			return(right_path);
		i++;
	}
	return (NULL);
}
