/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaratsi <kkaratsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:43:35 by kkaratsi          #+#    #+#             */
/*   Updated: 2026/06/18 14:44:42 by kkaratsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "stdlib.h"

typedef struct s_memory
{
	size_t	capacity;
	size_t	size;
}	t_memory;

#endif