/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:45:02 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/18 17:50:57 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_list  *ft_lstlast(t_list *lst)
// {
// 	t_list  *temp;
// 	t_list  *actual;

// 	temp = lst;
// 	actual = lst;
// 	while (temp)
// 	{
// 		actual = temp;
// 		temp = temp->next;
// 	}
// 	return (actual);
// }

// void    ft_lstadd_back(t_list **alst, t_list *new)
// {
// 	t_list  *last;

// 	if (!*alst)
// 		*alst = new;
// 	else
// 	{
// 		last = ft_lstlast(*alst);
// 		last->next = new;
// 	}
// }

// t_list  *ft_lstnew(void *str, void *type)
// {
// 	t_list  *newlist;

// 	newlist = malloc(sizeof(t_list));
// 	if (!newlist)
// 		return (NULL);
// 	newlist->str = str;
// 	newlist->type = type;
// 	newlist->next = NULL;
// 	return (newlist);
// }

// void	ft_create_list(t_list **list)
// {
// 	ft_lstadd_back(list, ft_lstnew("cat", "cmd"));
// 	ft_lstadd_back(list, ft_lstnew("test.txt", "str"));
// 	ft_lstadd_back(list, ft_lstnew("|", "pipe"));
// 	ft_lstadd_back(list, ft_lstnew("wc", "cmd"));
// 	ft_lstadd_back(list, ft_lstnew("-n", "option"));
// 	ft_lstadd_back(list, ft_lstnew(">", "redir"));
// 	ft_lstadd_back(list, ft_lstnew("result", "str"));
// }

// void	ft_print_list(t_list *list)
// {
// 	while (list)
// 	{
// 		printf("'%s' | '%s'\n", list->str, list->type);
// 		list = list->next;
// 	}
// }

// void	ft_lexer(t_list **list, char *line, int i)
// {
// 	if (line[i] == '\'')
// 		ft_simple_quote(list, line, i);
// }

// void	ft_parsing(t_list **list, char *line)
// {
// 	int	i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		while (line[i] && line[i] == ' ')
// 			i++;
// 		ft_lexer(list, line, i);
// 		write(1, &line[i], 1);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// 	(void)list;
// }

// int	main(int ac, char **av, char **env)
// {
// 	char *line;
// 	t_list	*list;
// 	// int	i = 0;

// 	list = malloc(sizeof(t_list));
// 	list = NULL;
// 	// printf("%d %s %s\n", __LINE__, __FILE__, __FUNCTION__);
// 	// ft_create_list(&list);
// 	// while (env[i])
// 	// {
// 	// 	printf("%s\n", env[i]);
// 	// 	i++;
// 	// }

// 	while (1)
// 	{
// 		line = readline("couscous > ");
// 		ft_parsing(&list, line);
// 		// printf("%s\n", line);
// 		ft_print_list(list);
// 	}
// 	(void)ac;
// 	(void)av;
// 	(void)env;
// }
