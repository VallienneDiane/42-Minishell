/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tabs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:20:19 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/31 17:59:59 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

////////////////////////////////////////////////////////////////////////////////
// Rempli les tableaux et verifie pour redir si fichier s'ouvre
////////////////////////////////////////////////////////////////////////////////
void    ft_fill_tab_str(t_cmd *cmd, t_list *list, int *i)
{
    cmd->tab_str[*i] = malloc(sizeof(char) * ft_strlen(list->content));
    if (!cmd->tab_str[*i])
    {
        free(cmd->tab_str);
        exit(EXIT_FAILURE);
    }
    cmd->tab_str[*i] = list->content;
    // printf("tab_str : %s\n", cmd->tab_str[*i]);
    *i += 1;
}

void    ft_fill_redir_in(t_cmd *cmd, t_list *list, int *j)
{
    cmd->redir_in[*j] = malloc(sizeof(char) * ft_strlen(list->content));
    if (!cmd->redir_in[*j])
    {
        free(cmd->redir_in);
        exit(EXIT_FAILURE);
    }
    cmd->redir_in[*j] = list->content;
    if (ft_create_file(cmd, 0) == -1)
        ft_error_create_file();
    // printf("STDIN %d\n", cmd->fd_stdin);
    // printf("redir_in : %s\n", cmd->redir_in[*j]);
}

void    ft_fill_redir_out1(t_cmd *cmd, t_list *list, int *k)
{
    cmd->redir_out1[*k] = malloc(sizeof(char) * ft_strlen(list->content));
    if (!cmd->redir_out1[*k])
    {
        free(cmd->redir_out1);
        exit(EXIT_FAILURE);
    }
    cmd->redir_out1[*k] = list->content;
    printf("redir_out1 : %s\n", cmd->redir_out1[*k]);
}

void    ft_fill_redir_out2(t_cmd *cmd, t_list *list, int *l)
{
    cmd->redir_out2[*l] = malloc(sizeof(char) * ft_strlen(list->content));
    if (!cmd->redir_out2[*l])
    {
        free(cmd->redir_out2);
        exit(EXIT_FAILURE);
    }
    cmd->redir_out2[*l] = list->content;
    printf("redir_out2 : %s\n", cmd->redir_out2[*l]);
}