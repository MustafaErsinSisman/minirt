/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:06:32 by musisman          #+#    #+#             */
/*   Updated: 2025/12/02 15:06:32 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

typedef struct s_light
{
	t_vector3	pos;
	double		range;
	t_vector3 rgb; // * şimdilik beyaz ışık varsayalım
}	t_light;
#endif