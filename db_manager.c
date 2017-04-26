/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
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
	while (fgets(buff, sizeof(buff)-1, meta->fd) != NULL)
		printf("%s", buff);
	pclose(meta->fd);
}

void	db_manipulator(t_parse *meta, char *source)
{
	char	***db;

	db = get_db(meta, source);
	display_db(meta, db, source);
	delete_db(db);
}

void	db_open(t_parse *meta)
{
	ls_cwd(meta);
	ft_printf("Please type DB file name: \n");
	scanf("%s", meta->data);
	ft_printf("[.green.%s.] selected\n", meta->data);
	if ((access(meta->data, F_OK)) != -1)
	{
		ft_printf("Access [.green.Granted.]\n");
		db_manipulator(meta, meta->data);
	}
	else
	{
		ft_printf("Opps, something wrong with filename [.red.%s.]\n", meta->data);
		db_manager(meta);
	}
}

void	db_manager(t_parse *meta)
{
	int	x;

	x = 0;
	printf("Welcome to EZ-DB manager.\n");
	sleep(1);
	ft_printf("(1) [.green.Open Existing DB.]\n");
	ft_printf("(0) [.red.Exit.]\n");
	scanf("%d", &x);
	if (x == 0)
		return ;
	else if (x == 1)
		db_open(meta);
}
