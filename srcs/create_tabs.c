/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tabs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:50:55 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/01 13:28:44 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
////////////////////////////////////////////////////////////////////////////////
// Parcours la liste pour calculer le nombre de blocs str ou redir_in/out1/out2
////////////////////////////////////////////////////////////////////////////////
void    ft_init_tab(t_cmd *cmd)
{
    cmd->nb_str = 0;
    cmd->nb_in = 0;
    cmd->nb_out1 = 0;
    cmd->nb_out2 = 0;
}

void    ft_start_exec(t_list *list, t_cmd *cmd, char **envp, int current_block)
{
    (void)envp;
    t_list  *lst_temp;

    lst_temp = list;
    ft_init_tab(cmd);
    while (lst_temp && lst_temp->block == current_block)
    {
		if (ft_strncmp("str", lst_temp->type, 3) == 0)
			cmd->nb_str++;
		else
        {
            if (ft_strncmp("redir_in", lst_temp->type, 8) == 0)
                cmd->nb_in++;
            else if (ft_strncmp("redir_out1", list->type, 8) == 0)
                cmd->nb_out1++;
            else if (ft_strncmp("redir_out2", list->type, 8) == 0)
                cmd->nb_out2++;
        }
        // printf("nb_str : %d, nb_in : %d, nb_out1 : %d, nb_out2 %d\n \n", cmd->nb_str, cmd->nb_in, cmd->nb_out1, cmd->nb_out1);
		lst_temp = lst_temp->next;
    }
    ft_create_tab(cmd, list, current_block);
}

////////////////////////////////////////////////////////////////////////////////
// Malloc chaque tableau de la bonne taille puis les remplir avec le list->content
////////////////////////////////////////////////////////////////////////////////
void    ft_malloc_tab(t_cmd *cmd)
{
    cmd->tab_str = malloc(sizeof(char *) * (cmd->nb_str + 1));
    cmd->redir_in = malloc(sizeof(char *) * (cmd->nb_in + 1));
    cmd->redir_out1 = malloc(sizeof(char *) * (cmd->nb_out1 + 1));
    cmd->redir_out2 = malloc(sizeof(char *) * (cmd->nb_out2 + 1));
    cmd->tab_str[cmd->nb_str] = NULL;
    cmd->redir_in[cmd->nb_in] = NULL;
    cmd->redir_out1[cmd->nb_out1] = NULL;
    cmd->redir_out2[cmd->nb_out2] = NULL;
    if (!cmd->tab_str || !cmd->redir_in || !cmd->redir_out1 || !cmd->redir_out2)
        exit(EXIT_FAILURE);
}

void    ft_create_tab(t_cmd *cmd, t_list *list, int current_block)
{
    int i;
    int j;
    int k;
    int l;
    
    i = 0;
    j = 0;
    k = 0;
    l = 0;
    ft_malloc_tab(cmd);
    while (list && list->block == current_block)
    {
        if (ft_strncmp("str", list->type, 3) == 0)
            ft_fill_tab_str(cmd, list, &i);
        else if (ft_strncmp("redir_in", list->type, 8) == 0)
            ft_fill_redir_in(cmd, list, &j);
        else if (ft_strncmp("redir_out1", list->type, 10) == 0)
            ft_fill_redir_out1(cmd, list, &k);
        else if (ft_strncmp("redir_out2", list->type, 10) == 0)
            ft_fill_redir_out2(cmd, list, &l);
        list = list->next;
    }
}

void    ft_error_create_file(void)
{
    printf("Error : file not created\n");
    exit(EXIT_FAILURE);
}
