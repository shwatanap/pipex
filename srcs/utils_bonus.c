/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:56:50 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/04 14:27:39 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * @brief
 *
 * @param file_path
 * @param i
 * @return int
 */
int	open_file(char *file_path, t_open_mode i)
{
	int	file;

	file = 0;
	if (i == FILE_APPEND_WRITE)
		file = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == FILE_OVER_WRITE)
		file = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == FILE_READ)
		file = open(file_path, O_RDONLY, 0777);
	else
		perror("open_file");
	if (file == -1)
		error();
	return (file);
}
