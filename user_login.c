/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_login.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		cred_check(char *ptr, char *buff)
{
	int x;
	int start;

	x = 0;
	while (buff[x])
	{
		if (buff[x] == '$')
		{
			start = x + 1;
			if (ft_strdelic(ptr, buff + start, '\n'))
			{
				ft_strdel(&ptr);
				return (1);
			}
		}
		x++;
	}
	return (0);
}

int		handle_login(char *user, char *pass)
{
	int		fd;
	int		r;
	char	*ptr;
	char	buff[4000];

	fd = open("login.txt", O_RDONLY);
	r = read(fd, &buff, 3999);
	buff[r] = '\0';
	ptr = ft_strjoin(user, ">");
	ptr = ft_strxjoin(ptr, pass, 1);
	ptr = ft_strxjoin(ptr, "\n", 1);
	if ((cred_check(ptr, buff)))
		return (1);
	return (0);
}

int		login_certification(char *user, char *pass)
{
	int		x;
	FILE	*fd;
	time_t	current;

	x = 0;
	if ((handle_login(user, pass)) && (x = 1))
	{
		printf("Welcome to our database, %s.\n", user);
		fd = fopen("cert.ers", "w+");
		current = time(NULL);
		fprintf(fd, "$%s>%s\n%s", user, pass, asctime(gmtime(&current)));
	}
	else
		ft_putstr("Invalid username/Pass\n");
	return (x);
}

void	user_login(t_parse *meta)
{
	char	user[100];
	char	*pass;

	printf("Enter username: ");
	scanf(" %s", user);
	pass = getpass("Enter pass: ");
	if ((login_certification(user, pass)))
		meta->cert_present = 1;
	ft_strdel(&pass);
}
