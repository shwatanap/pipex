/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 09:31:31 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/03 23:49:38 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t size)
{
	size_t	len;
	char	*new_char;

	len = ft_strlen(str);
	if (len < size)
		size = len;
	new_char = (char *)malloc(sizeof(char) * (size + 1));
	if (new_char == NULL)
		return (NULL);
	ft_strlcpy(new_char, str, size + 1);
	return (new_char);
}
