/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 23:19:53 by mher              #+#    #+#             */
/*   Updated: 2022/06/05 16:15:05 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	get_tmp_file_no(void)
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
		file_name = ft_strjoin("tmp_file_", str_no);
		if (is_exist_file(file_name) == 0)
			return (file_name);
		free(file_name);
		free(str_no);
	}
}

void	delete_tmp_file(void)
{
	int	tmp_no;
	char	*str_no;
	char	*file_name;

	tmp_no = get_tmp_file_no();
	while (--tmp_no > -1)
	{
		str_no = ft_itoa(tmp_no);
		file_name = ft_strjoin("tmp_file_", str_no);
		if (is_exist_file(file_name)) 
			unlink(file_name);
		free(str_no);
		free(file_name);
	}
	return ;
}
