/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 16:48:52 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/22 18:05:46 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redir(t_list *list, t_cmd *cmd, char **envp)
{
	int i;
	int count;
	(void)envp;

	i = 0;
	count = 0;
	while (list->next && ft_strncmp("pipe", list->type, 4) != 0)
	{
		if (ft_strncmp("redir", list->type, 5) == 0)
		{
			i++;
		}
		list = list->next;
		count++;
	}
	ft_create_tab_redir(list, cmd, i);
	while (count > 0)
	{
		list = list->previous;
		count--;
	}
	// ft_fill_tab_redir(list, cmd, envp);
	
	// cmd->fd1 = open(list->content, O_RDONLY);
	// if (cmd->fd1 < 0)
	// 	strerror(cmd->fd1);
	// dup2(cmd->fd1, STDIN_FILENO);
}

void	ft_create_tab_redir(t_list *list, t_cmd *cmd, int i)
{
	if (ft_strncmp("redir", list->type, 5) == 0 && \
	ft_strncmp("pipe", list->type, 4) != 0)
		i++;
	cmd->tab_redir = malloc(sizeof(char *) * ((i * 2) + 1));
	if (!cmd->tab_redir)
	{
		free (cmd->tab_redir);
		exit(EXIT_FAILURE);
	}
}


// Recreer un tableau d'arguments avec les redirections
// Compteur pour avoir le nombre de redirections, *2 avec les fichiers, + 1 pour la commande
// 1er tableau avec les redirections
// 2nd tableau avec la commande a l'index 0
	
	// if (dup2(cmd->fd2, 1) < 0)
	// 	printf("error dup2\n");
	// cmd->fd2 = open(list->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
	// printf("fd2 open %s\n", list->content);