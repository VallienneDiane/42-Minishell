/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:55:23 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/12 11:49:10 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_cmd *cmd)
{
	int	i;
	
	i = 0;
	while (cmd->env_cpy[i])
	{
		printf("%s\n", cmd->env_cpy[i]);
		i++;
	}
	return (0);
}

char	*ft_env_var(int i, int	j, t_cmd *cmd)
{
	int		k;
	char	*env_var;
	
	k = 0;
	j++;
	while (cmd->env_cpy[i][j + k])
		k++;
	env_var = ft_calloc(sizeof(char), k + 1);
	k = 0;
	while (cmd->env_cpy[i][j + k])
	{
		env_var[k] = cmd->env_cpy[i][j + k];
		k++;
	}
	return (env_var);
}

char	*ft_getenv(char *env_name, t_cmd *cmd)
{
	int		i;
	int		j;

	i = 0;
	while (cmd->env_cpy[i])
	{
		j = 0;
		while (cmd->env_cpy[i][j] != '=')
			j++;
		if (ft_strncmp(env_name, cmd->env_cpy[i], j) == 0 && !env_name[j])
			return (ft_env_var(i, j, cmd));
		i++;
	}
	return ("");
}
