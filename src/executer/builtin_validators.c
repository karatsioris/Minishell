#include "builtin_internal.h"
#include "libft.h"

int	is_valid_exit_arg(const char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_identifier(const char *name)
{
	int	i;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_parent_builtin(const char *name)
{
	if (!name)
		return (0);
	if (ft_strncmp(name, "cd", ft_strlen("cd") + 1) == 0)
		return (1);
	if (ft_strncmp(name, "exit", ft_strlen("exit") + 1) == 0)
		return (1);
	if (ft_strncmp(name, "export", ft_strlen("export") + 1) == 0)
		return (1);
	if (ft_strncmp(name, "unset", ft_strlen("unset") + 1) == 0)
		return (1);
	return (0);
}
