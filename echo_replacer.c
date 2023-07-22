/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_replacer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:08:51 by riccardobor       #+#    #+#             */
/*   Updated: 2023/07/20 18:55:50 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// norma ok
extern int	g_exit_status;

static int	ft_contace(char *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

static int	check(char	*s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			return (1);
		if (s[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

static char	*ft_strongest(t_args *node, int i, int j, char *tmp)
{
	while (node->argument[i] != '\0')
	{
		if (node->argument[i] == '$' && check(node->argument) != 0)
		{
			tmp[j] = 6;
			i++;
			j++;
			while (node->argument[i] != ' ' && node->argument[i] != '\''
				&& node->argument[i] != '\"' && node->argument[i] != '\0')
				tmp[j++] = node->argument[i++];
			if (node->argument[i] != '\0')
			{
				tmp[j] = 6;
				j++;
			}
			if (node->argument[i] == '\0')
			{
				tmp[j] = '\0';
				return (tmp);
			}
		}
		tmp[j++] = node->argument[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*ft_quite_strong(t_args *node)
{
	int		i;
	int		j;
	char	*tmp;
	int		counter;

	i = 0;
	j = 0;
	counter = ft_contace(node->argument, '$');
	tmp = ft_calloc((ft_strlen(node->argument) + (2 * counter)), sizeof(char));
	tmp = ft_strongest(node, i, j, tmp);
	return (tmp);
}

void	echo_replacer(t_shell *mini, t_args *node)
{
	int		i;
	char	*en;
	char	**matrix;
	char	*str;

	i = -1;
	matrix = NULL;
	en = ft_strdup("");
	if (node->argument != NULL && my_strchr(node->argument, '$') != -1)
	{
		matrix = tyu(node);
		while (matrix[++i] != NULL)
		{
			matrix[i] = echo_expanding_d(mini, matrix[i]);
			en = ft_strjoin(en, matrix[i], FREE, NO_FREE);
			str = ft_strtrim(en, "\"");
			free(en);
			en = ft_strdup(str);
			free(str);
		}
		free(node->argument);
		node->argument = ft_strdup(en);
		free_matrix(matrix);
	}
	free(en);
}
