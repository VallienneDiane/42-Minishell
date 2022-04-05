/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tabs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:20:19 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/05 16:17:07 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_fill_tab_str(t_cmd *cmd, t_list *list, int *i)
{
    cmd->tab_str[*i] = malloc(sizeof(char) * ft_strlen(list->content));
    if (!cmd->tab_str[*i])
    {
        free(cmd->tab_str);
        exit(EXIT_FAILURE);
    }
    cmd->tab_str[*i] = list->content;
    // printf("FILL TAB STR : %s\n", cmd->tab_str[*i]);
    *i += 1;
}


void    ft_fill_redir_in(t_cmd *cmd, t_list *list, int *j)
{
    cmd->tab_redir_in[*j] = malloc(sizeof(char) * ft_strlen(list->content));
    if (!cmd->tab_redir_in[*j])
    {
        free(cmd->tab_redir_in);
        exit(EXIT_FAILURE);
    }
    cmd->tab_redir_in[*j] = list->content;
    // printf("\nFILL REDIR_IN %s\n", cmd->tab_redir_in[*j]);
    if (ft_strncmp("redir_in", list->type, 8) == 0)
    {
        if (ft_create_file(cmd, 0) == -1)
            ft_error_create_file();
    }
}

void    ft_fill_redir_out1(t_cmd *cmd, t_list *list, int *k)
{
    cmd->tab_redir_out1[*k] = malloc(sizeof(char) * ft_strlen(list->content));
    if (!cmd->tab_redir_out1[*k])
    {
        free(cmd->tab_redir_out1);
        exit(EXIT_FAILURE);
    }
    cmd->tab_redir_out1[*k] = list->content;
    // printf("\nFILL REDIR_OUT1 : %s\n", cmd->tab_redir_out1[*k]);
    if (ft_create_file(cmd, 1) == -1)
        ft_error_create_file();
    cmd->last_out = 1;
}

void    ft_fill_redir_out2(t_cmd *cmd, t_list *list, int *l)
{
    cmd->tab_redir_out2[*l] = malloc(sizeof(char) * ft_strlen(list->content));
    if (!cmd->tab_redir_out2[*l])
    {
        free(cmd->tab_redir_out2);
        exit(EXIT_FAILURE);
    }
    cmd->tab_redir_out2[*l] = list->content;
    // printf("\nFILL REDIR_OUT2 : %s\n", cmd->tab_redir_out2[*l]);
    if (ft_create_file(cmd, 2) == -1)
        ft_error_create_file();
    cmd->last_out = 2;
}

void    ft_fill_heredoc(t_cmd *cmd, t_list *list, int *m)
{
    cmd->tab_heredoc[*m] = malloc(sizeof(char) * ft_strlen(list->content));
    if (!cmd->tab_heredoc[*m])
    {
        free(cmd->tab_heredoc);
        exit(EXIT_FAILURE);
    }
    cmd->tab_heredoc[*m] = list->content;
    // printf("FILL TAB HEREDOC : %s\n", cmd->tab_heredoc[*m]);
}