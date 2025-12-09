/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musisman <musisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:18:29 by musisman          #+#    #+#             */
/*   Updated: 2025/10/19 16:18:29 by musisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

bool	hit_world(t_list *world, t_hit_status *status)
{
	t_hit_record	temp_rec;
	bool			hit_anything;
	double			closest_so_far;
	t_list			*current_node;
	t_hit_status	temp_status;

	hit_anything = false;
	closest_so_far = status->t_max;
	current_node = world;
	temp_status = *status;
	temp_status.rec = &temp_rec;
	while (current_node)
	{
		temp_status.t_max = closest_so_far;
		if (((t_object *)current_node->content)->hit(current_node->content,
				&temp_status))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*(status->rec) = temp_rec;
		}
		current_node = current_node->next;
	}
	return (hit_anything);
}
