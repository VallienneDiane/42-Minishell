/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:10:43 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/29 13:12:31 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_option(char *arg)
{
    int i;

    i = 1;
    while (arg[i])
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int ft_echo(char **args)
{
    int i;
    int is_arg;
    int option;

    i = 1;
    is_arg = 0;
    option = 0;
    while (args[i])
    {
        if (is_arg)
            printf(" ");
        if (args[i][0] == '-' && is_arg == 0)
        {
            if (ft_option(args[i]))
                option = 1;
            else
                is_arg = 1;
        }
        if (is_arg || args[i][0] != '-')
        {
            printf("%s", args[i]);
            is_arg = 1;
        }
        i++;
    }
    if (!option)
        printf("\n");
    return (0);
}