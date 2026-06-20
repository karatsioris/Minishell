#include "parser_expand.h"

char	*lookup_env_value(char **envp, const char *name, int name_len)
{
	int	i;

	if (!envp || !name || name_len <= 0)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

char	*append_str(char *base, const char *suffix)
{
	char	*joined;

	if (!base || !suffix)
		return (NULL);
	joined = ft_strjoin(base, suffix);
	free(base);
	return (joined);
}

static char	*expand_exit_status(t_shell *shell, char *result, int *index)
{
	char	*status;

	status = ft_itoa(shell->exit_code);
	if (!status)
		return (NULL);
	result = append_str(result, status);
	free(status);
	*index += 2;
	return (result);
}

static char	*expand_var_name(const char *value, int *index, t_shell *shell,
		char *result)
{
	int		name_start;
	int		name_len;
	char	*env_value;

	name_start = *index + 1;
	name_len = name_start;
	while (value[name_len] == '_' || ft_isalnum(value[name_len]))
		name_len++;
	env_value = lookup_env_value(shell->envp, value + name_start,
			name_len - name_start);
	result = append_str(result, env_value ? env_value : "");
	*index = name_len;
	return (result);
}

char	*expand_dollar(const char *value, int *index, t_shell *shell,
		char *result)
{
	if (value[*index + 1] == '?')
		return (expand_exit_status(shell, result, index));
	if (value[*index + 1] == '\0')
	{
		result = append_str(result, "$");
		(*index)++;
		return (result);
	}
	if (value[*index + 1] == '_' || ft_isalpha(value[*index + 1]))
		return (expand_var_name(value, index, shell, result));
	result = append_str(result, "$");
	(*index)++;
	return (result);
}
