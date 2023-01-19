/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_2_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akashets <akashets@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:24:05 by akashets          #+#    #+#             */
/*   Updated: 2023/01/19 12:15:38 by akashets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/pipex_bonus.h"

void	single_quota(char *str, char **res, t_parsing *tab)
{
	tab->i++;
	res[tab->j] = malloc(sizeof(char) * (ft_tab_len(str, 39, tab->i) + 1));
	if (!res)
		return ;
	while (str[tab->i] != '\0' && str[tab->i] != 39)
		res[tab->j][tab->count++] = str[tab->i++];
}

void	double_quota(char *str, char **res, t_parsing *tab)
{
	tab->i++;
	res[tab->j] = malloc(sizeof(char) * (ft_tab_len(str, 34, tab->i) + 1));
	if (!res)
		return ;
	while (str[tab->i] != '\0' && str[tab->i] != 34)
		res[tab->j][tab->count++] = str[tab->i++];
}

void	space_case(char *str, char **res, t_parsing *tab)
{
	res[tab->j] = malloc(sizeof(char) * (ft_tab_len(str, ' ', tab->i) + 1));
	if (!res)
		return ;
	while (str[tab->i] != '\0' && str[tab->i] != ' ')
		res[tab->j][tab->count++] = str[tab->i++];
}
