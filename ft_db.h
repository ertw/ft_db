/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DB_H
# define FT_DB_H
# include "./libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <termios.h>

typedef struct		s_parse
{
	char			data[100];
	FILE			*fd;
	int				opt_l;
	int				opt_a;
	int				opt_r;
	int				opt_c;
	int				opt_x;
	int				opt_m;
	int				opt_d;
	int				columns;
	int				rows;
	int				cert_present;
	int				x;
	int				y;
}					t_parse;

typedef struct		s_data
{
	char			name[128];
	int				age;
}					t_data;

void				user_login(t_parse *meta);
void				add_array_column(t_parse *meta, char **argv);
void				display_array_db(t_parse *meta, char **argv);
int					count_columns(char *source);
int					count_rows(char *source);
char				***fill_db(t_parse *meta, char *source);
void				display_db(t_parse *meta, char ***db, char *name);
void				delete_db(char ***db);
void				remove_array_column(t_parse *meta, char **argv);
char				***get_db(t_parse *meta, char *source);
void				update_db(t_parse *meta, char ***db, char *file_name);
void				add_array_row(t_parse *meta, char **argv);
void				remove_array_row(t_parse *meta, char **argv);
void				modify_array_cell(t_parse *meta, char **argv);
void				dispatch_manager(t_parse *meta, char **argv);
void				db_manager(t_parse *meta);
char				***add_row(t_parse *meta, char ***db, char *content);
void				db_manipulator(t_parse *meta, char *source);
void				db_open(t_parse *meta);

#endif
