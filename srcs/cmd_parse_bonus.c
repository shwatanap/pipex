/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parse_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:51:41 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/07 23:24:23 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static bool	switch_has_single_quart(bool has_single_quart);
static char	**convert_list_to_str_arr(t_list *cmd_list);
static char	*str_cpy(t_list *cmd_list);

char	**cmd_parse(char *cmd)
{
	size_t	i;
	bool	has_single_quart;
	t_list	*cmd_list;
	t_list	*new_node;

	i = 0;
	has_single_quart = false;
	cmd_list = ft_lstnew(cmd);
	if (cmd_list == NULL)
		perror_with_exit("ft_lstnew");
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'')
			has_single_quart = switch_has_single_quart(has_single_quart);
		if (cmd[i] == ' ' && cmd[i + 1] != '\0' && !has_single_quart)
		{
			new_node = ft_lstnew(&cmd[i + 1]);
			if (new_node == NULL)
				perror_with_exit("ft_lstnew");
			ft_lstadd_back(&cmd_list, new_node);
		}
		i++;
	}
	return (convert_list_to_str_arr(cmd_list));
}

static bool	switch_has_single_quart(bool has_single_quart)
{
	if (has_single_quart)
		return (false);
	return (true);
}

static char	**convert_list_to_str_arr(t_list *cmd_list)
{
	size_t	i;
	char	**cmd_str_arr;
	char	*tmp;

	cmd_str_arr = (char **)malloc(sizeof(char *) * (ft_lstsize(cmd_list) + 1));
	if (cmd_str_arr == NULL)
		perror_with_exit("malloc");
	i = 0;
	while (cmd_list != NULL)
	{
		cmd_str_arr[i] = str_cpy(cmd_list);
		tmp = ft_remove_chr(cmd_str_arr[i], '\'');
		free(cmd_str_arr[i]);
		cmd_str_arr[i] = tmp;
		if (cmd_str_arr[i] == NULL)
			perror_with_exit("ft_strdup");
		cmd_list = cmd_list->next;
		i++;
	}
	cmd_str_arr[i] = NULL;
	return (cmd_str_arr);
}

static char	*str_cpy(t_list *cmd_list)
{
	char	*dest;
	size_t	str_len;

	if (cmd_list->next == NULL)
	{
		dest = ft_strdup(cmd_list->content);
		if (dest == NULL)
			perror("ft_strdup");
		return (dest);
	}
	str_len = (size_t)(cmd_list->next->content - cmd_list->content);
	dest = ft_substr(cmd_list->content, 0, str_len - 1);
	if (dest == NULL)
		perror("ft_substr");
	return (dest);
}
