/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 06:47:01 by rschramm          #+#    #+#             */
/*   Updated: 2017/03/20 10:53:34 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_n		**init_all(t_n **a, int fd)
{
	if (!a)
		a = (t_n **)ft_memalloc(sizeof(t_n *) * MAX_FD);
	a[fd] = (t_n *)ft_memalloc(sizeof(t_n));
	a[fd]->str = ft_strnew(0);
	a[fd]->r = 0;
	a[fd]->ret = 0;
	return (a);
}

int		find_ret(t_n *a)
{
	int c;

	c = 0;
	while (a->str[c] != '\0' && a->str[c] != '\n')
		c++;
	if (a->r > 0)
	{
		if (a->str[c] == '\n')
			return (c);
		else if (a->str[c] == '\0')
			return (-1);
	}
	if (a->str[c] == '\0')
		a->fin = 1;
	if (a->str[c + 1] == '\0')
		a->fin = 1;
	return (a->ret = c);
}

void	create_ret(t_n *a, char **line)
{
	char *ptr;

	if (a->r > 0)
	{
		*line = ft_strnxdup(a->str, 0, a->ret);
		ptr = ft_strndup(a->str, a->ret + 1);
		ft_strdel(&a->str);
		a->str = ft_strdup(ptr);
		ft_strdel(&ptr);
	}
	else
	{
		if (a->fin == 1)
		{
			*line = ft_strnxdup(a->str, 0, a->ret);
		}
		else
		{
			*line = ft_strnxdup(a->str, 0, a->ret);
			ptr = ft_strndup(a->str, a->ret);
			ft_strdel(&a->str);
			a->str = ft_strdup(ptr);
			ft_strdel(&ptr);
		}
	}
}

int		is_return(t_n *a, char **line, char *buff)
{
	a->ret = -1;
	buff[a->r] = '\0';
	if (a->r > 0)
		a->str = ft_strxjoin(a->str, buff, 1);
	if ((a->ret = find_ret(a)) > -1)
		create_ret(a, line);
	if (a->ret > -1)
		return (1);
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static t_n	**a;
	char		buff[BUFF_SIZE + 1];

	if (fd < 0 || !line || fd > MAX_FD)
		return (-1);
	if ((!a || !a[fd]) && !(a = init_all(a, fd)))
		return (-1);
	if (a[fd]->ret == -1 || a[fd]->fin == 1)
	{
		ft_mmurder(a, fd);
		*line = NULL;
		return (0);
	}
	while ((a[fd]->r = read(fd, buff, BUFF_SIZE)) != 0)
	{
		if (a[fd]->r < 0)
			return (-1);
		if ((is_return(a[fd], line, buff)) == 1)
			return (1);
	}
	is_return(a[fd], line, buff);
	if (a[fd]->fin == 1 && a[fd]->str[0] == '\0' && ft_mmurder(a, fd))
		return (0);
	return (1);
}
