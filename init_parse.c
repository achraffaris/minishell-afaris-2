/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoukou <schoukou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 01:41:45 by schoukou          #+#    #+#             */
/*   Updated: 2022/11/03 23:08:53 by schoukou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_parse2(t_token *head, t_parse *tmp, t_lexer *lexer, t_rdr *rdr)
{
	if (head->e_type == 2 && head->next != NULL && head->next->e_type == 2)
		lexer->flg_error = 1;
	if (head->e_type == 0 && !lexer->flg_error)
		tmp->cmd = ft_strdup(head->value);
	else if (head->e_type == 1 && !lexer->flg_error)
	{
		if (!tmp->arg)
		{
			tmp->arg = malloc(sizeof(char *) * (count_arg(head) + 1));
			lexer->y = 0;
		}
		tmp->arg[lexer->y] = ft_strdup(head->value);
		tmp->arg[++lexer->y] = NULL;
	}
	if (((head->e_type == 4 || head->e_type == 5
		|| head->e_type == 6) && !lexer->flg_error ) || head->e_type == 3)
	{
		rdr = add_rdr(head->value, head->e_type, head->rdr_flg);
		add_back_rdr(&tmp->rdr, rdr);
	}
	return (lexer->y);
}

t_parse	*init_var(t_parse *tmp)
{
	tmp = malloc(sizeof(t_parse));
	tmp->arg = NULL;
	tmp->cmd = NULL;
	tmp->rdr = NULL;
	tmp->next = NULL;
	return (tmp);
}

t_parse	*init_parsing(t_token **token, t_lexer *lexer)
{
	t_token	*head;
	t_parse	*tmp;
	t_parse	*parse;
	t_rdr	*rdr;

	tmp = NULL;
	parse = NULL;
	rdr = NULL;
	head = *token;
	lexer->y = 0;
	if (head->e_type == 2)
	{
		lexer->flg_error = 1;
		return (NULL);
	}
	tmp = init_var(tmp);
	while (head)
	{
		if (head->e_type == 2 && head->next == NULL)
		{
			lexer->flg_error = 1;
			break ;
		}
		lexer->y = init_parse2(head, tmp, lexer, rdr);
		if (head->e_type == 2)
		{
			add_back_parse(&parse, tmp);
			tmp = init_var(tmp);
		}
		head = head->next;
	}
	add_back_parse(&parse, tmp);
	return (parse);
}
