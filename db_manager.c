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
	ft_strdel(&path);
	while (fgets(buff, sizeof(buff)-1, meta->fd) != NULL)
		printf("%s", buff);
	pclose(meta->fd);
}

void	add_row_gui(t_parse *meta, char *source)
{
	char	buff[100];

	printf("Please type in content for new cells\n");
	scanf("%s", buff);
	add_array_row(meta, source, buff);
	db_manipulator(meta, source);
}

void	response_manager(t_parse *meta, char ***db, char *source, char *input)
{
	printf("%s\n", source);
	if (input[0] == '1')
		add_row_gui(meta, source);
	//else if (selection[0] == '2')
	//else if (selection[0] == '3')
	//else if (selection[0] == '4')
	//else if (selection[0] == '5')
	else if (input[0] == '6')
	{
		display_db(meta, db, source);
		db_manipulator(meta, source);
	}
	else if (input[0] == '7')
		db_open(meta);
	else if (input[0] == '0')
		return ;
}

void	db_manipulator(t_parse *meta, char *source)
{
	char	***db;
	char	buff[100];

	db = get_db(meta, source);
	display_db(meta, db, source);
	ft_printf("** EZ-DB Options **\n");
	ft_printf("(1) [.green.Add.] [.cyan.row.]\n");
	ft_printf("(2) [.green.Add.] [.magenta.column.]\n");
	ft_printf("(3) [.yellow.Modify.] individual cell\n");
	ft_printf("(4) [.red.Remove.] [.cyan.row.]\n");
	ft_printf("(5) [.red.Remove.] [.magenta.column.]\n");
	ft_printf("(6) [.blue.Reprint.] DB\n");
	ft_printf("(7) Open a different DB\n");
	ft_printf("(0) Quit\n");
	ft_printf("Please make a selection\n");
	scanf("%s", buff);
	response_manager(meta, db, source, buff);
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
		printf("%s\n", meta->data);
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
