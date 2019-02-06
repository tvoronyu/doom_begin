#include "wolf3d.h"

void    ft_error(int error, t_wolf *wolf)
{
    if (error == 1)
        ft_putendl("Error !");
    else if (error == 4)
        ft_putendl("Error map !");
    exit(0);
}

int     ft_valid_error_arr_pos(t_wolf *wolf)
{
    int n;

    wolf->width_arr = ft_atoi(wolf->full_map[0]);
    wolf->height_arr = ft_atoi(wolf->full_map[1]);
    wolf->raycast.posX = ft_atoi(wolf->full_map[2]);
    wolf->raycast.posY = ft_atoi(wolf->full_map[3]);
    wolf->pos_X = ft_atoi(wolf->full_map[2]);
    wolf->pos_Y = ft_atoi(wolf->full_map[3]);
    if (((!(n = ft_check_size_map(wolf)))) || wolf->width_arr != n
    || wolf->height_arr != wolf->counter_str_on_map - 4 || wolf->width_arr < 3
    || ft_check_min_size_map(wolf) || ft_check_pos_player(wolf)
    || wolf->array[wolf->pos_Y - 1][wolf->pos_X - 1] != 0)
        return (1);
    return (0);
}

int     ft_valid(t_wolf *wolf)
{
    if (wolf->counter_str_on_map >= 7)
    {
        if (ft_valid_error_arr_pos(wolf))
            return (1);
    }
    else
        ft_error(4, wolf);
    return (0);
}