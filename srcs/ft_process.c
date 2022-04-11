/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:44:25 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/17 14:18:13 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_process(t_list *list, t_cmd *cmd, char **envp)
{
    char    **tab_cmd;
    int     i;

    i = 0;
    tab_cmd = malloc(sizeof(char *));
    while (ft_strncmp("cmd", list->type, 3) == 0 && ft_strncmp("option", list->type, 3) == 0)
    {
        tab_cmd[i] = malloc(sizeof(char) * ft_strlen(list->content));
        tab_cmd[i] = list->content;
        printf("%s\n", tab_cmd[i]);
        list = list->next;
        while (ft_strncmp("option", list->type, 6) == 0)
        {
            tab_cmd[i] = malloc(sizeof(char) * ft_strlen(list->content));
            tab_cmd[i] = list->content;   
            printf("%s\n", tab_cmd[i]);
            list = list->next;
        }
        i++;      
    }
    if (ft_strncmp("str", list->next->type, 3) == 0)
    {
        cmd->fd1 = open(list->next->content, O_RDONLY);
        if (execve(cmd->valid_path, &list->content, envp) < 0)
        {
            free(cmd->valid_path);
            free(&list->content);
            printf("Error execve\n");
        }
        // ft_error_open();
        // cmd->fd2 = open(list->next->next->content, O_CREAT | O_RDWR | O_TRUNC, 0644);
        // printf("fd2 open %s\n", list->next->next->content);
    }
}