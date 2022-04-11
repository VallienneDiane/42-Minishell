/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chained_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:31:02 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/29 16:40:31 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;
	t_list	*actual;

	temp = lst;
	actual = lst;
	while (temp)
	{
		actual = temp;
		temp = temp->next;
	}
	return (actual);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (!*alst)
		*alst = new;
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
	}
}

t_list	*ft_lstnew(char *content, int type, int block)
{
	t_list	*newlist;
	
	newlist = malloc(sizeof(t_list));
	if (!newlist)
		return (NULL);
	newlist->content = content;
	newlist->type = type;
	newlist->block = block;
	newlist->next = NULL;
	return (newlist);
}

void	ft_print_list(t_list *list)
{
	while (list)
	{
		printf("\033[93m%s | type %d | block %d\n\033[0m", list->content, list->type, list->block);
		list = list->next;
	}
}
