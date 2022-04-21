/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:24:46 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/21 11:45:14 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_line_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*ft_access_path(t_cmd *cmd)
{	
	char	*tmp_path;
	char	*path;
	int		i;

	i = -1;
	if (access(cmd->tab_str[0], X_OK) == 0)
	{
		while (cmd->tab_path[++i])
		{
			tmp_path = ft_strjoin(cmd->tab_path[i], "/");
			if ((ft_strcmp(cmd->tab_path[i], cmd->tab_str[0]) == 0) \
			|| (ft_strcmp(tmp_path, cmd->tab_str[0]) == 0))
				printf("miniHell: %s: is a directory\n", cmd->tab_str[0]);
			free(tmp_path);
		}
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
