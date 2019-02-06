#include "wolf3d.h"

SDL_Surface		*load_image(char *path)
{
	SDL_Surface	*texture;

	texture = IMG_Load(path);
	if (texture == NULL)
		ft_error(4, NULL);
	return (texture);
}

unsigned int	get_pixel_int(SDL_Surface *surface, int x, int y)
{
	unsigned int	*pixels;

	if (surface)
	{
        if ((pixels = (unsigned int *) surface->pixels))
        {
            if ((y * surface->w) + x < WIDTH * HEIGHT)
                return (pixels[(y * surface->w) + x]);
        }
    }
	return (0);
}

Mix_Music		*load_music(char *path)
{
	Mix_Music *music;

	if (!(music = Mix_LoadMUS(path)))
		ft_error(4, NULL);
	return (music);
}