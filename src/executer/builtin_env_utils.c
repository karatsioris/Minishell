#include "builtin_internal.h"
#include "libft.h"

int	env_name_len(const char *entry)
{
	int	i;

	if (!entry)
		return (0);
	i = 0;
	while (entry[i] && entry[i] != '=')
		i++;
	return (i);
}

int	env_find_index(char **envp, const char *name)
{
	int	i;
	int	len;

	if (!envp || !name)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**env_realloc(char **envp, int new_count)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (new_count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < new_count)
	{
		if (envp)
			new_env[i] = envp[i];
		else
			new_env[i] = NULL;
		i++;
	}
	new_env[new_count] = NULL;
	return (new_env);
}

int	env_count(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

char	*make_env_entry(const char *name, const char *value)
{
	char	*tmp;
	char	*entry;

	if (!name || !value)
		return (NULL);
	tmp = ft_strjoin(name, "=");
	if (!tmp)
		return (NULL);
	entry = ft_strjoin(tmp, value);
	free(tmp);
	return (entry);
}
