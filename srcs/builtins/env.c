/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:55:23 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/28 17:26:27 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_cmd *cmd)
{
	t_env	*temp;

	temp = cmd->env_list;
	while (temp)
	{
		if (temp->value)
		{
			printf("%s", temp->name);
			printf("=%s\n", temp->value);
		}
		temp = temp->next;
	}
	return (0);
}

char	*ft_getenv(char *env_name, t_cmd *cmd)
{
	t_env	*temp;

	temp = cmd->env_list;
	while (temp)
	{
		if (ft_strcmp(env_name, temp->name) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return ("");
}

void	ft_set_env(t_env *temp, char **env_tab, int i)
{
	if (temp->value)
	{
		env_tab[i] = ft_calloc(sizeof(char), ft_strlen(temp->name)
				+ ft_strlen(temp->value) + 2);
		env_tab[i] = ft_strjoin(env_tab[i], temp->name);
		env_tab[i] = ft_strjoin(env_tab[i], "=");
		env_tab[i] = ft_strjoin(env_tab[i], temp->value);
	}
	else
	{
		env_tab[i] = ft_calloc(sizeof(char), ft_strlen(temp->name) + 1);
		env_tab[i] = ft_strjoin(env_tab[i], temp->name);
	}
}

char	**ft_env_to_tab(t_cmd *cmd)
{
	char	**env_tab;
	int		i;
	t_env	*temp;

	i = 0;
	temp = cmd->env_list;
	env_tab = ft_calloc(sizeof(char *), ft_env_lst_size(cmd->env_list) + 1);
	while (temp)
	{
		ft_set_env(temp, env_tab, i);
		i++;
		temp = temp->next;
	}
	return (env_tab);
}
