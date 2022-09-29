/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:30:21 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/29 20:58:54 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution_unset_env(t_env **env, char *variable_name)
{
	t_env	*current;
	t_env	*check;

	current = *env;
	check = *env;
	if (string_compare((*env)->name, variable_name) == 1)
	{
		*env = (*env)->next;
		environment_delete(current);
		// free(current->name);
		// free(current->value);
		// free(current);
		return (0);
	}
	while (current != NULL)
	{
		check = check->next;
		if (check != NULL && string_compare(check->name, variable_name) == 1)
		{
			current->next = check->next;
			environment_delete(check);
			// free(check->name);
			// free(check->value);
			// free(check);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

void	envtironment_delete(t_env *env)
{
	free(env->name);
	free(env->value);
	free(env);
}
