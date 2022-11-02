/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:58:49 by hkhalil           #+#    #+#             */
/*   Updated: 2022/11/02 23:18:11 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int ac, char **av)
{
	char	**tab;
	t_info	*info;
	int		fd;

	fd = 0;
	(void)ac;
	tab = init_file(av[1], fd);
	if (to_parse(tab) != 0)
	{
		close(fd);
		free_tab(tab);
		return (0);
	}
	info = fill_infos(tab);
	//
	//add player direction (N == 3*M_PI/2, S == M_PI/2, E == 0, W == M_PI)
	t_data *game = malloc(sizeof(t_data));
	game->map = info->map;
	game->map_rows = info->map_y;
	game->map_columns = info->map_x;
	game->map_length = info->map_y * CUBE;
	game->map_width = info->map_x * CUBE;
	game->player_x = info->x*CUBE + CUBE/2;
	game->player_y = info->y*CUBE + CUBE/2;
	game->angle = ft_angle(info->dir);
	//game->resolution_x = game->map_width;
	game->num_of_rays = info->map_x * CUBE;
	game->mlx = mlx_init();
	game->mlx_window = mlx_new_window(game->mlx, game->map_width, game->map_length, "cub3d");
	
	render_walls(game);
	render_map(game);
	mlx_key_hook(game->mlx_window, key_hook, game);
	mlx_loop(game->mlx);
}