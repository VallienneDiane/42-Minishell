/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:24:46 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/22 17:01:09 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_line_path(t_cmd *cmd)
{
	t_env	*temp;

	temp = cmd->env_list;
	while (temp)
	{
		if (ft_strcmp(temp->name, "PATH") == 0)
			return (temp->value);
		temp = temp->next;
	}
	return ("");
}

char	*ft_access_path(t_cmd *cmd)
{	
	char	*tmp_path;
	char	*path;
	int		i;

	i = -1;
	tmp_path = NULL;
	if (access(cmd->tab_str[0], X_OK) == 0)
	{
		ft_absolute_path(cmd, i, tmp_path);
		return (ft_strdup(cmd->tab_str[0]));
	}
	while (cmd->tab_path[++i])
	{
		tmp_path = ft_strjoin(cmd->tab_path[i], "/");
		path = ft_strjoin(tmp_path, cmd->tab_str[0]);
		free(tmp_path);
		if (access(path, 0) == 0)
			return (path);
		else
			free(path);
	}
	printf("miniHell : %s : command not found\n", cmd->tab_str[0]);
	return (NULL);
}

void	ft_absolute_path(t_cmd *cmd, int i, char *tmp_path)
{
	while (cmd->tab_path[++i])
	{
		tmp_path = ft_strjoin(cmd->tab_path[i], "/");
		if ((ft_strcmp(cmd->tab_path[i], cmd->tab_str[0]) == 0) \
		|| (ft_strcmp(tmp_path, cmd->tab_str[0]) == 0))
			printf("miniHell: %s: is a directory\n", cmd->tab_str[0]);
		free(tmp_path);
	}
}
