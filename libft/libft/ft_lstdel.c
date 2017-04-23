/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 15:34:52 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:13:34 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*next;

	if (!alst || !(*alst) || !del)
		return ;
	next = *alst;
	while (next)
	{
		next = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		ft_memdel((void**)alst);
		*alst = next;
	}
	*alst = NULL;
}
