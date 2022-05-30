/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:00:41 by mher              #+#    #+#             */
/*   Updated: 2022/05/30 18:10:27 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*ft_getenv(t_env *env_head, char *key)
{
	t_env	*cur;

	cur = compare_env_key(env_head, key);
	return (cur->value);
}
