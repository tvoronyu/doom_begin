#include "wolf3d.h"

void    ft_mouse_right(t_wolf *wolf)
{
    if (wolf->sdl.event.motion.xrel > 0 && wolf->sdl.event.motion.xrel < 1000)
    {
		wolf->dir = wolf->raycast.dir_x;
        wolf->raycast.dir_x = wolf->raycast.dir_x * cos(-(fabs(wolf->sdl.event.motion.xrel / 700.0))) -
                              wolf->raycast.dir_y * sin(-(fabs(wolf->sdl.event.motion.xrel / 700.0)));
        wolf->raycast.dir_y = wolf->dir * sin(-(fabs(wolf->sdl.event.motion.xrel / 700.0))) +
                              wolf->raycast.dir_y * cos(-(fabs(wolf->sdl.event.motion.xrel / 700.0)));
		wolf->plan = wolf->raycast.plan_x;
        wolf->raycast.plan_x = wolf->raycast.plan_x * cos(-(fabs(wolf->sdl.event.motion.xrel / 700.0))) -
                               wolf->raycast.plan_y * sin(-(fabs(wolf->sdl.event.motion.xrel / 700.0)));
        wolf->raycast.plan_y = wolf->plan * sin(-(fabs(wolf->sdl.event.motion.xrel / 700.0))) +
                               wolf->raycast.plan_y * cos(-(fabs(wolf->sdl.event.motion.xrel / 700.0)));
    }
}

void    ft_pause_2(t_wolf *wolf)
{
    if (wolf->sdl.event.type == SDL_QUIT)
        wolf->for_exit = 2;
    if (wolf->sdl.event.type == SDL_KEYDOWN && wolf->sdl.event.key.keysym.sym == SDLK_ESCAPE)
        wolf->for_exit = 1;
    if (wolf->sdl.event.motion.xrel > -1000 && wolf->sdl.event.motion.xrel < 0)
    {
		wolf->dir = wolf->raycast.dir_x;
        wolf->raycast.dir_x = wolf->raycast.dir_x * cos(fabs(wolf->sdl.event.motion.xrel / 700.0)) -
                              wolf->raycast.dir_y * sin(fabs(wolf->sdl.event.motion.xrel / 700.0));
        wolf->raycast.dir_y = wolf->dir * sin(fabs(wolf->sdl.event.motion.xrel / 700.0)) +
                              wolf->raycast.dir_y * cos(fabs(wolf->sdl.event.motion.xrel / 700.0));
		wolf->plan = wolf->raycast.plan_x;
        wolf->raycast.plan_x = wolf->raycast.plan_x * cos(fabs(wolf->sdl.event.motion.xrel / 700.0)) -
                               wolf->raycast.plan_y * sin(fabs(wolf->sdl.event.motion.xrel / 700.0));
        wolf->raycast.plan_y = wolf->plan * sin(fabs(wolf->sdl.event.motion.xrel / 700.0)) +
                               wolf->raycast.plan_y * cos(fabs(wolf->sdl.event.motion.xrel / 700.0));
    }
    ft_mouse_right(wolf);
}

void    ft_keys_1(t_wolf *wolf)
{
    if (wolf->keys[SDL_SCANCODE_LSHIFT] == 1)
        wolf->speed = 0.15;
    else {
        if (wolf->keys[SDL_SCANCODE_LALT] == 1)
            wolf->speed = 0.04;
        else
            wolf->speed = 0.075;
    }
    if (wolf->keys[SDL_SCANCODE_RIGHT]) {
        wolf->dir = wolf->raycast.dir_x;
        wolf->raycast.dir_x = wolf->raycast.dir_x *
                              cos(-wolf->koef) - wolf->raycast.dir_y * sin(-wolf->koef);
        wolf->raycast.dir_y = wolf->dir * sin(-wolf->koef)
                              + wolf->raycast.dir_y * cos(-wolf->koef);
        wolf->plan = wolf->raycast.plan_x;
        wolf->raycast.plan_x = wolf->raycast.plan_x *
                               cos(-wolf->koef) - wolf->raycast.plan_y * sin(-wolf->koef);
        wolf->raycast.plan_y = wolf->plan * sin(-wolf->koef) +
                               wolf->raycast.plan_y * cos(-wolf->koef);
    }
}

void    ft_keys_2(t_wolf *wolf)
{
    if (wolf->keys[SDL_SCANCODE_LEFT]) {
        wolf->dir = wolf->raycast.dir_x;
        wolf->raycast.dir_x = wolf->raycast.dir_x * cos(wolf->koef) -
                              wolf->raycast.dir_y * sin(wolf->koef);
        wolf->raycast.dir_y = wolf->dir * sin(wolf->koef) +
                              wolf->raycast.dir_y * cos(wolf->koef);
        wolf->plan = wolf->raycast.plan_x;
        wolf->raycast.plan_x = wolf->raycast.plan_x * cos(wolf->koef) -
                               wolf->raycast.plan_y * sin(wolf->koef);
        wolf->raycast.plan_y = wolf->plan * sin(wolf->koef) +
                               wolf->raycast.plan_y * cos(wolf->koef);
    }
    if (wolf->keys[SDL_SCANCODE_UP] || wolf->keys[SDL_SCANCODE_W]) {
        if (wolf->array[(int)(wolf->raycast.posY)][(int)(wolf->raycast.posX
                                                         + wolf->raycast.dir_x * wolf->speed)] == 0)
            wolf->raycast.posX += wolf->raycast.dir_x * wolf->speed;
        if (wolf->array[(int)(wolf->raycast.posY + wolf->raycast.dir_y
                                                   * wolf->speed)][(int)(wolf->raycast.posX)] == 0)
            wolf->raycast.posY += wolf->raycast.dir_y * wolf->speed;
    }
}

void    ft_keys_3(t_wolf *wolf)
{
    if (wolf->keys[SDL_SCANCODE_DOWN] || wolf->keys[SDL_SCANCODE_S])
    {
        if (wolf->array[(int)(wolf->raycast.posY)]
        [(int)(wolf->raycast.posX - wolf->raycast.dir_x * wolf->speed)] == 0)
        wolf->raycast.posX -= wolf->raycast.dir_x * wolf->speed;
        if (wolf->array
        [(int)(wolf->raycast.posY - wolf->raycast.dir_y * wolf->speed)]
        [(int)(wolf->raycast.posX)] == 0)
            wolf->raycast.posY -= wolf->raycast.dir_y * wolf->speed;
    }
    if (wolf->keys[SDL_SCANCODE_D])
    {
        if (wolf->array[(int)(wolf->raycast.posY +
        wolf->raycast.plan_y * wolf->speed)]
            [(int)(wolf->raycast.posX)] == 0)
            wolf->raycast.posY += wolf->raycast.plan_y *
                    wolf->speed;
        if (wolf->array[(int)(wolf->raycast.posY)]
            [(int)(wolf->raycast.posX + wolf->raycast.plan_x *
            wolf->speed)] == 0)
            wolf->raycast.posX += wolf->raycast.plan_x *
                    wolf->speed;
    }
}


void    ft_keys_4(t_wolf *wolf)
{
    if (wolf->keys[SDL_SCANCODE_A])
    {
        if (wolf->array[(int)(wolf->raycast.posY -
        wolf->raycast.plan_y * wolf->speed)]
            [(int)(wolf->raycast.posX)] == 0)
            wolf->raycast.posY -= wolf->raycast.plan_y * wolf->speed;
        if (wolf->array[(int)(wolf->raycast.posY)]
            [(int)(wolf->raycast.posX -
            wolf->raycast.plan_x * wolf->speed)] == 0)
            wolf->raycast.posX -= wolf->raycast.plan_x
                    * wolf->speed;
    }
}
void    ft_pause_3(t_wolf *wolf)
{
    ft_keys_1(wolf);
    ft_keys_2(wolf);
    ft_keys_3(wolf);
    ft_keys_4(wolf);
}

void	keys(t_wolf *wolf)
{
	wolf->koef = 0.05;
	wolf->dir = 0.0;
	wolf->plan = 0.0;
	wolf->keys = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&wolf->sdl.event))
		if (wolf->pause)
		    ft_pause_2(wolf);
	if (wolf->pause)
	    ft_pause_3(wolf);
    if (wolf->keys[SDL_SCANCODE_P])
	{
    	if (wolf->pause) {
			SDL_Delay(100);
			wolf->pause = 0;
			SDL_SetRelativeMouseMode(0);
		}
    	else {
			SDL_Delay(100);
			wolf->pause = 1;
			SDL_SetRelativeMouseMode(1);
		}
	}
}

void	render(t_wolf *wolf)
{
	int n;
    unsigned int color;
	wolf->raycast.cameraX = (double)((wolf->x * 2) / (double)(WIDTH) - 1);
	wolf->raycast.ray_dir_x = wolf->raycast.dir_x + wolf->raycast.plan_x * wolf->raycast.cameraX;
	wolf->raycast.ray_dir_y = wolf->raycast.dir_y + wolf->raycast.plan_y * wolf->raycast.cameraX;
	if ((int)wolf->raycast.posX > wolf->width_arr)
        wolf->raycast.posX = wolf->width_arr;
	if ((int)wolf->raycast.posY > wolf->height_arr)
        wolf->raycast.posY = wolf->height_arr;
	wolf->raycast.map_x = (int)wolf->raycast.posX;
	wolf->raycast.map_y = (int)wolf->raycast.posY;
	wolf->raycast.delta_dist_x = fabs(1 / wolf->raycast.ray_dir_x);
	wolf->raycast.delta_dist_y = fabs(1 / wolf->raycast.ray_dir_y);
	wolf->raycast.hit = 0;

	if (wolf->raycast.ray_dir_x < 0)
	{
		wolf->raycast.step_x = -1;
		wolf->raycast.side_dist_x = (wolf->raycast.posX - wolf->raycast.map_x) * wolf->raycast.delta_dist_x;
	}
	else
	{
		wolf->raycast.step_x = 1;
		wolf->raycast.side_dist_x = (wolf->raycast.map_x + 1.0 - wolf->raycast.posX) * wolf->raycast.delta_dist_x;
	}
	if (wolf->raycast.ray_dir_y < 0)
	{
		wolf->raycast.step_y = -1;
		wolf->raycast.side_dist_y = (wolf->raycast.posY - wolf->raycast.map_y) * wolf->raycast.delta_dist_y;
	}
	else
	{
		wolf->raycast.step_y = 1;
		wolf->raycast.side_dist_y = (wolf->raycast.map_y + 1.0 - wolf->raycast.posY) * wolf->raycast.delta_dist_y;
	}
	while (wolf->raycast.hit == 0)
	{
		if (wolf->raycast.side_dist_x < wolf->raycast.side_dist_y)
		{
			wolf->raycast.side_dist_x += wolf->raycast.delta_dist_x;
			wolf->raycast.map_x += wolf->raycast.step_x;
			wolf->raycast.side = 0;
		}
		else
		{
			wolf->raycast.side_dist_y += wolf->raycast.delta_dist_y;
			wolf->raycast.map_y += wolf->raycast.step_y;
			wolf->raycast.side = 1;
		}
		if (wolf->array[wolf->raycast.map_y][wolf->raycast.map_x] > 0)
			wolf->raycast.hit = 1;
	}
	if (wolf->raycast.side == 0)
		wolf->draw.perp_wall_dist = (wolf->raycast.map_x - wolf->raycast.posX + (1 - wolf->raycast.step_x) / 2) / wolf->raycast.ray_dir_x;
	else
		wolf->draw.perp_wall_dist = (wolf->raycast.map_y - wolf->raycast.posY + (1 - wolf->raycast.step_y) / 2) / wolf->raycast.ray_dir_y;
	if (wolf->draw.perp_wall_dist < 0.05)
        wolf->draw.perp_wall_dist = 0.05;
	wolf->draw.line_height = (int)(HEIGHT / wolf->draw.perp_wall_dist);
	wolf->draw.draw_start = (-wolf->draw.line_height / 2 + HEIGHT / 2);
	if (wolf->draw.draw_start < 0)
		wolf->draw.draw_start = 0;
	wolf->draw.draw_end = (wolf->draw.line_height / 2 + HEIGHT / 2);
	if (wolf->draw.draw_end >= HEIGHT)
		wolf->draw.draw_end = HEIGHT - 1;
	n = wolf->array[wolf->raycast.map_y][wolf->raycast.map_x] - 1;
    if (wolf->raycast.side == 0)
    {
        if (wolf->raycast.ray_dir_x > 0)
            n = 0;
        else
            n = 1;
    }
    else
    {
        if (wolf->raycast.ray_dir_y > 0)
            n = 2;
        else
            n = 3;
    }
	if (wolf->raycast.side == 0)
		wolf->draw.wall_x = wolf->raycast.posY + wolf->draw.perp_wall_dist * wolf->raycast.ray_dir_y;
	else
		wolf->draw.wall_x = wolf->raycast.posX + wolf->draw.perp_wall_dist * wolf->raycast.ray_dir_x;
	wolf->draw.wall_x -= floor(wolf->draw.wall_x);
	wolf->draw.tex_x = (int)(wolf->draw.wall_x * 256.0);
	if (wolf->raycast.side == 0 && wolf->raycast.ray_dir_x > 0)
		wolf->draw.tex_x = 256.0 - wolf->draw.tex_x - 1;
	if (wolf->raycast.side == 1 & wolf->raycast.ray_dir_y < 0)
		wolf->draw.tex_x = 256.0 - wolf->draw.tex_x - 1;
	wolf->y = wolf->draw.draw_start;
	while (++wolf->y < wolf->draw.draw_end)
	{
		wolf->d = wolf->y * 256 - HEIGHT * 128 + wolf->draw.line_height * 128;
		wolf->draw.tex_y = ((wolf->d * 256.0) / wolf->draw.line_height / 256);
		if ((color = get_pixel_int(wolf->sdl.wall[n], wolf->draw.tex_x, wolf->draw.tex_y)) != 0)
            wolf->buf[wolf->y][wolf->x] = color;
	}
	if (wolf->raycast.side == 0 && wolf->raycast.ray_dir_x > 0)
	{
		wolf->draw.floor_wall_x = wolf->raycast.map_x;
		wolf->draw.floor_wall_y = wolf->raycast.map_y + wolf->draw.wall_x;
	}
	else if (wolf->raycast.side == 0 && wolf->raycast.ray_dir_x < 0)
	{
		wolf->draw.floor_wall_x = wolf->raycast.map_x + 1.0;
		wolf->draw.floor_wall_y = wolf->raycast.map_y + wolf->draw.wall_x;
	}
	else if (wolf->raycast.side == 1 && wolf->raycast.ray_dir_y > 0)
	{
		wolf->draw.floor_wall_x = wolf->raycast.map_x + wolf->draw.wall_x;
		wolf->draw.floor_wall_y = wolf->raycast.map_y;
	}
	else
	{
		wolf->draw.floor_wall_x = wolf->raycast.map_x + wolf->draw.wall_x;
		wolf->draw.floor_wall_y = wolf->raycast.map_y + 1.0;
	}
	wolf->raycast.dist_player = 0.0;
	if (wolf->draw.draw_end < 0)
		wolf->draw.draw_end = HEIGHT;
	wolf->y = wolf->draw.draw_end - 1;
	while (++wolf->y < HEIGHT)
	{
		wolf->draw.current_dist = HEIGHT / (2.0 * wolf->y - HEIGHT);
		wolf->draw.weight = (wolf->draw.current_dist - wolf->raycast.dist_player) / (wolf->draw.perp_wall_dist - wolf->raycast.dist_player);
		wolf->draw.current_floor_x = wolf->draw.weight * wolf->draw.floor_wall_x + (1.0 - wolf->draw.weight) * wolf->raycast.posX;
		wolf->draw.current_floor_y = wolf->draw.weight * wolf->draw.floor_wall_y + (1.0 - wolf->draw.weight) * wolf->raycast.posY;
		wolf->draw.floor_tex_x = (int)(wolf->draw.current_floor_x * 256) % 256;
		wolf->draw.floor_tex_y = (int)(wolf->draw.current_floor_y * 256) % 256;
		color = get_pixel_int(wolf->sdl.floor, wolf->draw.floor_tex_x, wolf->draw.floor_tex_y);
		wolf->buf[wolf->y][wolf->x] = color;
		color = get_pixel_int(wolf->sdl.up, wolf->draw.floor_tex_x, wolf->draw.floor_tex_y);
		wolf->buf[WIDTH / 4 * 3 - wolf->y][wolf->x] = color;
	}
}

void    ft_fps(t_wolf *wolf)
{
    static int		my_time;
    static int		fps;
    static int		my_fps;
    char            *s;

    if (time(NULL) != my_time)
    {
        my_fps = fps;
        fps = 0;
        my_time = (int)time(NULL);
    }
    else
        fps++;
    s = ft_itoa(my_fps);
    wolf->test = ft_strjoin("FPS ", s);
    free(s);
}

void    ft_init_ttf(t_wolf *wolf)
{
    wolf->sdl.font_ttf = TTF_OpenFont("Roboto-Bold.ttf", 20);
    SDL_GetWindowSize(wolf->sdl.win, &wolf->ww, &wolf->wh);
    SDL_Color color = {255,255,255,255};
    wolf->sdl.font_surface = TTF_RenderText_Solid(wolf->sdl.font_ttf, wolf->test, color);
    wolf->sdl.font_text = SDL_CreateTextureFromSurface(wolf->sdl.ren, wolf->sdl.font_surface);
    SDL_QueryTexture(wolf->sdl.font_text, NULL, NULL, &wolf->tw, &wolf->th);
    wolf->sdl.font_rect.x = wolf->ww - 100;
    wolf->sdl.font_rect.y = wolf->wh - 40;
    wolf->sdl.font_rect.w = wolf->tw;
    wolf->sdl.font_rect.h = wolf->th;
}

void    render_texture(t_wolf *wolf)
{
    SDL_UpdateTexture(wolf->sdl.screen, NULL, wolf->buf, WIDTH << 2);
    SDL_RenderCopy(wolf->sdl.ren, wolf->sdl.screen, NULL, NULL);
    SDL_RenderCopy(wolf->sdl.ren, wolf->sdl.font_text, NULL, &wolf->sdl.font_rect);
    SDL_RenderPresent(wolf->sdl.ren);
    SDL_DestroyTexture(wolf->sdl.font_text);
    SDL_FreeSurface(wolf->sdl.font_surface);
    TTF_CloseFont(wolf->sdl.font_ttf);
    free(wolf->test);
}

void    ft_draw_player(t_wolf *wolf)
{
    if ((int)((wolf->q / 6) - 1) >= 0) {
        if ((int)((wolf->w / 6) - 1) >= 0) {
            if (wolf->array[(int)((wolf->q / 6) - 1)][(int) ((wolf->w / 6) - 1)] != 0) {
                while (wolf->q < wolf->i + 6) {
                    wolf->w = wolf->m;
                    while (wolf->w < wolf->m + 6) {
                        wolf->buf[(int)((wolf->i / 6) - 1) * 6 + abs(wolf->i - wolf->q)][
                                (int)((wolf->m / 6) - 1) * 6 +
                                abs(wolf->m - wolf->w)] =
                                (256 * 256 * 200) + (256 * 200) + 50;
                        wolf->w++;
                    }
                    wolf->q++;
                }
            }
        }
    }
}

void    ft_draw_wall(t_wolf *wolf)
{
    while (wolf->i++ < wolf->height_arr * 6) {
        wolf->m = -1;
        while (wolf->m++ < wolf->width_arr * 6) {
            wolf->buf[wolf->i][wolf->m] = (256 * 256 * 0) + (256 * 0) + 0;
            wolf->q = wolf->i;
            wolf->w = wolf->m;
            while (wolf->q < wolf->i + 6) {
                wolf->w = wolf->m;
                while (wolf->w < wolf->m + 6) {
                    wolf->buf[(int) wolf->raycast.posY * 6 + abs(wolf->i - wolf->q)]
                    [(int)wolf->raycast.posX * 6 + abs(wolf->m - wolf->w)]
                            = (256 * 256 * 255) + (256 * 0) + 0;
                    wolf->w++;
                }
                wolf->q++;
            }
            wolf->q = wolf->i;
            wolf->w = wolf->m;
            ft_draw_player(wolf);
        }
    }
}

void    ft_raycast(t_wolf *wolf)
{
    wolf->x = -1;
    if (wolf->pause)
    {
        SDL_SetRelativeMouseMode(0);
        SDL_SetRelativeMouseMode(1);
        while (++wolf->x < WIDTH)
            render(wolf);
        if (wolf->t1 < wolf->ww / 4 && wolf->t2 < wolf->wh / 4)
        {
            wolf->i = -1;
            ft_draw_wall(wolf);
        }
    }
}

void	ft_game(t_wolf *wolf)
{
    SDL_SetRelativeMouseMode(1);
    SDL_WarpMouseInWindow(wolf->sdl.win, WIDTH / 2, HEIGHT / 2);
    Mix_PlayMusic(wolf->sdl.mus[0], -1);
	if (wolf->for_exit == 0)
		while (wolf->for_exit == 0)
		{
            ft_fps(wolf);
            ft_init_ttf(wolf);
			render_texture(wolf);
			ft_raycast(wolf);
			keys(wolf);
		}
    SDL_DestroyTexture(wolf->sdl.screen);
    TTF_Quit();
}