/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 12:27:51 by jtaylor           #+#    #+#             */
/*   Updated: 2020/01/15 17:19:43 by jtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "filler.h"

void		set_struct_val_zero(t_filler *filler)
{
	filler->piece = NULL;
	filler->map_in = NULL;
	filler->map = NULL;
	filler->last_x = -1;
	filler->last_xy = -1;
	filler->last_o = -1;
	filler->last_oy = -1;
	filler->map_dim_x = -1;
	filler->map_dim_y = -1;
	filler->piece_size_y = -1;
	filler->piece_size_x = -1;
	filler->check_start_x = -1;
	filler->check_start_y = -1;
	filler->player = -1;
	filler->p1_count = 0;
	filler->p2_count = 0;
}

static void	inner_struct_print_values(t_filler *filler, int fd)
{
	ft_dprintf(fd, "\nDUMP::\n\nvalues:\nlast_x\t%d\nlast_xy\t%d\nlast_o\
		\t%d\nlast_oy\t%d\nmap_dim_x\t%d\nmap_dim_y\t%d\npiece_size_y\
		\t%d\npiece_size_x\t%d\nplayer\t%d\n",
		filler->last_x, filler->last_xy, filler->last_o, filler->last_oy,
		filler->map_dim_x, filler->map_dim_y,
		filler->piece_size_y, filler->piece_size_x, filler->player);
	ft_dprintf(fd, "dir_prio:\t%d\ndir_x:\t%d\ndir_y:\t%d\n", filler->dir_prio,
			filler->dir_x, filler->dir_y);
}

void		dump_struct_contents(t_filler *filler, int fd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	inner_struct_print_values(filler, fd);
	ft_dprintf(fd, "Piece:\n");
	while (filler->piece[i])
		ft_dprintf(fd, "%s\n", filler->piece[i++]);
	i = 0;
	ft_dprintf(fd, "\nMap_in:\n");
	while (filler->map_in[i])
		ft_dprintf(fd, "%s\n", filler->map_in[i++]);
	ft_dprintf(fd, "Map:\n");
	i = 0;
	while (i < filler->map_dim_y)
	{
		j = 0;
		while (j < filler->map_dim_x)
			ft_dprintf(fd, "%d ", filler->map[i][j++]);
		ft_dprintf(fd, " ::%d\n", i++);
	}
}

static int	filler_loop(t_filler *filler)
{
	char	*line;
	int		i;

	while ((i = get_next_line(0, &line) >= 0))
	{
		if (!line)
			continue ;
		if (!ft_strncmp(line, "Plateau", 7))
		{
			free(line);
			get_next_line(0, &line);
			re_fetch(filler);
			find_placement(filler);
		}
		free(line);
	}
	return (i);
}

int			main(void)
{
	t_filler		filler;

	set_struct_val_zero(&filler);
	filler_parser(&filler);
	input_map_to_int_matrix(&filler);
	chose_direction_to_fill_in(&filler);
	find_placement(&filler);
	filler_loop(&filler);
	return (0);
}
