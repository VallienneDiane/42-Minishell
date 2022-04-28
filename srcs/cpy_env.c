/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:37:35 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/27 10:37:53 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_lst_env_name(char *env)
{
	int		i;
	char	*env_name;

	i = 0;
	while (env[i])
	{
		i++;
		if (env[i] == '=')
			break ;
	}
	env_name = ft_calloc(sizeof(char), i);
	if (!env_name)
		exit (EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			break ;
		env_name[i] = env[i];
		i++;
	}
	return (env_name);
}

char	*ft_lst_env_value(char *env)
{
	int		i;
	int		j;
	char	*env_value;

	i = 0;
	j = 0;
	while (env[i])
	{
		i++;
		if (env[i] == '=')
			break ;
	}
	if (!env[i])
		return (NULL);
	i++;
	while (env[i + j])
		j++;
	env_value = ft_calloc(sizeof(char), j + 1);
	if (!env_value)
		exit (EXIT_FAILURE);
	j = 0;
	while (env[i + j])
	{
		env_value[j] = env[i + j];
		j++;
	}
	return (env_value);
}

void	ft_cpy_env(char **env, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(ft_lst_env_name(env[i]), "SHLVL") == 0)
		{
			ft_lstadd_back_env(&cmd->env_list, ft_lstnew_env(ft_lst_env_name(env[i]), ft_itoa(ft_atoi(ft_lst_env_value(env[i])) + 1)));
			
		}
		else
			ft_lstadd_back_env(&cmd->env_list, ft_lstnew_env(ft_lst_env_name(env[i]), ft_lst_env_value(env[i])));
		i++;
	}
}
