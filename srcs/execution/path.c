/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:24:46 by dvallien          #+#    #+#             */
/*   Updated: 2022/05/03 14:41:10 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*ft_no_command(t_cmd *cmd)
{
	printf("miniHell : %s : command not found\n", cmd->tab_str[0]);
	return (NULL);
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
		return (cmd->tab_str[0]);
	}
	while (cmd->tab_path[++i])
	{
		tmp_path = ft_strjoin(cmd->tab_path[i], "/");
		path = ft_strjoin(tmp_path, cmd->tab_str[0]);
		free(tmp_path);
		if (access(path, 0) == 0)
		{
			cmd->path_ok = 1;
			return (path);
		}
		else
			free(path);
	}
	return (ft_no_command(cmd));
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
