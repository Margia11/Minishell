/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:26:51 by riccardobor       #+#    #+#             */
/*   Updated: 2023/07/20 18:57:39 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calculating_k(char *s, int i)
{
	int	k;

	k = 0;
	if (s[i] == '<')
		if (apices(s, '\'', i)
			|| apices(s, '\"', i))
			k = 2;
	if (s[i] == '>')
		if (apices(s, '\'', i) == 1
			|| apices(s, '\"', i) == 1)
			k = 4;
	if (s[i] == '|')
		if (apices(s, '\'', i) == 1
			|| apices(s, '\"', i) == 1)
			k = 6;
	if (s[i] == '&')
		if (apices(s, '\'', i) == 1
			|| apices(s, '\"', i) == 1)
			k = 8;
	return (k);
}

int	check_redirection(char *s)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (s[i])
	{
		k = calculating_k(s, i);
		if (k != 0)
			break ;
		i++;
	}
	if (k != 0 && s[i + 1] == s[i] && s[i + 2] != s[i])
		k -= 1;
	else if (k != 0 && s[i + 1] == s[i] && s[i + 2] == s[i])
	{
		printf("Minishell: syntax error near unexpected token '%c'\n", s[i]);
		return (-2);
	}
	return (k);
}

static char	*ck_pa(char **temp, char *command)
{
	int		i;
	char	*tampax;
	char	*support;

	i = -1;
	while (temp[++i])
	{
		tampax = ft_strjoin(temp[i], "/", NO_FREE, NO_FREE);
		support = ft_strjoin(tampax, command, NO_FREE, NO_FREE);
		if (access(support, F_OK) == 0)
		{
			free(tampax);
			free_matrix(temp);
			return (support);
		}
		free(support);
		free(tampax);
	}
	free_matrix(temp);
	return (NULL);
}

char	*check_path(t_shell *mini, char *command)
{
	char	*path;
	char	*support;
	char	**temp;

	path = get_my_env(mini, "PATH");
	if (!path)
		return (NULL);
	temp = ft_split(path, ':');
	free(path);
	support = ck_pa(temp, command);
	return (support);
}

int	check_path2(t_shell *mini, char *s)
{
	if (access(s, F_OK) == 0)
		return (1);
	return (0);
}
