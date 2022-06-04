/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 20:22:19 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/04 20:22:45 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chrjoin(char *str, char c, bool is_free_old_str)
{
	char	*new_str;
	size_t	i;

	if (str == NULL)
	{
		new_str = malloc(sizeof(char) * 2);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (new_str == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	if (is_free_old_str)
		free(str);
	return (new_str);
}
