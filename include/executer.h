/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:21:52 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:21:53 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "parse.h"

int		execute_ast(t_node *node, t_shell *shell);
void	free_tokens(t_token *tokens, int count);
void	free_ast(t_node *node);

#endif