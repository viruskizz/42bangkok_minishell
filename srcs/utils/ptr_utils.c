/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 00:16:33 by araiva            #+#    #+#             */
/*   Updated: 2022/10/23 23:50:54 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_db_ptr(char **str1, char **str2, void *str3)
{
	int	index;

	index = 0;
	if (str1 != NULL)
	{
		while (str1[index] != NULL)
			free(str1[index++]);
		free(str1);
		str1 = NULL;
	}
	index = 0;
	if (str2 != NULL)
	{
		while (str2[index] != NULL)
			free(str2[index++]);
		free(str2);
		str2 = NULL;
	}
	if (str3 != NULL)
	{
		free(str3);
		str3 = NULL;
	}
	return (1);
}

/* print error */
void	print_error(char *str, char *cmd, int mode)
{
	if (mode == ENV_NAME)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
	else if (mode == CD_NODIR)
	{
		ft_putstr_fd("minishell: cd: no such file or directory: ", 2);
		ft_putendl_fd(str, 2);
	}
	else if (mode == CD_PWD)
	{
		ft_putstr_fd("minishell: cd: string not in pwd: ", 2);
		ft_putendl_fd(str, 2);
	}
	else if (mode == NO_CMD)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd (str, 2);
	}
}
