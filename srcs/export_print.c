/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:54:09 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/28 13:55:10 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env_lst_size(t_env *env_list)
{
	t_env	*temp;
	int		i;

	temp = env_list;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	ft_print_env(t_cmd *cmd, t_env *current, int *i)
{
	int		j;
	t_env	*temp;

	j = 0;
	temp = cmd->env_list;
	while (temp)
	{
		if (ft_strcmp(current->name, temp->name) > 0)
			j++;
		temp = temp->next;
	}
	if (j == *i)
	{
		printf("declare -x %s", current->name);
		if (current->value)
			printf("=\"%s\"", current->value);
		printf("\n");
		*i += 1;
	}
}

void	ft_export_print(t_cmd *cmd)
{
	int		size;
	int		i;
	t_env	*current;

	i = 0;
	size = ft_env_lst_size(cmd->env_list);
	while (i < size)
	{
		current = cmd->env_list;
		while (current)
		{
			ft_print_env(cmd, current, &i);
			current = current->next;
		}
	}
}
