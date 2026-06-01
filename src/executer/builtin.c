#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "builtin.h"
#include "libft.h"

int is_parent_builtin(const char *name)
{
    if (!name)
        return 0;
    if (ft_strncmp(name, "cd", ft_strlen("cd") + 1) == 0)
        return 1;
    if (ft_strncmp(name, "exit", ft_strlen("exit") + 1) == 0)
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

        if (!node->args[1] || node->args[2])
        {
            ft_putstr_fd("minishell: cd: path required\n", STDERR_FILENO);
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
        int code = 0;
        if (node->args[1])
            code = ft_atoi(node->args[1]);
        shell->exit_code = code;
        shell->running = 0;
        return shell->exit_code;
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
        while (shell->envp && shell->envp[i])
        {
            write(STDOUT_FILENO, shell->envp[i], ft_strlen(shell->envp[i]));
            write(STDOUT_FILENO, "\n", 1);
            i++;
        }
        return 0;
    }
    return -1;
}
