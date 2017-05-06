/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_array_db_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewilliam <me@erik.tw>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		count_columns(char *source)
{
	char	*line;
	char	**split;
	FILE	*file;
	int		x;
	size_t	bufsize;

	line = NULL;
	x = 0;
	bufsize = 0;
	file = fopen(source, "r");
	getline(&line, &bufsize, file);
	split = ft_strsplit(line, ' ');
	while (split[x])
		x++;
	fclose(file);
	ft_strdel(&line);
	bufsize = 0;
	while (split[bufsize])
		ft_strdel(&split[bufsize++]);
	ft_memdel((void*)&split);
	return (x);
}

int		count_rows(char *source)
{
	char	buff[1024];
	FILE	*file;
	int		r;
	int		rows;

	file = fopen(source, "r");
	r = fread(buff, 1, 1023, file);
	buff[r] = '\0';
	r = 0;
	rows = 0;
	while (buff[r] != '\0')
	{
		if (buff[r] == '\n')
			rows++;
		r++;
	}
	fclose(file);
	return (rows);
}

char	***make_empty(t_parse *meta)
{
	char	***db;
	int		z;

	db = (char***)ft_memalloc(sizeof(char**) * (meta->columns + 1));
	db[meta->columns] = 0;
	z = 0;
	while (z < meta->columns)
	{
		db[z] = (char**)ft_memalloc(sizeof(char*) * (meta->rows + 1));
		db[z][meta->rows] = 0;
		z++;
	}
	return (db);
}

char	***fill_db(t_parse *meta, char *source)
{
	char	***db;
	int		y;
	int		x;
	char	buf[128];

	db = make_empty(meta);
	meta->fd = fopen(source, "r");
	x = 0;
	y = 0;
	while (x < meta->rows)
	{
		fscanf(meta->fd, "%s", buf);
		db[y][x] = ft_strdup(buf);
		y++;
		if (y >= meta->columns)
		{
			x++;
			y = 0;
		}
	}
	fclose(meta->fd);
	return (db);
}
