/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 12:20:12 by dcologgi          #+#    #+#             */
/*   Updated: 2023/07/20 18:56:15 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_var(t_shell *mini, int i)
{
	int		j;
	char	**tmp_env;

	j = 0;
	while (mini->new_envp[j])
		j++;
	tmp_env = malloc(sizeof(char *) * j);
	j = 0;
	while (j != i)
	{
		tmp_env[j] = ft_strdup(mini->new_envp[j]);
		j++;
	}
	j++;
	while (mini->new_envp[j])
	{
		tmp_env[j - 1] = ft_strdup(mini->new_envp[j]);
		j++;
	}
	tmp_env[j] = NULL;
	free_matrix(mini->new_envp);
	copy_envp(mini, tmp_env);
}

static void	delete_var2(t_shell *mini, int i)
{
	int		j;
	char	**tmp_env;

	j = 0;
	while (mini->envp[j])
		j++;
	tmp_env = ft_calloc(j, sizeof(char *));
	j = 0;
	while (j != i)
	{
		tmp_env[j] = ft_strdup(mini->envp[j]);
		j++;
	}
	j++;
	while (mini->envp[j])
	{
		tmp_env[j - 1] = ft_strdup(mini->envp[j]);
		j++;
	}
	tmp_env[j] = NULL;
	free_matrix(mini->envp);
	cloning_envp(mini, tmp_env);
}

void	command_unset(t_shell *mini, char *str)
{
	int	i;

	i = -1;
	if (mini->new_envp != NULL)
	{
		while (mini->new_envp[++i] != NULL)
		{
			if (ft_strncmp(mini->new_envp[i], str, ft_strlen(str)) == 0
				&& mini->new_envp[i][ft_strlen(str)] == '=')
				delete_var(mini, i);
		}
	}
	else
	{
		while (mini->envp[++i] != NULL)
		{
			if (ft_strncmp(mini->envp[i], str, ft_strlen(str)) == 0
				&& mini->envp[i][ft_strlen(str)] == '=')
				delete_var2(mini, i);
		}
	}
}

static void	order_new_envp(t_shell *mini)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (mini->new_envp[i])
	{
		j = 0;
		while (mini->new_envp[i][j] != '=')
			j++;
		k = i + 1;
		while (mini->new_envp[k])
		{
			if (ft_strncmp(mini->new_envp[i], mini->new_envp[k], j) > 0)
			{
				swap_envp(mini, i, k);
				i = 0;
				break ;
			}
			k++;
		}
		i++;
	}
}

void	command_export(t_shell *mini, char **envp, char *str)
{
	int	i;

	i = 0;
	if(str != 0)
	{
	command_unset(mini, ft_substr(str, 0, my_strchr(str, '=')));
	copy_envp(mini, mini->envp);
	create_new_var(mini, str);
	order_new_envp(mini);
	
	} 
	else
		return ;
}
