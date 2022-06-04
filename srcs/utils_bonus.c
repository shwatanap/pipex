/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:56:50 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/04 22:51:19 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
		perror_with_exit("open_file");
	if (file == FAIL)
		perror_with_exit("open");
	return (file);
}

bool	ft_read_line(char **line)
{
	ssize_t	read_size;
	char	c;

	c = '0';
	while (c != '\n' && c != '\0')
	{
		read_size = read(STDIN_FILENO, &c, sizeof(char));
		if (read_size == FAIL)
			perror_with_exit("read");
		if (read_size == 0)
			break ;
		if (c != '\n' && c != '\0')
		{
			if (*line == NULL)
				*line = ft_chrjoin(*line, c, false);
			else
				*line = ft_chrjoin(*line, c, true);
		}
	}
	if (c == '\n')
		*line = ft_chrjoin(*line, '\n', true);
	*line = ft_chrjoin(*line, '\0', true);
	if (read_size == 0)
		return (true);
	return (false);
}
