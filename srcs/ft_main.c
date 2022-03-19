/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:36:32 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/19 16:48:14 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parse_type(t_list *list, t_cmd *cmd, char **envp)
{	
	if (ft_strncmp("redir", list->type, 5) == 0)
		ft_redir(list, cmd, envp);
	else
	{
		cmd->valid_path = ft_access_path(list, cmd);
		ft_exec_cmd(list, cmd, envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_list	*list;
	t_cmd	cmd;
	// char 	*line;
	
	(void)ac;
	(void)av;
	list = malloc(sizeof(t_list));
	list = NULL;
	// while (1)
	// 	line = readline("minishell > ");
	ft_create_list(&list);
	cmd.line_path = ft_get_line_path(envp);
	cmd.tab_path = ft_split(cmd.line_path, ':');
	ft_parse_type(list, &cmd, envp);
}
