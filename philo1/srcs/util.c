/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanhwang <sanhwang@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:41:43 by sanhwang          #+#    #+#             */
/*   Updated: 2024/11/20 20:22:36 by sanhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atoi(char *str)
{
    int i;
    int n;
    int r;

    i = 0;
    n = 1;
    r = 0;

    // Skip whitespaces
    while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
        i++;

    // Check sign
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            n = -1;
        i++;
    }

    // Parse digits
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
        r = (str[i++] - '0') + r * 10;

    return (r * n);
}
