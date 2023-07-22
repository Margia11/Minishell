/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 09:39:49 by dcologgi          #+#    #+#             */
/*   Updated: 2023/07/20 18:56:02 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//norma ok 3 funzioni
int	ft_echo_strcheck(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_quotes(t_shell *mini, char const *s, int i, char c)
{
	int	z;

	z = i + 1;
	while (s[z] != c && s[z])
		z++;
	if (s[z] == c)
		return (z);
	return (0);
}

static void	echo_print(t_args *current)
{
	write(1, current->argument, ft_strlen(current->argument));
	if (current->flags == NULL)
		write(1, "\n", 1);
}

void	command_echo(t_shell *mini, char **envp, t_args *current)
{
	char	*res;

	if ((current->argument == NULL && current->flags != NULL)
		|| (current->argument != NULL
			&& (ft_strncmp(current->argument, "\"-n\"", 4) == 0)))
		return ;
	else if (current->argument == NULL && current->flags == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	if (current->argument[0] == '\'' && current->argument != NULL)
	{
		current->argument = ft_strtrim(current->argument, "\'");
		write(1, current->argument, ft_strlen(current->argument));
		if (current->flags == NULL)
			write(1, "\n", 1);
		return ;
	}
	echo_replacer(mini, current);
	res = ft_strtrim(current->argument, "\"");
	free(current->argument);
	current->argument = ft_strdup(res);
	free(res);
	echo_print(current);
}
