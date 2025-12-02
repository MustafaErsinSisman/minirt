/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:06:26 by musisman          #+#    #+#             */
/*   Updated: 2025/12/02 15:06:26 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMBIENT_H
# define AMBIENT_H

typedef struct s_ambient
{
	double		range;
	t_vector3	rgb;
}	t_ambient;

#endif