/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_expand.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:22:12 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:22:13 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_EXPAND_H
# define PARSER_EXPAND_H

# include "token.h"
# include "shell.h"

int		apply_expansions(t_token *tokens, int count, t_shell *shell);
char	*expand_token_value(const char *value, t_shell *shell,
			t_quote_state quote);
char	*expand_dollar(const char *value, int *index, t_shell *shell,
			char *result);
char	*lookup_env_value(char **envp, const char *name, int name_len);
char	*append_str(char *base, const char *suffix);

#endif
