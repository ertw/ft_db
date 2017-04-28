/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <me@erik.tw>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	ls_cwd(t_parse *meta)
{
	char	buff[100];
	char	*path;
	char	*cwd;

	cwd = getcwd(buff, 100);
	path = ft_strjoin("/bin/ls ", cwd);
	meta->fd = popen(path, "r");
	ft_strdel(&path);
	while (fgets(buff, sizeof(buff) - 1, meta->fd) != NULL)
		printf("%s", buff);
	pclose(meta->fd);
}
