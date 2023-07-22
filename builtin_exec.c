/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:11:11 by dcologgi          #+#    #+#             */
/*   Updated: 2023/07/20 18:55:34 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_env(t_shell *mini)
{
	int		j;
	char	*dollar;
	char	*argument;

	j = 0;
	dollar = "$";
	if (mini->new_envp == NULL)
	{
		while (mini->envp[j] != NULL)
		{
			argument = ft_strjoin(dollar, mini->envp[j], NO_FREE, NO_FREE);
			if (!(*mini->list)->argument)
				printf("%s\n", mini->envp[j]);
			else if (ft_strncmp(argument, (*mini->list)->argument,
					ft_strlen((*mini->list)->argument)) == 0)
				printf("%s\n", mini->envp[j]);
			j++;
		}
	}
	else
		command_env2(mini, dollar);
}

void	command_pwd(t_shell *mini, t_args *current)
{
	char	pwd_path[1024];

	if (current->argument != NULL)
	{
		printf("pwd: too many arguments\n");
		mini->flag_status = 1;
		return ;
	}
	if (getcwd(pwd_path, sizeof(pwd_path)) != NULL)
		printf("%s\n", pwd_path);
}

static void	create_path(t_shell *mini, char *path)
{
	mini->main_path = ft_strtrim(mini->main_path, "$ ");
	mini->main_path = ft_strjoin(mini->main_path, "/", FREE,
			NO_FREE);
	mini->main_path = ft_strjoin(mini->main_path, path, FREE,
			NO_FREE);
	mini->main_path = ft_strtrim(mini->main_path, "/");
	mini->main_path = ft_strjoin(mini->main_path, "$ ", FREE,
			NO_FREE);
}

static void	command_cd2(t_shell *mini, char *path)
{
	if (ft_strcmp(path, "..") == 0)
	{
		mini->main_path = ft_substr(mini->main_path, 0,
				ft_strlen(mini->main_path)
				- ft_strchr(rev_string(mini->main_path), '/') - 1);
		mini->main_path = ft_strjoin(mini->main_path, "$ ", FREE,
				NO_FREE);
	}
	else if (ft_strcmp(path, ".") == 0)
		return ;
	else
		create_path(mini, path);
}

void	command_cd(t_shell *mini, t_args *node, char *arg)
{
	char	*curr_path;
	char	*path;

	curr_path = get_my_env(mini, "PWD");
	if (!arg)
		path = get_my_env(mini, "HOME");
	else
		path = arg;
	if (chdir(path) == -1)
	{
		printf("chdir error: Bad address %s\n", path);
		mini->flag_status = 1;
	}
	else
		command_cd2(mini, path);
}
