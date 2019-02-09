#ifndef WOLF3D_WOLF3D_H
#define WOLF3D_WOLF3D_H
#define WIDTH 1024
#define HEIGHT 768
#define TILE_SIZE 256
#define WALL_HEIGHT 256
#define PROJECTIONPLANEWIDTH 1024
#define PROJECTIONPLANEHEIGHT 768



# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <SDL.h>
# include <math.h>
# include <fcntl.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_mixer.h>
# include <SDL_ttf.h>
# include <time.h>
# include "../lib/libft/libft.h"
# include "../include/get_next_line.h"

// We use FOV of 60 degrees.  So we use this FOV basis of the table, taking into account
// that we need to cast 320 rays (PROJECTIONPLANEWIDTH) within that 60 degree FOV.
#define ANGLE60 PROJECTIONPLANEWIDTH

// You must make sure these values are integers because we're using loopup tables.
#define ANGLE30 floor(ANGLE60/2)
#define ANGLE15 floor(ANGLE30/2)
#define ANGLE90 floor(ANGLE30*3)
#define ANGLE180 floor(ANGLE90*2)
#define ANGLE270 floor(ANGLE90*3)
#define ANGLE360 floor(ANGLE60*6)
#define ANGLE0 0
#define ANGLE5 floor(ANGLE30/6)
#define ANGLE10 floor(ANGLE5*2)
#define ANGLE45 floor(ANGLE15*3)

#define MAP_WIDTH 20
#define MAP_HEIGHT 20

typedef struct		s_raycast
{
    double			posX;
    double			posY;
    double			dir_x;
    double			dir_y;
    double			cameraX;
    double			ray_dir_x;
    double			ray_dir_y;
    double			plan_x;
    double			plan_y;
    double			delta_dist_x;
    double			delta_dist_y;
    double			side_dist_x;
    double			side_dist_y;
    double			dist_player;
    int				map_x;
    int				map_y;
    double				side;
    int				hit;
    int				step_x;
    int				step_y;
    int 			posMouseX;

    int             centerX;
    int             centerY;
    int             lenToCenter;
    double          agle;
    int             sizePrjPln;
    double          pov;
    double          fov;
    double          pov_t;
    double          fov_t;
    double          temp;
    int             updown;

}					t_raycast;

typedef struct		s_draw
{
    double			weight;
    double			floor_wall_y;
    double			floor_wall_x;
    int				draw_start;
    int				draw_end;
    int				tex_x;
    int				tex_y;
    int				floor_tex_x;
    int				floor_tex_y;
    double			perp_wall_dist;
    double			wall_x;
    double			current_floor_x;
    double			current_floor_y;
    double			current_dist;
    int				line_height;

}					t_draw;

typedef	struct		s_sdl
{
    SDL_Window		*win;
    SDL_Renderer	*ren;
    SDL_Texture		*screen;
    SDL_Surface		*up;
    SDL_Surface		*up_1;
    SDL_Surface		*floor;
    SDL_Surface		*wall[7];
    Mix_Music		*mus[3];
    TTF_Font        *font_ttf;
    SDL_Surface     *font_surface;
    SDL_Color             color;
    SDL_Rect		font_rect;
    SDL_Texture     *font_text;
    SDL_Event       event;
}					t_sdl;

typedef struct wolf_f
{
    t_raycast		raycast;
    t_draw 			draw;
    t_sdl			sdl;
    double			speed;
    Uint32			buf[HEIGHT][WIDTH];
    Uint32          buf_js[HEIGHT * WIDTH];
    int             counter_str_on_map;
    int				loop;
    char            *name;
    char            **full_map;
    int             **array;
    int             width_arr;
    int             height_arr;
    int             pos_X;
    int             pos_Y;
    int             count;
    int             code_error;
    int				x;
    int				y;
    int				d;
    int         fPlayerX;
    int         fPlayerY;
    int         fPlayerArc;
    int         fPlayerDistanceToTheProjectionPlane;
    int         fPlayerHeight;
    int         fPlayerSpeed;
    int             pause;
    char            *test;
    int             tw;
    int             th;
    int             ww;
    int             wh;
    int             t1;
    int             t2;
    int             i;
    int             m;
    int             q;
    int             w;
/*keys*/
    const Uint8 *keys;
    double plan;
    double dir;
    double koef;



    // trigonometric tables (the ones with "I" such as ISiTable are "Inverse" table)
    long double        *fSinTable;
    long double        *fISinTable;
    long double        *fCosTable;
    long double        *fICosTable;
    long double        *fTanTable;
    long double        *fITanTable;
    long double        *fFishTable;
    long double        *fXStepTable;
    long double        *fYStepTable;


    // player's attributes
//    int         fPlayerX;
//    int         fPlayerY;
//    int         fPlayerArc;
//    int         fPlayerDistanceToTheProjectionPlane;
//    int         fPlayerHeight;
//    int         fPlayerSpeed;

    // Half of the screen height
    int         fProjectionPlaneYCenter;

    // the following variables are used to keep the player coordinate in the overhead map
    int         fPlayerMapX;
    int         fPlayerMapY;
    int         fMinimapWidth;


    // movement flag
    int         fKeyUp;
    int         fKeyDown;
    int         fKeyLeft;
    int         fKeyRight;
    int         fKeyLookUp;
    int         fKeyLookDown;
    int         fKeyFlyUp;
    int         fKeyFlyDown;


    // 2 dimensional map
    char        *fMap;

    int animationFrameID;

    int fWallTextureCanvas;
    int fWallTexturePixels;
    int fBackgroundImageArc;

    int         baseLightValue;
    int         baseLightValueDelta;


    int         frameRate;

    int         arcAngle;
    int         bytesPerPixel;
    int         xIncrement;
    int         yIncrement;
    int         dy;
    int         dx;
    double      endY;
    double      endX;
    double      startY;
    double      startX;
    int         error;
    int         yError;
    int         targetIndex;
    int         length;
    int         height;
    double      x_1;
    double      y_1;
    double      xOffset;
    double      sourceIndex;
    double      lastSourceIndex;
    int         heightToDraw;
    int         cssColor;


} t_wolf;


int     main(int argc, char *argv[]);
int     ft_valid(t_wolf *wolf);
void    ft_error(int error, t_wolf *wolf);
void	ft_free_mas(char **ret);
int     ft_check_min_size_map(t_wolf *wolf);
int     ft_check_pos_player(t_wolf *wolf);
char**  ft_chrlen(char *str);
void    ft_write_mas_int(int n, t_wolf *wolf, char **str);
int     ft_check_size_map(t_wolf *wolf);
void    ft_init_varible(t_wolf *wolf);

SDL_Texture			*load_img(SDL_Renderer *ren, SDL_Surface *bmp, char *imag);
void				first_ar(t_wolf *wolf, char **str);
void				check_str(t_wolf *wolf, char **str);
void				make_arr(t_wolf *wolf, char **str);
int					**int_malloc(t_wolf *wolf);
void				check_rest(t_wolf *wolf);
int					len_int(char *str);
void				raycasting(t_wolf *wolf);
void				keys(t_wolf *wolf);
unsigned int		get_pixel_int(SDL_Surface *SDL_Surfaceace, int x, int y);
void				put_pixel32(SDL_Surface *SDL_Surfaceace, int x, int y, int pixel);
SDL_Surface			*load_image(char *path);
Mix_Music			*load_music(char *path);
void				ft_game(t_wolf *wolf);
void				fresh(t_wolf *wolf);

long double  *creatMasInt(int count);
void    loadTexture(t_wolf *wolf);
void    t_init(t_wolf *wolf);
void    ft_game_js(t_wolf *wolf);
void	raycast(t_wolf *wolf);



// void    ft_load_texture(t_wolf *wolf);
// double    arcToRad(t_wolf *wolf);
// void    drawLine(t_wolf *wolf, double startX, double startY, double endX, double endY, int red, int green, int blue, int alpha);
// void    drawOverheadMap(t_wolf *wolf);
// void    drawWallSliceRectangleTinted(t_wolf *wolf);
// void    drawRayOnOverheadMap(t_wolf *wolf, int x, int y);
// void    drawPlayerPOVOnOverheadMap(t_wolf *wolf, int x, int y);








#endif //WOLF3D_WOLF3D_H