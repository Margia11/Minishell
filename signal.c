/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:12:59 by dcologgi          #+#    #+#             */
/*   Updated: 2023/07/20 18:57:58 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	handlectrl(t_shell *mini, char **envp)
{
	char	input[256];

	if (!mini->input)
	{
		clear_mini(mini, 1);
		write(1, "exit\n", 5);
		exit(0);
	}
}

void	handlectrlc(int signal)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
