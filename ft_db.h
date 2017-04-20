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
# include <termios.h>

typedef struct		s_parse
{
	int				opt_l;
	int				cert_present;
}					t_parse;

typedef struct		s_data
{
	char			name[128];
	int				age;
}					t_data;

int					ft_strdelic(char *s1, char *s2, char delim);
void				user_login(t_parse *meta);

#endif
