/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiva <tsomsa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:52:43 by araiva            #+#    #+#             */
/*   Updated: 2022/09/25 18:52:44 by araiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wordlen(char *str);
static int	count_word(char *line);

char	**split_input(char *line)
{
	int		i;
	int		wlen;
	int		cword;
	char	**words;

	i = 0;
	cword = count_word(line);
	if (cword < 0)
		return (NULL);
	printf("cword: %d\n", cword);
	words = ft_calloc(sizeof(char *), cword + 1);
	while (*line)
	{
		wlen = wordlen(line);
		words[i] = ft_calloc(sizeof(char), wlen + 1);
		ft_strlcpy(words[i++], line, wlen + 1);
		line += wlen;
		while (*line && ft_strchr(FIELDS, *(++line)))
			if (!*line)
				break ;
	}
	words[i] = NULL;
	return (words);
}

static int	wordlen(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr(QUOTES, str[0]))
	{
		while (str[++i])
			if (ft_strchr(QUOTES, str[i]))
				return (++i);
		perror("token reconize error quoting");
		return (-1);
	}
	while (str[i] && !ft_strchr(FIELDS, str[i]))
		i++;
	return (i);
}

static int	count_word(char *s)
{
	int	count;
	int	wlen;

	count = 0;
	while (*s)
	{
		wlen = wordlen(s);
		if (wlen < 0)
			return (-1);
		s = s + wlen;
		if (wlen > 0)
			count++;
		while (*s && ft_strchr(FIELDS, *(++s)))
			if (!*s)
				break ;
	}
	return (count);
}
