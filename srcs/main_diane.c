/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_diane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:36:32 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/29 17:51:07 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parse_type(t_list *list, t_cmd *cmd, char **envp)
{	
	while (list && list->block >= 1)
	{
		ft_minishell(list, cmd, envp);
		cmd->valid_path = ft_access_path(list, cmd);
		list->block--;
		printf("block %d\n", list->block);
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
