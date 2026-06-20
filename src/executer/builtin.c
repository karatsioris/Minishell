#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "builtin.h"
#include "libft.h"

static int is_valid_exit_arg(const char *arg)
{
    int i;

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

static int is_valid_identifier(const char *name)
{
    int i;

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

static int env_name_len(const char *entry)
{
    int i;

    if (!entry)
        return (0);
    i = 0;
    while (entry[i] && entry[i] != '=')
        i++;
    return (i);
}

static int env_find_index(char **envp, const char *name)
{
    int i;
    int len;

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

static char **env_realloc(char **envp, int new_count)
{
    char **new_env;
    int i;

    new_env = malloc(sizeof(char *) * (new_count + 1));
    if (!new_env)
        return (NULL);
    i = 0;
    while (i < new_count)
    {
        new_env[i] = envp ? envp[i] : NULL;
        i++;
    }
    new_env[new_count] = NULL;
    return (new_env);
}

static int env_count(char **envp)
{
    int count;

    count = 0;
    while (envp && envp[count])
        count++;
    return (count);
}

static char *make_env_entry(const char *name, const char *value)
{
    char *tmp;
    char *entry;

    if (!name || !value)
        return (NULL);
    tmp = ft_strjoin(name, "=");
    if (!tmp)
        return (NULL);
    entry = ft_strjoin(tmp, value);
    free(tmp);
    return (entry);
}

static int set_env_value(t_shell *shell, const char *name, const char *value)
{
    int index;
    int count;
    char *entry;
    char **new_env;

    if (!shell || !name || !value)
        return (1);
    entry = make_env_entry(name, value);
    if (!entry)
        return (1);
    index = env_find_index(shell->envp, name);
    if (index >= 0)
    {
        free(shell->envp[index]);
        shell->envp[index] = entry;
        return (0);
    }
    count = env_count(shell->envp);
    new_env = env_realloc(shell->envp, count + 1);
    if (!new_env)
    {
        free(entry);
        return (1);
    }
    new_env[count] = entry;
    free(shell->envp);
    shell->envp = new_env;
    return (0);
}

static int unset_env_value(t_shell *shell, const char *name)
{
    int index;
    int count;
    char **new_env;
    int i;

    if (!shell || !name)
        return (1);
    index = env_find_index(shell->envp, name);
    if (index < 0)
        return (0);
    free(shell->envp[index]);
    count = env_count(shell->envp);
    new_env = malloc(sizeof(char *) * count);
    if (!new_env)
        return (1);
    i = 0;
    while (i < index)
    {
        new_env[i] = shell->envp[i];
        i++;
    }
    while (i < count - 1)
    {
        new_env[i] = shell->envp[i + 1];
        i++;
    }
    new_env[count - 1] = NULL;
    free(shell->envp);
    shell->envp = new_env;
    return (0);
}

static int env_entry_cmp(const char *a, const char *b)
{
    while (*a && *a == *b)
    {
        a++;
        b++;
    }
    return ((unsigned char)*a - (unsigned char)*b);
}

static void sort_env_entries(char **sorted, int count)
{
    int     i;
    int     j;
    char    *tmp;

    i = 1;
    while (i < count)
    {
        j = i;
        while (j > 0 && env_entry_cmp(sorted[j - 1], sorted[j]) > 0)
        {
            tmp = sorted[j - 1];
            sorted[j - 1] = sorted[j];
            sorted[j] = tmp;
            j--;
        }
        i++;
    }
}

char **dup_envp(char **envp)
{
    char **dup;
    int count;
    int i;

    count = env_count(envp);
    dup = malloc(sizeof(char *) * (count + 1));
    if (!dup)
        return (NULL);
    i = 0;
    while (i < count)
    {
        dup[i] = ft_strdup(envp[i]);
        if (!dup[i])
        {
            while (i > 0)
                free(dup[--i]);
            free(dup);
            return (NULL);
        }
        i++;
    }
    dup[count] = NULL;
    return (dup);
}

void free_envp(char **envp)
{
    int i;

    if (!envp)
        return ;
    i = 0;
    while (envp[i])
    {
        free(envp[i]);
        i++;
    }
    free(envp);
}

int is_parent_builtin(const char *name)
{
    if (!name)
        return 0;
    if (ft_strncmp(name, "cd", ft_strlen("cd") + 1) == 0)
        return 1;
    if (ft_strncmp(name, "exit", ft_strlen("exit") + 1) == 0)
        return 1;
    if (ft_strncmp(name, "export", ft_strlen("export") + 1) == 0)
        return 1;
    if (ft_strncmp(name, "unset", ft_strlen("unset") + 1) == 0)
        return 1;
    return 0;
}

int run_builtin_parent(t_node *node, t_shell *shell)
{
    if (!node || !node->args || !node->args[0])
        return 0;
    if (ft_strncmp(node->args[0], "cd", ft_strlen("cd") + 1) == 0)
    {
        const char *path;

        if (!node->args[1])
        {
            ft_putstr_fd("minishell: cd: path required\n", STDERR_FILENO);
            shell->exit_code = 1;
            return 1;
        }
        if (node->args[2])
        {
            ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
            shell->exit_code = 1;
            return 1;
        }
        path = node->args[1];
        if (chdir(path) != 0)
        {
            perror("minishell: cd");
            shell->exit_code = 1;
            return 1;
        }
        shell->exit_code = 0;
        return 0;
    }
    else if (ft_strncmp(node->args[0], "exit", ft_strlen("exit") + 1) == 0)
    {
        if (node->args[1] && node->args[2])
        {
            ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
            shell->exit_code = 1;
            return 1;
        }
        if (node->args[1] && !is_valid_exit_arg(node->args[1]))
        {
            ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
            ft_putstr_fd(node->args[1], STDERR_FILENO);
            ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
            shell->exit_code = 2;
            shell->running = 0;
            return shell->exit_code;
        }
        if (node->args[1])
            shell->exit_code = ft_atoi(node->args[1]);
        shell->running = 0;
        return shell->exit_code;
    }
    if (ft_strncmp(node->args[0], "export", ft_strlen("export") + 1) == 0)
    {
        int i;
        int status;

        status = 0;
        if (!node->args[1])
        {
            char **sorted;
            int count;
            int j;

            count = env_count(shell->envp);
            sorted = malloc(sizeof(char *) * (count + 1));
            if (!sorted)
                return (1);
            i = 0;
            while (i < count)
            {
                sorted[i] = shell->envp[i];
                i++;
            }
            sorted[count] = NULL;
            sort_env_entries(sorted, count);
            j = 0;
            while (j < count)
            {
                int name_len = env_name_len(sorted[j]);
                write(STDOUT_FILENO, "declare -x ", 11);
                write(STDOUT_FILENO, sorted[j], name_len);
                if (sorted[j][name_len] == '=')
                {
                    write(STDOUT_FILENO, "=\"", 2);
                    write(STDOUT_FILENO, sorted[j] + name_len + 1, ft_strlen(sorted[j] + name_len + 1));
                    write(STDOUT_FILENO, "\"", 1);
                }
                write(STDOUT_FILENO, "\n", 1);
                j++;
            }
            free(sorted);
            return (0);
        }
        i = 1;
        while (node->args[i])
        {
            char *equal;
            char *name;

            equal = ft_strchr(node->args[i], '=');
            if (equal)
                name = ft_substr(node->args[i], 0, equal - node->args[i]);
            else
                name = ft_strdup(node->args[i]);
            if (!is_valid_identifier(name))
            {
                ft_putstr_fd("minishell: export: not a valid identifier\n", STDERR_FILENO);
                status = 1;
                free(name);
                i++;
                continue;
            }
            if (equal)
                status |= set_env_value(shell, name, equal + 1);
            else if (env_find_index(shell->envp, name) < 0)
                status |= set_env_value(shell, name, "");
            free(name);
            i++;
        }
        shell->exit_code = status;
        return (status);
    }
    if (ft_strncmp(node->args[0], "unset", ft_strlen("unset") + 1) == 0)
    {
        int i;
        int status;

        status = 0;
        i = 1;
        while (node->args[i])
        {
            if (!is_valid_identifier(node->args[i]))
            {
                ft_putstr_fd("minishell: unset: not a valid identifier\n", STDERR_FILENO);
                status = 1;
            }
            else
                status |= unset_env_value(shell, node->args[i]);
            i++;
        }
        shell->exit_code = status;
        return (status);
    }
    return 0;
}

int run_builtin_child(t_node *node, t_shell *shell)
{
    if (!node || !node->args || !node->args[0])
        return -1;
    if (ft_strncmp(node->args[0], "echo", ft_strlen("echo") + 1) == 0)
    {
        int i = 1;
        int newline = 1;
        while (node->args[i] && ft_strncmp(node->args[i], "-n", 2) == 0)
        {
            int j = 2;
            int all_n = 1;
            while (node->args[i][j])
            {
                if (node->args[i][j] != 'n')
                {
                    all_n = 0;
                    break;
                }
                j++;
            }
            if (all_n)
                newline = 0;
            else
                break;
            i++;
        }
        int first = 1;
        while (node->args[i])
        {
            if (!first)
                write(STDOUT_FILENO, " ", 1);
            write(STDOUT_FILENO, node->args[i], ft_strlen(node->args[i]));
            first = 0;
            i++;
        }
        if (newline)
            write(STDOUT_FILENO, "\n", 1);
        return 0;
    }
    if (ft_strncmp(node->args[0], "pwd", ft_strlen("pwd") + 1) == 0)
    {
        char buf[PATH_MAX];
        if (getcwd(buf, sizeof(buf)))
        {
            write(STDOUT_FILENO, buf, ft_strlen(buf));
            write(STDOUT_FILENO, "\n", 1);
            return 0;
        }
        perror("minishell: pwd");
        return 1;
    }
    if (ft_strncmp(node->args[0], "env", ft_strlen("env") + 1) == 0)
    {
        int i = 0;

        if (node->args[1])
        {
            ft_putstr_fd("minishell: env: too many arguments\n", STDERR_FILENO);
            return (1);
        }
        while (shell->envp && shell->envp[i])
        {
            write(STDOUT_FILENO, shell->envp[i], ft_strlen(shell->envp[i]));
            write(STDOUT_FILENO, "\n", 1);
            i++;
        }
        return 0;
    }
    if (is_parent_builtin(node->args[0]))
        return (run_builtin_parent(node, shell));
    return -1;
}
