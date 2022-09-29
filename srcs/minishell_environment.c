/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <sharnvon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:52:47 by sharnvon          #+#    #+#             */
/*   Updated: 2022/09/29 22:03:23 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* function make new node of link-list of t_env */
t_env	*environment_new(char *env)
{
	t_env	*result;

	result = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (result == NULL)
	{
		return (0);
	}
	result->name = environment_get_name(&env, ENVI);
	result->value = environment_get_value(&env, ENVI);
	result->next = NULL;
	return (result);
}

/* function add node of back of link-list of t_env */
void	environment_add_back(t_env **env, t_env *new)
{
	t_env	*temp;

	temp = *env;
	if (*env == NULL)
		*env = new;
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}

void	environment_clear(t_env **env)
{
	t_env	*temp;

	temp = *env;
	if (env != NULL)
	{
		while (temp != NULL)
		{
			*env = (*env)->next;
			free(temp->name);
			free(temp->value);
			free(temp);
			temp = *env;
		}
	}
}

int	execution_print_env(t_shell *shell)
{
	t_env	*environment;

	environment = shell->env;
	if (environment == NULL)
		return (1);
	while (environment != NULL)
	{
		printf("%s=%s\n", environment->name, environment->value);
		environment = environment->next;
	}
	return (0);
}

/* function get the environment */
int	minishell_make_environment(t_shell *shell)
{
	t_env	*new;
	int		index;

	index = 0;
	shell->env = NULL;
	while (environ[index] != NULL)
	{
		new = environment_new(environ[index]);
		if (new == NULL)
		{
			environment_clear(&shell->env);
			perror("ERROR: ");
			return (-1); //exit//
		}
		environment_add_back(&shell->env, new);
		index++;
	}
	return (0);
}

// int main(void)
// {
// 	t_shell *shell;

// 	shell = (t_shell *)ft_calloc(sizeof(t_shell), 1);
//     minishell_make_environment(shell);
// 	execution_print_env(shell);
// 	execution_unset_env(&shell->env, "USER");
// 	printf("\n===============================================\n\n");
// 	execution_print_env(shell);
// 	execution_unset_env(&shell->env, "TERM");
// 	printf("\n===============================================\n\n");
// 	execution_print_env(shell);
// 	execution_unset_env(&shell->env, "_");
// 	printf("\n===============================================\n\n");
// 	execution_print_env(shell);
// 	printf("=> |%s|=|%s|\n", shell->env->name, shell->env->value);	
//     return (0);
// }