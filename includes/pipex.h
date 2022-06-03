/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:31:18 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/03 22:55:11 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define FAIL -1
# define CPID 0
# define PIPE_IN_FD 0
# define PIPE_OUT_FD 1
# define SUCCESS 0

// utils.c
void	perror_with_exit(const char *str);
void	execute(char *argv, char **envp);

#endif
