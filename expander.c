/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:08:51 by riccardobor       #+#    #+#             */
/*   Updated: 2023/07/20 18:56:11 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	replacer(t_shell *mini)
{
	int		i;
	char	*en;
	t_args	*node;

	node = *mini->list;
	i = 0;
	while (node != NULL)
	{
		if (node->argument != NULL && my_strchr(node->argument, '$') != -1
			&& ft_strcmp(node->command, "export") != 0
			&& ft_strcmp(node->command, "unset") != 0
			&& ft_strcmp(node->command, "echo") != 0)
		{
			en = expanding_d(mini, node->argument);
			if (en != NULL)
			{
				node->argument = ft_strdup(en);
				break ;
			}
		}
		node = node->next;
	}
}

char	*get_my_new_env(t_shell *mini, char *d)
{
	int	i;

	i = -1;
	while (mini->new_envp[++i] != NULL)
	{
		if (ft_strncmp(mini->new_envp[i], d, ft_strlen(d)) == 0
			&& mini->new_envp[i][ft_strlen(d)] == '=')
			return (ft_substr(mini->new_envp[i], ft_strlen(d) + 1,
					ft_strlen(mini->new_envp[i]) - ft_strlen(d) - 1));
	}
	return (NULL);
}

char	*get_my_env(t_shell *mini, char *d)
{
	int	i;

	i = -1;
	if (mini->new_envp != NULL)
		return (get_my_new_env(mini, d));
	while (mini->envp[++i] != NULL)
	{
		if (ft_strncmp(mini->envp[i], d, ft_strlen(d)) == 0
			&& mini->envp[i][ft_strlen(d)] == '=')
			return (ft_substr(mini->envp[i], ft_strlen(d) + 1,
					ft_strlen(mini->envp[i]) - ft_strlen(d) - 1));
	}
	return (NULL);
}

char	*expanding_d(t_shell *mini, char *s)
{
	char	*d;
	char	*en;

	d = ft_strtrim(s, "$");
	en = get_my_env(mini, d);
	if (d[0] == '?' && d[1] == '\0')
	{
		if (mini->flag_status != 0)
		{
			en = ft_itoa(mini->flag_status);
			mini->flag_status = 0;
		}
		else
			en = ft_itoa(WEXITSTATUS(g_exit_status));
	}
	free(d);
	free(s);
	if (!en)
		return (NULL);
	return (en);
}
