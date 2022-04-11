/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tabs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:50:55 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/11 14:06:50 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_tab(t_cmd *cmd)
{
	cmd->nb_str = 0;
	cmd->nb_in = 0;
	cmd->nb_out1 = 0;
	cmd->nb_out2 = 0;
	cmd->nb_heredoc = 0;
	cmd->last_in = 0;
	cmd->last_out = 0;
}

void	ft_get_args(t_list *list, t_cmd *cmd, int current_block)
{
	t_list	*lst_temp;

	lst_temp = list;
	ft_init_tab(cmd);
	while (lst_temp && lst_temp->block == current_block)
	{
		if (lst_temp->type == STR)
			cmd->nb_str++;
		else
		{
			if (lst_temp->type == REDIR_IN)
				cmd->nb_in++;
			else if (lst_temp->type == REDIR_OUT)
				cmd->nb_out1++;
			else if (lst_temp->type == REDIR_CONC)
				cmd->nb_out2++;
			else if (lst_temp->type == HEREDOC)
				cmd->nb_heredoc++;
		}
		lst_temp = lst_temp->next;
	}
	ft_create_tab(cmd, list, current_block);
}

void	ft_malloc_tab(t_cmd *cmd)
{
	cmd->tab_str = ft_calloc(sizeof(char *), (cmd->nb_str + 1));
	cmd->tab_redir_in = ft_calloc(sizeof(char *), (cmd->nb_in + 1));
	cmd->tab_heredoc = ft_calloc(sizeof(char *), (cmd->nb_heredoc + 1));
	cmd->tab_redir_out1 = ft_calloc(sizeof(char *), (cmd->nb_out1 + 1));
	cmd->tab_redir_out2 = ft_calloc(sizeof(char *), (cmd->nb_out2 + 1));
	cmd->tab_str[cmd->nb_str] = NULL;
	cmd->tab_redir_in[cmd->nb_in] = NULL;
	cmd->tab_redir_out1[cmd->nb_out1] = NULL;
	cmd->tab_redir_out2[cmd->nb_out2] = NULL;
	cmd->tab_heredoc[cmd->nb_heredoc] = NULL;
	if (!cmd->tab_str || !cmd->tab_redir_in || !cmd->tab_redir_out1 \
	|| !cmd->tab_redir_out2 || !cmd->tab_heredoc)
		exit(EXIT_FAILURE);
}

void	ft_create_tab(t_cmd *cmd, t_list *list, int current_block)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int m;

	i = 0;
	j = 0;
	k = 0;
	l = 0;
	m = 0;
	ft_malloc_tab(cmd);
	while (list && list->block == current_block)
	{
		if (list->type == STR)
			ft_fill_tab_str(cmd, list, &i);
		else if (list->type == REDIR_IN)
			ft_fill_redir_in(cmd, list, &j);
		else if (list->type == REDIR_OUT)
			ft_fill_redir_out1(cmd, list, &k);
		else if (list->type == REDIR_CONC)
			ft_fill_redir_out2(cmd, list, &l);
		else if (list->type == HEREDOC)
			ft_fill_heredoc(cmd, list, &m);
		list = list->next;
	}
}

void	ft_error_create_file(void)
{
	printf("Error : file not created\n");
	exit(EXIT_FAILURE);
}
