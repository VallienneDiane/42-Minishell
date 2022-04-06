/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:31:02 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/06 17:28:26 by dvallien         ###   ########.fr       */
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
		new->previous = last;
		last->next = new;
	}
}

t_list	*ft_lstnew(void *content, void *type, int block)
{
	t_list	*newlist;

	newlist = malloc(sizeof(t_list));
	if (!newlist)
		return (NULL);
	newlist->content = content;
	newlist->type = type;
	newlist->block = block;
	newlist->next = NULL;
	newlist->previous = NULL;
	return (newlist);
}

void	ft_create_list(t_list **list)
{
	ft_lstadd_back(list, ft_lstnew("cat", "str", 1));
	ft_lstadd_back(list, ft_lstnew("infile", "str", 1));
	ft_lstadd_back(list, ft_lstnew("OK", "heredoc", 2));
	// ft_lstadd_back(list, ft_lstnew("cat", "str", 1));
	// ft_lstadd_back(list, ft_lstnew("wc", "str", 2));
	// ft_lstadd_back(list, ft_lstnew("outfile", "redir_out1", 3));
}
