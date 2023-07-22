/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:08:55 by riccardobor       #+#    #+#             */
/*   Updated: 2023/07/20 18:57:28 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	boh(t_shell *mini, char *temp)
{
	int	j;

	j = 0;
	while ((*mini->high)->str[j] == ' ')
		j++;
	while ((*mini->high)->str[j] && (*mini->high)->str[j] != ' ')
		j++;
	while ((*mini->high)->str[j] == ' ')
		j++;
	if ((*mini->high)->str[j] != '<')
	{
		mini->exit = 1;
		mini->flag_status = 127;
		return ;
	}
	else
		(*mini->high)->infile = ft_strdup(temp);
}

int	reassembling_brackets(t_shell *mini, char **temp, int i)
{
	int	j;

	j = i;
	while (temp[j] && (temp[j][ft_strlen(temp[j]) - 1] != ')'))
	{
		if ((*mini->high)->argument == NULL)
			(*mini->high)->argument = ft_strdup(temp[j]);
		else
			(*mini->high)->argument = ft_strjoin_mini((*mini->high)->argument,
					temp[j], FREE, NO_FREE);
		j++;
	}
	if (temp[j] && (temp[j][ft_strlen(temp[j]) - 1] == ')'))
	{
		if ((*mini->high)->argument == NULL)
			(*mini->high)->argument = ft_strdup(temp[j]);
		else
			(*mini->high)->argument = ft_strjoin_mini((*mini->high)->argument,
					temp[j], FREE, NO_FREE);
	}
	return (j);
}

void	its_a_flag(t_shell *mini, char *temp)
{
	if ((*mini->high)->flags == NULL)
		(*mini->high)->flags = ft_strdup(temp);
	else
	{
		if ((*mini->high)->argument != NULL)
			(*mini->high)->argument = ft_strjoin_mini((*mini->high)->argument,
					temp, FREE, NO_FREE);
		else
			(*mini->high)->argument = ft_strdup(temp);
	}
}
