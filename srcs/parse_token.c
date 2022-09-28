/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiva <tsomsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:53:08 by araiva            #+#    #+#             */
/*   Updated: 2022/09/28 16:53:10 by araiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_dq_quote(t_list *token);
static int	word_len(char *token);
static int	exp_str(char *token, char **str);

t_list	*parse_token(t_list *tokens)
{
	t_list	*lst;

	lst = tokens;
	while (lst)
	{
		if (is_dq_str(lst->content))
			parse_dq_quote(lst);
		lst = lst->next;
	}
	return (tokens);
}

static void	parse_dq_quote(t_list *lst)
{
	char	*token;
	char	*s;
	char	*new;
	int		wlen;

	token = lst->content;
	token++;
	new = ft_strdup("\"");
	while (*token && *token != '"')
	{
		if (*token == '$')
			wlen = exp_env(token, &new);
		else
			wlen = exp_str(token, &new);
		token += wlen;
	}
	s = ft_strdup("\"");
	new = my_strcat(new, s);
	free(lst->content);
	lst->content = new;
}

static int	exp_str(char *token, char **str)
{
	int		wlen;
	char	*s;

	wlen = word_len(token);
	s = ft_calloc(wlen + 1, sizeof(char));
	ft_strlcpy(s, token, wlen + 1);
	*str = my_strcat(*str, s);
	return (wlen);
}

/*
 * word length is including space char
 */
static int	word_len(char *s)
{
	int		i;
	char	*pattern;

	i = 0;
	pattern = "$\"\0";
	while (!ft_strchr(pattern, s[++i]))
		;
	return (i);
}