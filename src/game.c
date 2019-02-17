/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvoronyu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 19:25:50 by tvoronyu          #+#    #+#             */
/*   Updated: 2019/01/24 19:27:44 by tvoronyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

char **creatMapArray(int width, int height)
{
	char **map;

	map = NULL;
	map = (char**)malloc(sizeof(char *) * height + 1);
	map[height] = NULL;
	map[0]  = "WWWWWWWWWWWW";
	map[1]  = "WOOOOOOOOOOW";
	map[2]  = "WOOOOOOOOOOW";
	map[3]  = "WOWOOOOWOOOW";
	map[4]  = "WOOOQWOOOOOW";
	map[5]  = "WOOWOOOOOOOW";
	map[6]  = "WOOOWWWWOOOW";
	map[7]  = "WOOOOWWOOOOW";
	map[8]  = "WOWOOWOOOOOW";
	map[9]  = "WOOOOWOOOOOW";
	map[10] = "WOOOOOOOOOOW";
	map[11] = "WWWWWWWWWWWW";
	return (map);
}

void  creatMap(t_wolf *wolf)
{
	wolf->fMap = creatMapArray(wolf->MAP_WIDTH, wolf->MAP_HEIGHT);
}

float *newFloat(int len, float *tmp)
{
	tmp = (float*)malloc(sizeof(float) * len);
	ft_bzero(tmp, sizeof(float) * len);
	return (tmp);
}

float arcToRad(float arcAngle, t_wolf *wolf)
{
	return ((float)(arcAngle * 3.14)/(float)wolf->ANGLE180);
}

void	render_texture(t_wolf *wolf)
{
    SDL_UpdateTexture(wolf->sdl.screen, NULL, wolf->buf, WIDTH << 2);
    SDL_RenderCopy(wolf->sdl.ren, wolf->sdl.screen, NULL, NULL);
    SDL_RenderPresent(wolf->sdl.ren);
    SDL_FreeSurface(wolf->sdl.font_surface);
}

void    ft_render(t_wolf *wolf)
{
	int 	verticalGrid;
	int 	horizontalGrid;
	int 	distToNextVerticalGrid;
	int 	distToNextHorizontalGrid;
	float 	xIntersection;
	float 	yIntersection;
	float 	distToNextXIntersection;
	float 	distToNextYIntersection;
	int 	xGridIndex;
	int 	yGridIndex;
	float 	distToVerticalGridBeingHit;
	float 	distToHorizontalGridBeingHit;
	int 	castArc;
	int 	castColumn;

	castArc = wolf->fPlayerArc + (-wolf->ANGLE30);
	castColumn = -1;

	if (castArc < 0)
	{
		castArc = wolf->ANGLE360 + castArc;
	}
	while (castColumn++ < wolf->PROJECTIONPLANEWIDTH)
	{
//	    if (wolf->checkWall)
//        {
//	        wolf->TILE_SIZE += 64;
//	        wolf->WALL_HEIGHT += 64;
//        }
//	    else
//        {
//            wolf->TILE_SIZE = 64;
//            wolf->WALL_HEIGHT = 64;
//        }
		if (castArc > wolf->ANGLE0 && castArc < wolf->ANGLE180)
		{
			horizontalGrid = (wolf->fPlayerY / wolf->TILE_SIZE) * wolf->TILE_SIZE + wolf->TILE_SIZE;
			distToNextHorizontalGrid = wolf->TILE_SIZE;
			float xtemp = wolf->fITanTable[castArc] * (horizontalGrid - wolf->fPlayerY);
			xIntersection = xtemp + wolf->fPlayerX;
		}
		else
		{
			horizontalGrid = (wolf->fPlayerY / wolf->TILE_SIZE) * wolf->TILE_SIZE;
			distToNextHorizontalGrid = -wolf->TILE_SIZE;
			float xtemp = wolf->fITanTable[castArc] * (horizontalGrid - wolf->fPlayerY);
			xIntersection = xtemp + wolf->fPlayerX;
			horizontalGrid--;
		}
		if (castArc == wolf->ANGLE0 || castArc == wolf->ANGLE180)
			distToHorizontalGridBeingHit = 9999999;
		else
		{
			distToNextXIntersection = wolf->fXStepTable[castArc];
			while (1)
			{
				xGridIndex = (int)(xIntersection / wolf->TILE_SIZE);
				yGridIndex = (horizontalGrid / wolf->TILE_SIZE);

				if ((xGridIndex >= wolf->MAP_WIDTH) || (yGridIndex >= wolf->MAP_HEIGHT) || xGridIndex < 0 || yGridIndex < 0)
				{
					distToHorizontalGridBeingHit = 9999999;
					break;
				}
				else if ((wolf->fMap[yGridIndex][xGridIndex]) != 'O')
				{
					distToHorizontalGridBeingHit  = (xIntersection - wolf->fPlayerX) * wolf->fICosTable[castArc];
					break;
				}
				else
				{
					xIntersection += distToNextXIntersection;
					horizontalGrid += distToNextHorizontalGrid;
				}
			}
		}
		if (castArc < wolf->ANGLE90 || castArc > wolf->ANGLE270)
		{
			verticalGrid = wolf->TILE_SIZE + (wolf->fPlayerX / wolf->TILE_SIZE) * wolf->TILE_SIZE;
			distToNextVerticalGrid = wolf->TILE_SIZE;

			float ytemp = wolf->fTanTable[castArc] * (verticalGrid - wolf->fPlayerX);
			yIntersection = ytemp + wolf->fPlayerY;
		}
		else
		{
			verticalGrid = (wolf->fPlayerX / wolf->TILE_SIZE) * wolf->TILE_SIZE;
			distToNextVerticalGrid = -wolf->TILE_SIZE;

			float ytemp = wolf->fTanTable[castArc] * (verticalGrid - wolf->fPlayerX);
			yIntersection = ytemp + wolf->fPlayerY;
			verticalGrid--;
		}
		if (castArc == wolf->ANGLE90 || castArc == wolf->ANGLE270)
			distToVerticalGridBeingHit = 9999999;
		else
		{
			distToNextYIntersection = wolf->fYStepTable[castArc];
			while (1)
			{
				xGridIndex = (verticalGrid / wolf->TILE_SIZE);
				yGridIndex = (int)(yIntersection / wolf->TILE_SIZE);
				if ((xGridIndex >= wolf->MAP_WIDTH) ||
					(yGridIndex >= wolf->MAP_HEIGHT) ||
					xGridIndex < 0 || yGridIndex < 0)
				{
					distToVerticalGridBeingHit = 9999999;
					break;
				}
				else if ((wolf->fMap[yGridIndex][xGridIndex]) != 'O')
				{
				    if ((wolf->fMap[yGridIndex][xGridIndex]) == 'Q')
				        wolf->checkWall = 1;
					distToVerticalGridBeingHit =(yIntersection - wolf->fPlayerY) * wolf->fISinTable[castArc];
					break;
				}
				else
				{
					yIntersection += distToNextYIntersection;
					verticalGrid += distToNextVerticalGrid;
				}
			}
		}
		float scaleFactor;
		float dist;
		int topOfWall;
		int bottomOfWall;
		int xOffset;
		if (distToHorizontalGridBeingHit < distToVerticalGridBeingHit)
		{
            dist = distToHorizontalGridBeingHit / wolf->fFishTable[castColumn];
            float ratio = wolf->fPlayerDistanceToTheProjectionPlane / dist;
            float scale;
            bottomOfWall = (ratio * wolf->fPlayerHeight + wolf->fProjectionPlaneYCenter);
            if (wolf->checkWall)
                scale = (wolf->fPlayerDistanceToTheProjectionPlane * (wolf->WALL_HEIGHT * 2) / dist);
            else
                scale = (wolf->fPlayerDistanceToTheProjectionPlane * wolf->WALL_HEIGHT / dist);
            topOfWall = bottomOfWall - scale;
            xOffset = (int)xIntersection % wolf->TILE_SIZE;
        }
		else {
            dist = distToVerticalGridBeingHit / wolf->fFishTable[castColumn];
            float ratio = wolf->fPlayerDistanceToTheProjectionPlane / dist;
            float scale;
            bottomOfWall = (ratio * wolf->fPlayerHeight + wolf->fProjectionPlaneYCenter);
            if (wolf->checkWall) {
                printf("fef");
                scale = (wolf->fPlayerDistanceToTheProjectionPlane * (wolf->WALL_HEIGHT * 2) / dist);
            }
            else
                scale = (wolf->fPlayerDistanceToTheProjectionPlane * wolf->WALL_HEIGHT / dist);
            topOfWall = bottomOfWall - scale;
            xOffset = (int)yIntersection % wolf->TILE_SIZE;
        }
        wolf->checkWall = 0;
		drawWall(castColumn, topOfWall, bottomOfWall, bottomOfWall - topOfWall, xOffset, wolf);
		drawCeil(castColumn, topOfWall, bottomOfWall, bottomOfWall - topOfWall, xOffset, wolf);
		drawFloor(castColumn, topOfWall, bottomOfWall, bottomOfWall - topOfWall, xOffset, wolf);
		castArc++;
		wolf->checkWall = 0;
		if (castArc >= wolf->ANGLE360)
			castArc -= wolf->ANGLE360;
	}
}

void	drawWall(int x, int yStart, int yEnd, int height, int pixels, t_wolf *wolf)
{
    if (yEnd >= HEIGHT)
        yEnd = HEIGHT - 1;
    if (yStart < 0)
        yStart = 0;
    if (yStart >= HEIGHT)
        yStart = HEIGHT;
    if (yEnd < 0)
        yEnd = 0;
	while (yStart <= yEnd)
	{
	    wolf->buf[yStart][x] = (256 * 256 * 255) + (256 * 255) + 255;
	    yStart++;
	}
}

void	drawCeil(int x, int yStart, int yEnd, int height, int pixels, t_wolf *wolf)
{
	int y;

	y = 0;
	if (yStart < 0)
		yStart = 0;
	if (yStart >= HEIGHT)
	    yStart = HEIGHT - 1;
	while (y <= yStart)
	{
		wolf->buf[y][x] = (256 * 256 * 200) + (256 * 85) + 100;
		y++;
	}
}

void	drawFloor(int x, int yStart, int yEnd, int height, int pixels, t_wolf *wolf)
{
	if (yEnd >= HEIGHT)
		yEnd = HEIGHT - 1;
	if (yEnd < 0)
	    yEnd = 0;
	while (yEnd < HEIGHT - 1) {
		wolf->buf[yEnd][x] = (256 * 256 * 20) + (256 * 255) + 255;
		yEnd++;
	}
}

void	ft_game(t_wolf *wolf)
{
	SDL_SetRelativeMouseMode(1);
	SDL_WarpMouseInWindow(wolf->sdl.win, WIDTH / 2, HEIGHT / 2);
	Mix_PlayMusic(wolf->sdl.mus[0], -1);
	while (wolf->loop)
    {
	    ft_render(wolf);
	    render_texture(wolf);
		keys(wolf);
	}
	SDL_DestroyTexture(wolf->sdl.screen);
	TTF_Quit();
}
