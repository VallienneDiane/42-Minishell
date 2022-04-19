/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:24:59 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/19 16:18:48 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_remove_first(t_cmd *cmd)
{
	t_env	*temp;

	temp = cmd->env_list->next;
	free(cmd->env_list->name);
	free(cmd->env_list->value);
	free(cmd->env_list);
	cmd->env_list = temp;
}

void	ft_remove_last(t_cmd *cmd)
{
	t_env	*temp;

	temp = ft_lstlast_env(cmd->env_list);
	temp->previous->next = NULL;
	free(temp->name);
	free(temp->value);
	free(temp);
}

void	ft_remove(t_cmd *cmd, t_env *temp)
{
	if (!temp->previous)
		ft_remove_first(cmd);
	else if (!temp->next)
		ft_remove_last(cmd);
	else
	{
		temp->previous->next = temp->next;
		temp->next->previous = temp->previous;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

int	ft_unset(t_cmd *cmd)
{
	int		i;
	t_env	*temp;

	i = 1;
	while (cmd->tab_str[i])
	{
		temp = cmd->env_list;
		while (temp)
		{
			if (ft_strcmp(cmd->tab_str[i], temp->name) == 0)
				ft_remove(cmd, temp);
			temp = temp->next;
		}
		i++;
	}
	return (1);
}
