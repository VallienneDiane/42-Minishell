/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:46:49 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/13 17:45:05 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_valid_env_name(char *env_name, int *concat)
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
			*concat = 1;
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

int	ft_add_env(t_cmd *cmd, char *env_name, int concat)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (env_name[i])
	{
		if (env_name[i] == '+' || env_name[i] == '=')
			break ;
		i++;
	}
	name = ft_substr(env_name, 0, i);
	if (concat)
		value = ft_substr(env_name, i + 2, ft_strlen(env_name));
	else
		value = ft_substr(env_name, i + 1, ft_strlen(env_name));
	while (cmd->env_list)
	{
		if (ft_strcmp(name, cmd->env_list->name) == 0)
		{
			// printf("avt cmd->env_list->value : %s\n", cmd->env_list->value);
			if (concat)
				cmd->env_list->value = ft_strjoin(cmd->env_list->value, value);
			else
				ft_strcpy(cmd->env_list->value, value);
			free (name);
			free (value);
			// printf("apr cmd->env_list->value : %s\n", cmd->env_list->value);
			return (0);
		}
		cmd->env_list = cmd->env_list->next;
	}
	ft_lstadd_back_env(&cmd->env_list, ft_lstnew_env(name, value));
	// printf("apr cmd->env_list->value : %s\n", cmd->env_list->value);
	return (0);
}

int	ft_export(t_cmd *cmd)
{
	int	i;
	int	concat;

	i = 1;
	concat = 0;
	while (cmd->tab_str[i])
	{
		if (!ft_valid_env_name(cmd->tab_str[i], &concat))
			printf("export: `%s': not a valid identifier\n", cmd->tab_str[i]);
		else
		{
			printf("c'est good\n");
			ft_add_env(cmd, cmd->tab_str[i], concat);
				
		}
		i++;
	}
	// ft_env(cmd);
	(void)cmd;
	return (1);
}