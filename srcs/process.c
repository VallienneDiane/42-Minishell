/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:44:25 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/18 17:48:35 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_process(t_list *list, t_cmd *cmd, char **envp)
{
    int  i;
    int  count;

    i = 0;
    count = 0;
    while (list->next && ft_strncmp("pipe", list->type, 4) != 0)
    {
        if (ft_strncmp("redir", list->type, 5) != 0)
            i++;
        list = list->next;
        count++;
    }
    if (ft_strncmp("redir", list->type, 5) != 0 && ft_strncmp("pipe", list->type, 4) != 0)
        i++;
    cmd->tab_args = malloc(sizeof(char *) * (i + 1));
    while (count > 0)
    {
        list = list->previous;
        count--;
    }
    i = 0;
    while (list->next && ft_strncmp("pipe", list->type, 4) != 0)
    {
        if (ft_strncmp("redir", list->type, 5) != 0)
        {
            cmd->tab_args[i] = malloc(sizeof(char) * ft_strlen(list->content));
            cmd->tab_args[i] = list->content;
            i++;      
        }
        list = list->next;
    }
    if (ft_strncmp("redir", list->type, 5) != 0 && ft_strncmp("pipe", list->type, 4) != 0)
    {
        cmd->tab_args[i] = malloc(sizeof(char) * ft_strlen(list->content));
        cmd->tab_args[i] = list->content;
        i++;      
    }
    cmd->tab_args[i] = 0;
    if (execve(cmd->valid_path, cmd->tab_args, envp) < 0)
    {
        free(cmd->valid_path);
        free(cmd->tab_args);
        printf("Error execve\n");
    }
    // cmd->fd1 = open(list->next->content, O_RDWR);
        // ft_error_open();
        // cmd->fd2 = open(list->next->next->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
        // printf("fd2 open %s\n", list->next->next->content);
}