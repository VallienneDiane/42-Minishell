/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:46:49 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/12 15:51:40 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_valid_env_name(char *env_name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(env_name[i]))
		return (0);
	i++;
	while (env_name[i])
	{
		if (env_name[i] == '+')
		{
			if (env_name[i + 1] && env_name[i + 1] == '=')
				return (1);
			else
				return (0);
		}
		if (env_name[i] == '=')
			return (1);
		if (!ft_isalnum(env_name[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->tab_str[i])
	{
		if (!ft_valid_env_name(cmd->tab_str[i]))
			printf("export: `%s': not a valid identifier\n", cmd->tab_str[i]);
		else
		{
			printf("c'est good\n");
			
		}
		i++;
	}
	return (1);
}