/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:45:17 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/06 19:53:16 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*replace_space_doble_quart(char *cmd)
{
	int		i;
	bool	has_single_quart;
	char	*new_char;

	i = 0;
	has_single_quart = false;
	new_char = ft_strdup(cmd);
	if (new_char == NULL)
		perror_with_exit("strdup");
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'')
		{
			if (has_single_quart)
				has_single_quart = false;
			else
				has_single_quart = true;
		}
		if (cmd[i] == ' ' && has_single_quart)
			new_char[i] = '\"';
		i++;
	}
	if (has_single_quart)
		perror_with_exit("invalid use single quart");
	return (new_char);
}

void	revert_replace_space(char **cmd)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (cmd[i] != NULL)
	{
		j = 0;
		while (cmd[i][j] != '\0')
		{
			if (cmd[i][j] == '\"')
			{
				cmd[i][j] = ' ';
			}
			j++;
		}
		tmp = ft_strtrim(cmd[i], "\'");
		free(cmd[i]);
		cmd[i] = tmp;
		i++;
	}
}
