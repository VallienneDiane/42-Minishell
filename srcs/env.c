/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:55:23 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/13 15:50:43 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_cmd *cmd)
{
	while (cmd->env_list)
	{
		if (cmd->env_list->value)
		{
			printf("%s", cmd->env_list->name);
			printf("=%s\n", cmd->env_list->value);
		}
		cmd->env_list = cmd->env_list->next;
	}
	return (0);
}

// char	*ft_env_var(int i, int	j, t_cmd *cmd)
// {
// 	int		k;
// 	char	*env_var;
	
// 	k = 0;
// 	j++;
// 	while (cmd->env_cpy[i][j + k])
// 		k++;
// 	env_var = ft_calloc(sizeof(char), k + 1);
// 	k = 0;
// 	while (cmd->env_cpy[i][j + k])
// 	{
// 		env_var[k] = cmd->env_cpy[i][j + k];
// 		k++;
// 	}
// 	return (env_var);
// }

char	*ft_getenv(char *env_name, t_cmd *cmd)
{
	while (cmd->env_list)
	{
		if (ft_strcmp(env_name, cmd->env_list->name) == 0)
			return (cmd->env_list->value);
		cmd->env_list = cmd->env_list->next;
	}
	return ("");
}
