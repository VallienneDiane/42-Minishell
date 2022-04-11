/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:05:20 by amarchal          #+#    #+#             */
/*   Updated: 2022/03/24 17:00:20 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	printf("New_content : %s\n", new->content);
	if (!*alst)
		*alst = new;
	else
	{
		last = ft_lstlast(*alst);
		new->previous = last;
		last->next = new;
	}
}
