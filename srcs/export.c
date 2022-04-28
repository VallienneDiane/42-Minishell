/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:46:49 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/28 15:45:48 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_valid_env_name(char *env_name, int *concat)
{
	int	i;

	i = 0;
	if (!ft_isalpha(env_name[i]) && env_name[i] != '_')
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

int	ft_existing_env(t_cmd *cmd, char *name, char *value, int concat)
{
	t_env	*temp;

	temp = cmd->env_list;
	while (temp)
	{
		if (ft_strcmp(name, temp->name) == 0)
		{
			if (!temp->value)
				temp->value = value;
			else if (concat && value)
			{	
				temp->value = ft_strjoin(temp->value, value);
				free (value);
			}
			else if (value)
			{
				ft_strcpy(temp->value, value);
				free (value);
			}
			free (name);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	ft_add_env(t_cmd *cmd, char *env_name, int concat)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*temp;

	i = -1;
	value = NULL;
	temp = cmd->env_list;
	while (env_name[++i])
		if (env_name[i] == '+' || env_name[i] == '=')
			break ;
	name = ft_substr(env_name, 0, i);
	if (env_name[i])
	{
		if (concat)
			value = ft_substr(env_name, i + 2, ft_strlen(env_name));
		else
			value = ft_substr(env_name, i + 1, ft_strlen(env_name));
	}
	if (ft_existing_env(cmd, name, value, concat))
		return (0);
	ft_lstadd_back_env(&cmd->env_list, ft_lstnew_env(name, value));
	return (0);
}

int	ft_export(t_cmd *cmd)
{
	int	i;
	int	concat;

	i = 1;
	concat = 0;
	if (!cmd->tab_str[i])
		ft_export_print(cmd);
	while (cmd->tab_str[i])
	{
		if (!ft_valid_env_name(cmd->tab_str[i], &concat))
			printf("export: `%s': not a valid identifier\n", cmd->tab_str[i]);
		else
			ft_add_env(cmd, cmd->tab_str[i], concat);
		i++;
	}
	return (1);
}
