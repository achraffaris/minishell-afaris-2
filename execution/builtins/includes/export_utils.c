#include "../builtins.h"



// append or overwrite

/*

export ab+=text ---> create or update (key = ab, value = text)

ab = 2;
if export ab+=[value] ----> add [value]
if export ab=[value]  ----> overwrite with [value]

if '=' or '+=' not found in arg, and key is valid, then value ===> NULL;

if arg start with something different then (a-z, A-Z, '_') before '=' or '+=' 
                        then arg is not valid;

*/

char    *copy_sub_string(char *arg, int index)
{
    int     i;
    char    *copy;

    i = 0;
    copy = malloc(sizeof(char) * (index + 1));
    if (!copy)
        raise_error("Memory Allocation Failed!", "malloc", EXIT_FAILURE, TRUE);
    while (arg && arg[i] && i < index)
    {
        copy[i] = arg[i];
        i++;
    }
    copy[i] = '\0';
    return (copy);
}

void    create_or_update_env_item(t_env **env, char *arg)
{
    t_env *found;
    char *key;
    char *value;
    int index;

    index = get_index_or_none(arg, '=');
    value = NULL;
    found = NULL;
    key = extract_env_key(arg, index);
    if (key)
    {
        found = get_env_item_or_none(key, *env);
        if (!found)
            add_env_item(env, arg);
        else
        {
            value = extract_env_value(arg, index);
            update_env_value(found, value);
        }
    }
}