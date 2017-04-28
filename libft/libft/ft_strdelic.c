/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <me@erik.tw>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 17:12:28 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/10 21:56:54 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_strdelic(char *s1, char *s2, char delim)
{
	int c;

	c = 0;
	while (s1[c] == s2[c] && s1[c] != '\0')
	{
		if (s1[c + 1] == delim || s2[c + 1] == delim)
			break ;
		c++;
	}
	if (s1[c + 1] == s2[c + 1])
		return (1);
	return (0);
}
