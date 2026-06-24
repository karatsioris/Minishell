/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:43:28 by kkaratsi          #+#    #+#             */
/*   Updated: 2026/06/19 14:10:50 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "token.h"
# include "shell.h"

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	int				expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_node
{
	t_node_type		type;
	char			**args;
	t_redir			*redirs;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

// parser.c
t_token			*array_of_token(t_shell *shell, int *out_len);
t_node			*new_node(t_node_type type);
t_node			*parse_subtokens(t_token *tokens, int start, int end);
t_node			*parse_token(t_token *all_token, int count);
t_redir			*build_redir_list(t_token *tokens, int start, int end);

// parser_utils.c
int				find_pipe(t_token *tokens, int start, int end);
t_redir_type	get_redir_type(t_token token);
t_redir			*new_redir(t_redir_type type, char *file);
void			add_redir_back(t_redir **list, t_redir *new);

// parser_free_utils.c
void			free_ast(t_node *node);

// parser_cmd.c
t_node			*cmd_node(t_token *tokens, int start, int end);
char			**build_args_array(t_token *tokens, int start, int end);

#endif