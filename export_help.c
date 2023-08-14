/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlhafi <youlhafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 08:28:41 by youlhafi          #+#    #+#             */
/*   Updated: 2023/08/10 13:15:10 by youlhafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_exist(t_pip *p, char *name)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (name[j] && name[j] != '=' && name[j] != '+')
		j++;
	while (p->envp[i])
	{
		if (ft_strncmp(p->envp[i], name, j) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	return_valid(char *name, int i)
{
	if (name[i] == '+')
	{
		if (name[i + 1] == '=')
			return (1);
		else
			return (0);
	}
	return (1);
}

int	if_valid_name(char *name)
{
	int	i;

	i = 0;
	if (ft_strlen(name) == 0)
		return (0);
	if (name[0] == '=')
		return (0);
	if (name[0] >= '0' & name[0] <= '9')
		return (0);
	while (name[i] != '=' && name[i] != '+')
	{
		if ((name[i] >= 0 && name[i] <= 47)
			|| (name[i] >= 58 && name [i] < 61)
			|| (name[i] > 61 && name [i] < 65)
			|| (name[i] > 90 && name [i] < 95)
			|| (name[i] > 122 && name [i] <= 127)
			|| name[i] == 96)
			return (0);
		i++;
	}
	return (return_valid(name, i));
}

int	if_valid_name_export(char *name)
{
	int	i;

	i = 0;
	if (ft_strlen(name) == 0)
		return (0);
	if (name[0] >= '0' & name[0] <= '9')
		return (0);
	while (name[i])
	{
		if (name[i] == '+' || name[i] == '=')
			return (0);
		if ((name[i] >= 0 && name[i] <= 47)
			|| (name[i] >= 58 && name [i] < 61)
			|| (name[i] > 61 && name [i] < 65)
			|| (name[i] > 90 && name [i] < 95)
			|| (name[i] > 122 && name [i] <= 127)
			|| name[i] == 96)
			return (0);
		i++;
	}
	return (1);
}

// void	print_export(t_pip *p)
// {
// 	int	i;
// 	char **split;

// 	i = 0;
// 	if (p->envp)
// 	{
// 		while (p->envp[i])
// 		{
// 			write (1, "declare -x ", 11);
// 			split = ft_split(p->envp[i], '=');
// 			write(1, split[0], ft_strlen(split[0]));
// 			write(1, "=\"", 2);
// 			write(1, split[1], ft_strlen(split[1]));
// 			write(1, "\"", 1);
// 			write (1, "\n", 1);
// 			free_double(split);
// 			i++;
// 		}
// 	}
// 	i = 0;
// 	if (p->export)
// 	{
// 		while (p->export[i])
// 		{
// 			write (1, "declare -x ", 11);
// 			write(1, p->export[i], ft_strlen(p->export[i]));
// 			write (1, "\n", 1);
// 			i++;
// 		}
// 	}
// 	g_global.status = 0;
// }
char *get_name(char *str)
{
	int i;
	char *ret;
	
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	ret = malloc(sizeof(char) * i + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while(str[i] != '=')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char *get_value(char *str)
{
	int i;
	char *ret;
	int j;
	int k;
	
	j = 0;
	i = 0;
	while(str[i] && str[i] != '=')
		i++;
	if (str[i + 1] == '\0')
		return (ft_strdup(""));
	i++;
	k = i;
	while(str[i])
	{
		i++;
		j++;
	}
	ret = malloc(sizeof(char) * j + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (str[k])
	{
		ret[i] = str[k];
		i++;
		k++;
	}
	ret[i] = '\0';
	return (ret);
}

void	print_export(t_pip *p)
{
	int	i;
	char *name;
	char *value;

	i = 0;
	if (p->envp)
	{
		while (p->envp[i])
		{
			write (1, "declare -x ", 11);
			name = get_name(p->envp[i]);
			value = get_value(p->envp[i]);
			write(1, name, ft_strlen(name));
			write(1, "=\"", 2);
			write(1, value, ft_strlen(value));
			write(1, "\"", 1);
			write (1, "\n", 1);
			free(name);
			free(value);
			i++;
		}
	}
	i = 0;
	if (p->export)
	{
		while (p->export[i])
		{
			write (1, "declare -x ", 11);
			write(1, p->export[i], ft_strlen(p->export[i]));
			write (1, "\n", 1);
			i++;
		}
	}
	g_global.status = 0;
}
