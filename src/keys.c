/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvoronyu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 19:30:34 by tvoronyu          #+#    #+#             */
/*   Updated: 2019/01/24 19:39:13 by tvoronyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void    clearCanvas(t_wolf *wolf)
{
    int x, y;

    x = y = 0;

    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            wolf->buf[y][x] = 0;
            x++;
        }
        y++;
    }
}

void	ft_keys_2(t_wolf *wolf)
{
	if (wolf->keys[SDL_SCANCODE_LEFT])
	{

	}
	if (wolf->keys[SDL_SCANCODE_W])
	{
        wolf->fPlayerX += (int)(wolf->playerXDir * wolf->fPlayerSpeed);
        wolf->fPlayerY += (int)(wolf->playerYDir * wolf->fPlayerSpeed);
	}
}

void	ft_keys_3(t_wolf *wolf)
{
	if (wolf->keys[SDL_SCANCODE_S])
	{
        wolf->fPlayerX -= (int)(wolf->playerXDir * wolf->fPlayerSpeed);
        wolf->fPlayerY -= (int)(wolf->playerYDir * wolf->fPlayerSpeed);
	}
	if (wolf->keys[SDL_SCANCODE_D])
	{

	}
	if (wolf->keys[SDL_SCANCODE_UP] && wolf->fPlayerHeight + 1 < wolf->WALL_HEIGHT)
    {

    }
	if (wolf->keys[SDL_SCANCODE_DOWN] && wolf->fPlayerHeight - 10 > 0)
    {

    }
}

void	ft_keys_4(t_wolf *wolf)
{
	if (wolf->keys[SDL_SCANCODE_A])
	{

	}
	if (wolf->keys[SDL_SCANCODE_Q] && wolf->fPlayerHeight + 2 < wolf->WALL_HEIGHT)
	{
		wolf->fPlayerHeight += 2;
	}
	if (wolf->keys[SDL_SCANCODE_E] && wolf->fPlayerHeight - 2 > 10)
	{
		wolf->fPlayerHeight -= 2;
	}
}

void	ft_keys_help(t_wolf *wolf)
{
	ft_keys_1(wolf);
	ft_keys_2(wolf);
	ft_keys_3(wolf);
	ft_keys_4(wolf);
}

void	ft_keys_1(t_wolf *wolf)
{
    if (wolf->keys[SDL_SCANCODE_RIGHT])
    {

    }
}

void	ft_moveLeft(t_wolf *wolf)
{
	if (wolf->sdl.event.motion.xrel > 0 && wolf->sdl.event.motion.xrel < 1000)
	{
		if ((wolf->fPlayerArc += (wolf->sdl.event.motion.xrel * 1.5)) >= wolf->ANGLE360)
			wolf->fPlayerArc -= wolf->ANGLE360;
		wolf->sdl.event.motion.xrel = 0;
	}
	else if (wolf->sdl.event.motion.xrel > -1000 && wolf->sdl.event.motion.xrel < 0)
	{
		if ((wolf->fPlayerArc -= -(wolf->sdl.event.motion.xrel * 1.5)) <= wolf->ANGLE0)
			wolf->fPlayerArc += wolf->ANGLE360;
		wolf->sdl.event.motion.xrel = 0;
	}
	if (wolf->sdl.event.motion.yrel > 0 && wolf->sdl.event.motion.yrel < 1000)
	{
		wolf->fProjectionPlaneYCenter -= wolf->sdl.event.motion.yrel;
		wolf->sdl.event.motion.yrel = 0;
	}
	else if (wolf->sdl.event.motion.yrel > -1000 && wolf->sdl.event.motion.yrel < 0)
	{
	    wolf->fProjectionPlaneYCenter += -wolf->sdl.event.motion.yrel;
		wolf->sdl.event.motion.yrel = 0;
	}
}

void	keys(t_wolf *wolf)
{
	wolf->playerXDir = wolf->fCosTable[wolf->fPlayerArc];
	wolf->playerYDir = wolf->fSinTable[wolf->fPlayerArc];

    clearCanvas(wolf);

	wolf->keys = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&wolf->sdl.event))
		ft_moveLeft(wolf);
    ft_pause_2(wolf);
	ft_keys_help(wolf);
}
