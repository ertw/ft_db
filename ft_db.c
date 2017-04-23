/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:55:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:10:43 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	cert_check(t_parse *meta)
{
	if ((access("cert.ers", F_OK)) != -1)
	{
		meta->cert_present = 1;
		ft_putstr("Certificate Status: good\n");
	}
	else
	{
		meta->cert_present = 0;
		ft_putstr("Certificate Status: meh :[\n");
	}
}

void	parse_args(int argc, char **argv, t_parse *meta)
{
	int	c;

	while ((c = getopt(argc, argv, "-al")) != -1)
	{
		if (c == 'l')
			meta->opt_l = 1;
		else if (c == 'a')
			meta->opt_a = 1;
		else
		{
			printf("EZ-DB: %c : invalid option\n", c);
			ft_putstr("usage: EZ-DB [-al] [...]\n");
			break ;
		}
	}
	cert_check(meta);
}

void	dispatch_manager(t_parse *meta, char **argv)
{
	if (meta->opt_a == 1)
	{
		ft_putstr("put add array function here\n");
		add_array_field(meta, argv);
	}
	if (meta->opt_l == 1)
		display_array_db(meta, argv);
	//add fork function here for manual editing through vim
	//if(meta->opt_z == 1)
	//    fork_with_vim(meta, argv);
}

int		main(int argc, char **argv)
{
	t_parse meta;

	if (argc == 1)
		ft_putstr("usage: EZ-DB [-l] [...]\n");
	else
		parse_args(argc, argv, &meta);
	if (meta.cert_present == 0)
		user_login(&meta);
	else
		dispatch_manager(&meta, argv);
	return (0);
}
