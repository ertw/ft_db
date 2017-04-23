/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_array_field                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	delete_db(char ***db)
{
	int x;
	int	y;

	x = 0;
	y = 0;
	while (db[y] != 0)
	{
		while (db[y][x] != 0)
		{
			ft_strdel(&db[y][x]);
			x++;
		}
		ft_strdel(&db[y][x]);
		x = 0;
		y++;
	}
}

char	***get_db(t_parse *meta, char **argv)
{
	char	***db;

	meta->rows = count_rows(argv[2]);
	meta->columns = count_columns(meta, argv[2]);
	db = fill_db(meta, argv[2]);
	return (db);
}

void	add_array_field(t_parse *meta, char **argv)
{
	char	***db;
	//char	***new;

	if ((access(argv[2], F_OK)) != -1)
	{
		ft_putstr("Database Access: Granted\n");
		if (argv[3])
		{
			db = get_db(meta, argv);
			display_db(meta, db);
			delete_db(db);
			//new = create_new_db(meta);
		}
		else
			ft_putstr("Need argument\n");
	}
	else
		ft_putstr("File error\n");
}