/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 03:40:55 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/04 04:10:18 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	display_usage_with_exit(void);

int	main(void)
{
	display_usage_with_exit();
	return (0);
}

static void	display_usage_with_exit(void)
{
	ft_putstr_fd(ESC_CLR_RED, STDERR_FILENO);
	perror(ARG_ERR_MSG);
	ft_putstr_fd(ESC_RESET, STDERR_FILENO);
	ft_putstr_fd("Usage:\n  ./pipex <infile> <cmd1> <cmd2> <outfile>\n",
		STDOUT_FILENO);
	ft_putstr_fd("  ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <outfile>\n",
		STDOUT_FILENO);
	exit(EXIT_FAILURE);
}
