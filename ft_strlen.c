/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yassinefahfouhi <yassinefahfouhi@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 23:33:49 by yassinefahf       #+#    #+#             */
/*   Updated: 2025/01/29 23:35:27 by yassinefahf      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t ft_strlen(char const *s)
{
	size_t i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}