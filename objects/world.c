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
	t_hit_record	temp_rec; // * geçici çarpma kaydı 
	bool			hit_anything; // * herhangi bir şeye çarpma durumu
	double			closest_so_far; // * şimdiye kadar bulunan en yakın çarpma noktası
	t_list			*current_node; // * dünyadaki mevcut nesne düğümü
	t_hit_status	temp_status; // * geçici çarpma durumu

	hit_anything = false; // * başlangıçta herhangi bir şeye çarpmadı
	closest_so_far = status->t_max; // * başlangıçta en yakın çarpma noktası maksimum t değeri
	current_node = world; // * dünyadaki ilk nesne düğümü
	temp_status = *status; // * geçici çarpma durumu kopyalandı
	temp_status.rec = &temp_rec; // * geçici çarpma kaydı atandı
	while (current_node) // * dünyadaki tüm nesneler için çarpma testi yapıldı
	{
		temp_status.t_max = closest_so_far; // * şimdiye kadar bulunan en yakın çarpma noktasına güncellendi
		if (((t_object *)current_node->content)->hit(current_node->content,
				&temp_status)) // * mevcut nesneye çarpma testi yapıldı
		{
			hit_anything = true; // * herhangi bir şeye çarptı
			closest_so_far = temp_rec.t; // * en yakın çarpma noktası güncellendi
			*(status->rec) = temp_rec; // * çarpma kaydı güncellendi
		}
		current_node = current_node->next; // * sonraki nesne düğümüne geçildi
	}
	return (hit_anything); // * herhangi bir şeye çarpma durumu döndürüldü
}
