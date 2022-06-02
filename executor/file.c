/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 01:46:25 by mher              #+#    #+#             */
/*   Updated: 2022/06/02 02:06:13 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	get_tmp_file_no(void)
{
	static int	tmp_file_no;

	return (tmp_file_no++);
}

char	*get_tmp_file_name(void)
{
	int	tmp_no;
	char	*str_no;
	char	*file_name;

	while (1)
	{
		tmp_no = get_tmp_file_no();
		str_no = ft_itoa(tmp_no);
		if (str_no == NULL)
			return (NULL);
		file_name = ft_strjoin("tmp_file_", str_no);
		if (file_name == NULL)
			return (NULL);
		if (access(file_name, F_OK) == -1)
			return (file_name);
		free(file_name);
	}
}
