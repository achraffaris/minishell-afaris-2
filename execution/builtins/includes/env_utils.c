#include "../builtins.h"

int env_key_valid(char *env_key)
{
    int i;

    i = 0;
    if (!(ft_isalpha(env_key[0]) || env_key[0] == '_'))
        return (FALSE);
    while (env_key[i])
    {
        if (!(ft_isalnum(env_key[i])
                || ft_isdigit(env_key[i])
                || env_key[i] == '_'))
            return (FALSE);
        i++;
    }
    return (TRUE);
}

char    *extract_env_key(char *item, int index)
{
    char    *env_key;

    env_key = NULL;
    if (index == NONE)
        env_key = ft_strdup(item);
    else if (index > 0)
        env_key = copy_sub_string(item, index);
    if (!env_key || !(env_key && env_key_valid(env_key)))
    {
        raise_error("Not a valid identifier", item, EXIT_FAILURE, FALSE);
        return (NULL);
    }
    return (env_key);
}

char    *extract_env_value(char *item, int index)
{
    if (index == NONE)
        return (NULL);
    else if (item[index + 1])
        return (ft_strdup(&item[index + 1]));
    else
        return (ft_calloc(1, 1));
}

void    add_env_item(t_env **head, char *item)
{
    t_env *current;
    t_env *new;
    int index;
    
    current = *head;
    index = get_index_or_none(item, '=');
    new = malloc(sizeof(t_env));
    if (!new)
        raise_error("Memory Allocation Failed!", "malloc", EXIT_FAILURE, TRUE);
    while (current && current->next)
        current = current->next;
    new->key = extract_env_key(item, index);
    if (!new->key)
        return (free(new));
    new->value = extract_env_value(item, index);
    new->is_printed = FALSE;
    new->next = NULL;
    if (!(*head))
        *head = new;
    else
        current->next = new;
}

t_env   *setup_env(char **env)
{
    t_env *head;
    int i;

    i = 0;
    head = NULL;
    while (env[i])
    {
        add_env_item(&head, env[i]);
        i++;
    }
    return (head);
}