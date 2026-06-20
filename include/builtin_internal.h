/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhensel <flhensel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:21:43 by flhensel          #+#    #+#             */
/*   Updated: 2026/06/20 14:21:44 by flhensel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_INTERNAL_H
# define BUILTIN_INTERNAL_H

# include "builtin.h"

// builtin_env_utils.c
int		env_name_len(const char *entry);
int		env_find_index(char **envp, const char *name);
char	**env_realloc(char **envp, int new_count);
int		env_count(char **envp);
char	*make_env_entry(const char *name, const char *value);

// builtin_env_set.c
int		set_env_value(t_shell *shell, const char *name, const char *value);
int		unset_env_value(t_shell *shell, const char *name);

// builtin_validators.c
int		is_valid_exit_arg(const char *arg);
int		is_valid_identifier(const char *name);

// builtin_cd_exit.c
int		builtin_cd(t_node *node, t_shell *shell);
int		builtin_exit(t_node *node, t_shell *shell);

// builtin_export_print.c
int		builtin_export_list(t_shell *shell);

// builtin_export_unset.c
int		builtin_export_set(t_node *node, t_shell *shell);
int		builtin_unset(t_node *node, t_shell *shell);

#endif
