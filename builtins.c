/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 07:52:56 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/09 17:27:53 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *get, t_pip *p)
{
	int	i;

	i = 0;
	while (p->envp[i])
	{
		if (ft_strncmp(p->envp[i], get, ft_strlen(get)) == 0)
			return (p->envp[i] + (ft_strlen(get) + 1));
		i++;
	}
	return (NULL);
}

void	set_env(char *name, char *value, t_pip *p)
{
	char	*all;

	if (!value)
		return ;
	all = ft_strjoin(name, value);
	ft_export_help(p, all);
	free(all);
}

void	ft_pwd(t_pip *p)
{
	printf("%s\n", p->pwd);
	g_global.status = 0;
}
