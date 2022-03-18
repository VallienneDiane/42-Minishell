/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:24:46 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/18 15:35:15 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_line_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*ft_access_path(t_list *list, t_cmd *cmd)
{
	char	*tmp_path;
	char	*path;
	int		i;

	i = -1;
	if (access(list->content, X_OK) == 0)
		return (ft_strdup(list->content));
	while (cmd->tab_path[++i])
	{
		tmp_path = ft_strjoin(cmd->tab_path[i], "/");
		path = ft_strjoin(tmp_path, list->content);
		free(tmp_path);
		if (access(path, 0) == 0)
			return (path);
		else
		{
			free(path);
			path = NULL;
		}
	}
	printf("command not found\n");
	// ft_error_path();
	return (NULL);
}
