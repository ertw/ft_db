/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_array_db.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		count_columns(t_parse *meta, char *source)
{
	char	*line;
	char	**split;
	int		fd;

	fd = open(source, O_RDONLY);
	get_next_line(fd, &line);
	split = ft_strsplit(line, ' ');
	meta->x = 0;
	while (split[meta->x])
		meta->x++;
	close(fd);
	return (meta->x);
}

int		count_rows(char *source)
{
	char	buff[4000];
	int		fd;
	int		r;
	int		rows;

	fd = open(source, O_RDONLY);
	r = read(fd, &buff, 3999);
	buff[r] = '\0';
	r = 0;
	rows = 0;
	while (buff[r] != '\0')
	{
		if (buff[r] == '\n')
			rows++;
		r++;
	}
	close(fd);
	return (rows);
}

char	***make_empty(t_parse *meta)
{
	char	***db;
	int		x;
	int		y;

	x = 0;
	y = 0;

	db = (char***)ft_memalloc(sizeof(char**) * (meta->columns + 1));
	db[meta->columns] = 0;
	meta->x = 0;
	while (meta->x < meta->columns)
	{
		db[meta->x] = (char**)ft_memalloc(sizeof(char*) * (meta->rows + 1));
		db[meta->x][meta->rows] = 0;
		meta->x++;
	}
	return (db);
}

char	***fill_db(t_parse *meta, char *source)
{
	char	***db;
	int		y;
	int		x;

	db = make_empty(meta);
	meta->fd = fopen(source, "r");
	meta->x = 0;
	x = 0;
	y = 0;
	while (x < meta->rows)
	{
		fscanf(meta->fd, "%s", meta->data);
		db[y][x] = ft_strdup(meta->data);
		y++;
		if (y % meta->columns == 0 && y != 0)
			x++;
		if (y >= meta->columns)
			y = 0;
	}
	fclose(meta->fd);
	return (db);
}

void	display_db(t_parse *meta, char ***db)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < meta->rows)
	{
		while (y < meta->columns)
		{
			ft_printf("| %s ", db[y][x]);
			y++;
		}
		ft_putstr("|\n");
		y = 0;
		x++;
	}
}

void	display_array_db(t_parse *meta, char **argv)
{
	char	***db;

	if ((access(argv[2], F_OK)) != -1)
	{
		if (meta->opt_l == 1)
		{
			ft_putstr("Mode: Array\n");
			meta->rows = count_rows(argv[2]);
			meta->columns = count_columns(meta, argv[2]);
			db = fill_db(meta, argv[2]);
			display_db(meta, db);
			delete_db(db);
		}
	}
	else
		ft_putstr("File error\n");
}
