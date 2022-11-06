#include "../execution.h"

char    *extract_cmd_path(char **paths, char *cmd)
{
    char *full_path;
    char *new_cmd;
    int i;

    i = 0;
    full_path = NULL;
    if (!paths)
        return (ft_strdup(cmd));
    new_cmd = ft_strjoinx("/", cmd);
    while (paths[i])
    {
        full_path = ft_strjoinx(paths[i], new_cmd);
        if (access(full_path, X_OK) != ERROR_RETURNED)
        {
            free_2d_buff(paths);
            free(new_cmd);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    free(new_cmd);
    free_2d_buff(paths);
    return (ft_strdup(cmd));
}

char    *find_cmd_path(char *cmd, t_env *env)
{
    t_env *current;
    char **paths;

    paths = NULL;
    current = env;
    while (current)
    {
        if (is_identical(current->key, PATH))
        {
            paths = ft_split(current->value, ':');
            break ;
        }
        current = current->next;
    }
    return (extract_cmd_path(paths, cmd));
}

char    **get_full_cmd(char *cmd, char **args)
{
    char **full_cmd;
    int i;
    int j;

    j = 0;
    i = 0;
    full_cmd = NULL;
    while (args && args[i])
        i++;
    full_cmd = malloc(sizeof(char *) * (i + 2));
    if (!full_cmd)
        raise_error("Memory allocation failed!", "malloc", EXIT_FAILURE, TRUE);
    i = 0;
    full_cmd[i] = ft_strdup(cmd);
    i++;
    while (args && args[j])
        full_cmd[i++] = ft_strdup(args[j++]);
    full_cmd[i] = NULL;
    return (full_cmd);
}

int cmds_len(t_parse *cmds)
{
    int i;
    t_parse *current;

    i = 0;
    current = cmds;
    while (current)
    {
        current = current->next;
        i++;
    }
    return (i);
}
