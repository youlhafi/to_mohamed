/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:42:13 by mhabib-a          #+#    #+#             */
/*   Updated: 2023/08/09 19:17:54 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_error(t_list *new)
{
	if (parsing(&new) || parse_quotes(&new))
	{
		ft_error("syntax error", 258, NULL, NULL);
		return (1);
	}
	return (0);
}

void	handle_ctrl_c(int i)
{
	if (i == SIGINT)
	{
		printf ("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		g_global.herdoc = 1;
		g_global.status = 1;
	}
}

void	handle_ctrl_b(int i)
{
	(void)i;
	return ;
}

char	**get_env1(char **env)
{
	char	**str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	str = NULL;
	while (env[count])
		count++;
	str = malloc(sizeof(char *) * (count + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (env[i])
	{
		str[i] = ft_strdup(env[i]);
		if (!str[i])
			return (ft_free_str(str), NULL);
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	ff(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		return ;
	}
}
