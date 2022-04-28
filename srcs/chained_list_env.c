/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chained_list_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:08:10 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/28 16:09:11 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*temp;
	t_env	*actual;

	temp = lst;
	actual = lst;
	while (temp)
	{
		actual = temp;
		temp = temp->next;
	}
	return (actual);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*last;

	if (!*alst)
		*alst = new;
	else
	{
		last = ft_lstlast_env(*alst);
		new->previous = last;
		last->next = new;
	}
}

t_env	*ft_lstnew_env(char *name, char *value)
{
	t_env	*newenv;

	newenv = malloc(sizeof(t_env));
	if (!newenv)
		return (NULL);
	newenv->name = name;
	newenv->value = value;
	newenv->next = NULL;
	return (newenv);
}
