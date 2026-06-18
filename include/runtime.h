/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 17:06:46 by kkaratsi          #+#    #+#             */
/*   Updated: 2026/06/18 17:33:29 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

# include "shell.h"
# include "token.h"
# include "parse.h"

int		evaluate_input(char	*line, t_shell	*shell);
void	initialization(t_shell	*shell);
void	cleanup(t_shell *shell, t_token	**all_token,
			int token_count, t_node **ast);

#endif
