#include "wolf3d.h"

//void  ft_init_all(t_wolf *wolf)
//{
//    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
//        ft_error(3, wolf);
//    if (!(wolf->sdl.win = SDL_CreateWindow("Wolf3D",
//            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH,
//            HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN)))
//        ft_error(3, wolf);
//    if (!(wolf->sdl.ren = SDL_CreateRenderer(wolf->sdl.win, -1,
//            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
//        ft_error(3, wolf);
//    if (!(wolf->sdl.screen = SDL_CreateTexture(wolf->sdl.ren,
//            SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, WIDTH, HEIGHT)))
//        ft_error(3, wolf);
//    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
//        ft_error(3, wolf);
//    if (TTF_Init() < 0)
//        ft_error(3, wolf);
//    ft_init_intible(wolf);
//}
//
//void    ft_init_intible(t_wolf *wolf)
//{
//    wolf->sdl.up = load_image("texture/ceil.jpg");
//    wolf->sdl.floor = load_image("texture/floor.jpg");
//    wolf->sdl.wall[0] = load_image("texture/11.jpg");
//    wolf->sdl.wall[1] = load_image("texture/16.jpg");
//    wolf->sdl.wall[2] = load_image("texture/13.jpg");
//    wolf->sdl.wall[3] = load_image("texture/14.jpg");
//    wolf->sdl.mus[0] = load_music("texture/sound.mp3");
//    wolf->raycast.dir_x = -1.0;
//    wolf->raycast.dir_y = 0.0;
//    wolf->raycast.plan_x = 0.0;
//    wolf->raycast.plan_y = 0.66;
//    wolf->speed = 0.1;
//    wolf->for_exit = 0;
//    wolf->pause = 1;
//    wolf->t1 = wolf->width_arr;
//    wolf->t2 = wolf->height_arr;
//}
//
//int    ft_count_str_on_map(t_wolf *wolf)
//{
//    int n;
//    int fd;
//    char *line;
//
//    n = 0;
//    fd = open(wolf->name, O_RDWR);
//    if (fd > 2)
//    {
//        while (get_next_line(fd, &line))
//        {
//            n++;
//            free(line);
//        }
//        close(fd);
//    }
//    return (n);
//}
//
//void  ft_read_map_on_file(t_wolf *wolf)
//{
//    int fd;
//    char *line;
//    char **str;
//
//    line = NULL;
//    if ((wolf->counter_str_on_map = ft_count_str_on_map(wolf)))
//    {
//        fd = open(wolf->name, O_RDWR);
//        str = (char**)malloc(sizeof(char*) * wolf->counter_str_on_map + 1);
//        str[wolf->counter_str_on_map] = NULL;
//        wolf->counter_str_on_map = 0;
//        while (get_next_line(fd, &line))
//        {
//            str[wolf->counter_str_on_map++] = ft_strjoin(line, "\n");
//            free(line);
//        }
//    }
//    wolf->full_map = str;
//    close(fd);
//}
//
//void ft_read(t_wolf *wolf)
//{
//    int fd;
//
//    fd = open(wolf->name, O_DIRECTORY);
//    if (fd >= 0)
//        ft_error(1, wolf);
//    ft_read_map_on_file(wolf);
//
//}


void    ft_load_texture(new_wolf *wolf)
{

}

double    arcToRad(new_wolf *wolf)
{
    return ((wolf->arcAngle * 3.14) / ANGLE180);
}


void    drawLine(new_wolf *wolf, double startX, double startY, double endX, double endY, int red, int green, int blue, int alpha)
{
    // console.log("8");
    wolf->bytesPerPixel = 4;
    // changes in x and y
//    wolf->xIncrement, wolf->yIncrement;


    // calculate Ydistance
    wolf->dy = endY - startY;

    // if moving negative dir (up)
    // note that we can simplify this function if we can guarantee that
    // the line will always move in one direction only
    if (wolf->dy < 0)
    {
        // get abs
        wolf->dy = -wolf->dy;
        // negative movement
//        wolf->yIncrement= -wolf->offscreenCanvasPixels.width*bytesPerPixel;/ТУТ ПРАЦЮЄМО З ПІКСЕЛЯМИ

    }
    //тут треба переписати на пікселі з SDL
//    else
//        yIncrement=this.offscreenCanvasPixels.width*bytesPerPixel;

    // calc x distance
    wolf->dx = endX - startX;

    // if negative dir (left)
    // note that we can simplify this function if we can guarantee that
    // the line will always move in one direction only
    if (wolf->dx < 0)
    {
        wolf->dx = -wolf->dx;
        wolf->xIncrement = -wolf->bytesPerPixel;
    }
    else
        wolf->xIncrement = wolf->bytesPerPixel;

    // deflation
    wolf->error = 0;
    //тут переписати на свої пікселі;
//    wolf->targetIndex = (bytesPerPixel*this.offscreenCanvasPixels.width)*startY+(bytesPerPixel*startX);

    // if movement in x direction is larger than in y
    // ie: width > height
    // we draw each row one by one
    if (wolf->dx > wolf->dy)
    {
        // length = width +1
        wolf->length = wolf->dx;

        for (int i=0;i < wolf->length; i++)
        {
            if (wolf->targetIndex < 0)
                break;

            //Знову переписати на свої пікселі;
//            this.offscreenCanvasPixels.data[targetIndex]=red;
//            this.offscreenCanvasPixels.data[targetIndex+1]=green;
//            this.offscreenCanvasPixels.data[targetIndex+2]=blue;
//            this.offscreenCanvasPixels.data[targetIndex+3]=alpha;

            // either move left/right
            wolf->targetIndex += wolf->xIncrement;
            // cumulate error term
            wolf->error += wolf->dy;

            // is it time to move y direction (chage row)
            if (wolf->error >= wolf->dx)
            {
                wolf->error -= wolf->dx;
                // move to next row
                wolf->targetIndex += wolf->yIncrement;
            }
        }
    }
    // if movement in y direction is larger than in x
    // ie: height > width
    // we draw each column one by one
    // note that a diagonal line will go here because xdiff = ydiff
    else //(YDiff>=XDiff)
    {
        wolf->length = wolf->dy;

        for (int i = 0; i < wolf->length; i++)
        {
        if (wolf->targetIndex < 0)
            break;

//переписати на свої пікселіЖ
//        this.offscreenCanvasPixels.data[targetIndex]=red;
//        this.offscreenCanvasPixels.data[targetIndex+1]=green;
//        this.offscreenCanvasPixels.data[targetIndex+2]=blue;
//        this.offscreenCanvasPixels.data[targetIndex+3]=alpha;

            wolf->targetIndex += wolf->yIncrement;
            wolf->error += wolf->dx;

            if (wolf->error >= wolf->dy)
            {
                wolf->error -= wolf->dy;
                wolf->targetIndex += wolf->xIncrement;
            }
        }
    }
}


void    drawWallSliceRectangleTinted(new_wolf *wolf)
{
    // console.log("9");
    // wait until the texture loads

    //тут поставити свої пікслеі;
//    if (wolf->fWallTextureBuffer == NULL)
//        return;

    wolf->dy = wolf->height;
    wolf->x = floor(wolf->x);
    wolf->y = floor(wolf->y);
    wolf->xOffset = floor(wolf->xOffset);
    wolf->bytesPerPixel = 4;

    wolf->sourceIndex = (wolf->bytesPerPixel * wolf->xOffset);
//    тут поставити свої пікселі
//    wolf->lastSourceIndex = wolf->sourceIndex + (wolf->fWallTextureBuffer.width*this.fWallTextureBuffer.height*bytesPerPixel);

    //int targetCanvasPixels=this.canvasContext.createImageData(0, 0, width, height);
//    тут поставити свої пікселі
//    int targetIndex=(this.offscreenCanvasPixels.width*bytesPerPixel)*y+(bytesPerPixel*x);


    wolf->heightToDraw = wolf->height;
    // clip bottom
    //тут підключити свої пікселі;
//    if (wolf->y+heightToDraw > wolf->offscreenCanvasPixels.height)
//        wolf->heightToDraw = this.offscreenCanvasPixels.height-y;


   wolf->yError = 0;

    // we need to check this, otherwise, program might crash when trying
    // to fetch the shade if this condition is true (possible if height is 0)
    if (wolf->heightToDraw<0)
        return;

    // we're going to draw the first row, then move down and draw the next row
    // and so on we can use the original x destination to find out
    // the x position of the next row
    // Remeber that the source bitmap is rotated, so the width is actually the
    // height
    while (1)
    {
        // if error < actualHeight, this will cause row to be skipped until
        // this addition sums to scaledHeight
        // if error > actualHeight, this ill cause row to be drawn repeatedly until
        // this addition becomes smaller than actualHeight
        // 1) Think the image height as 100, if percent is >= 100, we'll need to
        // copy the same pixel over and over while decrementing the percentage.
        // 2) Similarly, if percent is <100, we skip a pixel while incrementing
        // and do 1) when the percentage we're adding has reached >=100
        wolf->yError += wolf->height;

        // dereference for faster access (especially useful when the same bit
        // will be copied more than once)

        // Cheap shading trick by using brightnessLevel (which doesn't really have to correspond to "brightness")
        // to alter colors.  You can use logarithmic falloff or linear falloff to produce some interesting effect
//тут поставити свої пікселі;
        //        wolf->red = floor(this.fWallTexturePixels[sourceIndex]*brightnessLevel);
//        wolf->green = floor(this.fWallTexturePixels[sourceIndex+1]*brightnessLevel);
//        wolf->blue = floor(this.fWallTexturePixels[sourceIndex+2]*brightnessLevel);
//        wolf-> = floor(this.fWallTexturePixels[sourceIndex+3]);

        // while there's a row to draw & not end of drawing area
        //тут поставити свої пікселі;
//        while (wolf->yError >= this.fWallTextureBuffer.width)
//        {
//            yError-=this.fWallTextureBuffer.width;
//            this.offscreenCanvasPixels.data[targetIndex]=red;
//            this.offscreenCanvasPixels.data[targetIndex+1]=green;
//            this.offscreenCanvasPixels.data[targetIndex+2]=blue;
//            this.offscreenCanvasPixels.data[targetIndex+3]=alpha;
//            targetIndex+=(bytesPerPixel*this.offscreenCanvasPixels.width);
//            // clip bottom (just return if we reach bottom)
//            heightToDraw--;
//            if (heightToDraw<1)
//                return;
//        }

        //тут поставити свої пікселі;
//        wolf->sourceIndex += (wolf->bytesPerPixel * this.fWallTextureBuffer.width);

        if (wolf->sourceIndex > wolf->lastSourceIndex)
            wolf->sourceIndex = wolf->lastSourceIndex;
    }

}

//*******************************************************************//
//* Draw map on the right side
//*******************************************************************//
void    drawOverheadMap(new_wolf *wolf)
{
    // console.log("13");
    wolf->fMinimapWidth = 5;
    for (int r = 0; r < MAP_HEIGHT; r++)
    {
        for (int c = 0; c < MAP_WIDTH; c++)
        {
//            wolf->cssColor = "white";//тут косяк;
            if (wolf->fMap[r * MAP_WIDTH + c] != 'O')
            {
                drawFillRectangle(wolf, PROJECTIONPLANEWIDTH + (c * wolf->fMinimapWidth),
                                       (r * wolf->fMinimapWidth), wolf->fMinimapWidth, wolf->fMinimapWidth, 0, 0,0, 255);
            }
            else
            {
                drawFillRectangle(wolf, PROJECTIONPLANEWIDTH + (c * wolf->fMinimapWidth),
                                       (r * wolf->fMinimapWidth), wolf->fMinimapWidth, wolf->fMinimapWidth, 255, 255,255, 255);
            }
        }
    }
    // Draw player position on the overhead map
    wolf->fPlayerMapX = PROJECTIONPLANEWIDTH + ((wolf->fPlayerX / TILE_SIZE) * wolf->fMinimapWidth);
    wolf->fPlayerMapY = ((wolf->fPlayerY / TILE_SIZE) * wolf->fMinimapWidth);

}




void    drawRayOnOverheadMap(new_wolf *wolf, int x, int y)
{
    //console.log("drawRayOnOverheadMap x="+y+" y="+y);
    // draw line from the player position to the position where the ray
    // intersect with wall

    //тут косяк. забагато аргументів, треба все перенести в структуру;
    drawLine(wolf, floor(wolf->fPlayerMapX), floor(wolf->fPlayerMapY),
            floor(PROJECTIONPLANEWIDTH + ((x * wolf->fMinimapWidth) / TILE_SIZE)),floor(((y * wolf->fMinimapWidth) / TILE_SIZE)), 0,255,0,255);
}


//*******************************************************************//
//* Draw player POV on the overhead map (for illustartion purpose)
//* This is not part of the ray-casting process
//*******************************************************************//
void    drawPlayerPOVOnOverheadMap(new_wolf *wolf, int x, int y)
{
    // draw a red line indication the player's direction
//    this.drawLine(
//            Math.floor(this.fPlayerMapX),
//    Math.floor(this.fPlayerMapY),
//    Math.floor(this.fPlayerMapX+this.fCosTable[this.fPlayerArc]*10),
//    Math.floor(this.fPlayerMapY+this.fSinTable[this.fPlayerArc]*10),
//    255,0,0,255);

}


void    raycast(new_wolf *wolf)
{
    int verticalGrid;        // horizotal or vertical coordinate of intersection
    int horizontalGrid;      // theoritically, this will be multiple of TILE_SIZE
    // , but some trick did here might cause
    // the values off by 1
    int distToNextVerticalGrid; // how far to the next bound (this is multiple of
    int distToNextHorizontalGrid; // tile size)
    double xIntersection;  // x and y intersections
    double yIntersection;
    int distToNextXIntersection;
    int distToNextYIntersection;

    int xGridIndex;        // the current cell that the ray is in
    int yGridIndex;

    int distToVerticalGridBeingHit;      // the distance of the x and y ray intersections from
    int distToHorizontalGridBeingHit;      // the viewpoint

    int castArc, castColumn;
    int DEBUG = 0;

    double xtemp;

    castArc = wolf->fPlayerArc;
    // field of view is 60 degree with the point of view (player's direction in the middle)
    // 30  30
    //    ^
    //  \ | /
    //   \|/
    //    v
    // we will trace the rays starting from the leftmost ray
    castArc -= ANGLE30;
    // wrap around if necessary
    if (castArc < 0)
    {
        castArc = ANGLE360 + castArc;
    }

    for (castColumn = 0; castColumn < PROJECTIONPLANEWIDTH; castColumn++)
    {
        // Ray is between 0 to 180 degree (1st and 2nd quadrant).

        // Ray is facing down
        if (castArc > ANGLE0 && castArc < ANGLE180)
        {
            // truncuate then add to get the coordinate of the FIRST grid (horizontal
            // wall) that is in front of the player (this is in pixel unit)
            // ROUNDED DOWN
            horizontalGrid = floor(wolf->fPlayerY / TILE_SIZE) * TILE_SIZE  + TILE_SIZE;

            // compute distance to the next horizontal wall
            distToNextHorizontalGrid = TILE_SIZE;

            xtemp = wolf->fITanTable[castArc]*(horizontalGrid - wolf->fPlayerY);
            // we can get the vertical distance to that wall by
            // (horizontalGrid-playerY)
            // we can get the horizontal distance to that wall by
            // 1/tan(arc)*verticalDistance
            // find the x interception to that wall
            xIntersection = xtemp + wolf->fPlayerX;
//            if (DEBUG)
//            {
//                console.log("castArc="+castArc+" in CHECKPOINT A, horizontalGrid="+horizontalGrid+" distToNextHorizontalGrid="+distToNextHorizontalGrid+
//                            " xtemp="+xtemp+" xIntersection="+xIntersection);
//            }
        }
            // Else, the ray is facing up
        else
        {
            horizontalGrid = floor(wolf->fPlayerY / TILE_SIZE) * TILE_SIZE;
            distToNextHorizontalGrid = -TILE_SIZE;

            xtemp = wolf->fITanTable[castArc] * (horizontalGrid - wolf->fPlayerY);
            xIntersection = xtemp + wolf->fPlayerX;

            horizontalGrid--;
//            if (DEBUG)
//            {
//                console.log("castArc="+castArc+" in CHECKPOINT B, horizontalGrid="+horizontalGrid+" distToNextHorizontalGrid="+distToNextHorizontalGrid+
//                            " xtemp="+xtemp+" xIntersection="+xIntersection);
//            }
        }
        // LOOK FOR HORIZONTAL WALL

        // If ray is directly facing right or left, then ignore it 
        if (castArc == ANGLE0 || castArc == ANGLE180)
        {
            distToHorizontalGridBeingHit = 2147483647;
        }
            // else, move the ray until it hits a horizontal wall
        else
        {
            distToNextXIntersection = wolf->fXStepTable[castArc];
            while (1)
            {
                xGridIndex = floor(xIntersection / TILE_SIZE);
                yGridIndex = floor(horizontalGrid / TILE_SIZE);
                int mapIndex = floor(yGridIndex * MAP_WIDTH + xGridIndex);
//                if (DEBUG)
//                {
//                    //console.log("this.fPlayerY="+this.fPlayerY+" this.fPlayerX="+this.fPlayerX+" castColumn="+castColumn+" castArc="+castArc+" xIntersection="+xIntersection+" horizontalGrid="+horizontalGrid+" xGridIndex="+xGridIndex+" yGridIndex="+yGridIndex+" mapIndex="+mapIndex);
//                    //console.log("this.fITanTable="+this.fITanTable[castArc]);
//                }

                // If we've looked as far as outside the map range, then bail out
                if ((xGridIndex >= MAP_WIDTH) ||
                    (yGridIndex >= MAP_HEIGHT) ||
                    xGridIndex < 0 || yGridIndex < 0)
                {
                    distToHorizontalGridBeingHit = 2147483647;
                        break;
                }
                    // If the grid is not an Opening, then stop
                else if (wolf->fMap[mapIndex] != 'O')
                {
                    distToHorizontalGridBeingHit  = (xIntersection - wolf->fPlayerX) *
                            wolf->fICosTable[castArc];
                        break;
                }
                    // Else, keep looking.  At this point, the ray is not blocked, extend the ray to the next grid
                else
                {
                    xIntersection += distToNextXIntersection;
                    horizontalGrid += distToNextHorizontalGrid;
                }
            }
        }

        double ytemp;
        // FOLLOW X RAY
        if (castArc < ANGLE90 || castArc > ANGLE270)
        {
            verticalGrid = TILE_SIZE + floor(wolf->fPlayerX / TILE_SIZE) * TILE_SIZE;
            distToNextVerticalGrid = TILE_SIZE;

            ytemp = wolf->fTanTable[castArc]*(verticalGrid - wolf->fPlayerX);
            yIntersection = ytemp + wolf->fPlayerY;
            if (DEBUG)
            {

               // console.log("castArc="+castArc+" in CHECKPOINT C, horizontalGrid="+horizontalGrid+" distToNextHorizontalGrid="+distToNextHorizontalGrid+
                       //     " ytemp="+ytemp+" yIntersection="+yIntersection);
            }
        }
            // RAY FACING LEFT
        else
        {
            verticalGrid = floor(wolf->fPlayerX / TILE_SIZE) * TILE_SIZE;
            distToNextVerticalGrid = -TILE_SIZE;

            ytemp = wolf->fTanTable[castArc] * (verticalGrid - wolf->fPlayerX);
            yIntersection = ytemp + wolf->fPlayerY;

            verticalGrid--;
            if (DEBUG)
            {
                //console.log("castArc="+castArc+" in CHECKPOINT D, horizontalGrid="+horizontalGrid+" distToNextHorizontalGrid="+distToNextHorizontalGrid+
                          //  " ytemp="+ytemp+" yIntersection="+yIntersection);
            }
        }
        // LOOK FOR VERTICAL WALL
        if (castArc == ANGLE90||castArc == ANGLE270)
        {
            distToVerticalGridBeingHit = 2147483647;
        }
        else
        {
            distToNextYIntersection = wolf->fYStepTable[castArc];
            while (1)
            {
                // compute current map position to inspect
                xGridIndex = floor(verticalGrid / TILE_SIZE);
                yGridIndex = floor(yIntersection / TILE_SIZE);

                int mapIndex = floor(yGridIndex * MAP_WIDTH + xGridIndex);

                if (DEBUG)
                {
                    //console.log("this.fPlayerY="+this.fPlayerY+" this.fPlayerX="+this.fPlayerX+" castColumn="+castColumn+" castArc="+castArc+" xIntersection="+xIntersection+" horizontalGrid="+horizontalGrid+" xGridIndex="+xGridIndex+" yGridIndex="+yGridIndex+" mapIndex="+mapIndex);
                    //console.log("this.fITanTable="+this.fITanTable[castArc]);
                }

                if ((xGridIndex >= MAP_WIDTH) ||
                    (yGridIndex >= MAP_HEIGHT) ||
                    xGridIndex < 0 || yGridIndex < 0)
                {
                    distToVerticalGridBeingHit = 2147483647;
                        break;
                }
                else if (wolf->fMap[mapIndex] != 'O')
                {
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

        // DRAW THE WALL SLICE
        int scaleFactor;
        int dist;
        int xOffset;
        int topOfWall;   // used to compute the top and bottom of the sliver that
        int bottomOfWall;   // will be the staring point of floor and ceiling
        // determine which ray strikes a closer wall.
        // if yray distance to the wall is closer, the yDistance will be shorter than
        // the xDistance
        int isVerticalHit = 0;
        int distortedDistance = 0;
//        int bottomOfWall;
//        int topOfWall;
        if (distToHorizontalGridBeingHit < distToVerticalGridBeingHit)
        {
            // the next function call (drawRayOnMap()) is not a part of raycating rendering part, 
            // it just draws the ray on the overhead map to illustrate the raycasting process
            drawRayOnOverheadMap(wolf, xIntersection, horizontalGrid);
            dist = distToHorizontalGridBeingHit / wolf->fFishTable[castColumn];
//				dist_y /= convert_to_float(GLfishTable[GLcastColumn]);
            distortedDistance = dist;
            double ratio = wolf->fPlayerDistanceToTheProjectionPlane / dist;
            bottomOfWall = (ratio * wolf->fPlayerHeight + wolf->fProjectionPlaneYCenter);
            double scale = (wolf->fPlayerDistanceToTheProjectionPlane * WALL_HEIGHT / dist);
            topOfWall = bottomOfWall - scale;
            /*dist_y /= convert_to_float(GLfishTable[GLcastColumn]);
            float ratio = GLplayerDistance/dist_y;
            bot_of_wall = (int)(ratio * GLplayerHeight + GLviewportCenter);
            scale = (int)(GLplayerDistance*GLwallHeight/dist_y);
            top_of_wall = bot_of_wall - scale;*/


            xOffset = (int)xIntersection % TILE_SIZE;
//            if (DEBUG)
//            {
//                console.log("castColumn="+castColumn+" using distToHorizontalGridBeingHit");
//            }
        }
            // else, we use xray instead (meaning the vertical wall is closer than
            //   the horizontal wall)
        else
        {
            isVerticalHit = 1;
            // the next function call (drawRayOnMap()) is not a part of raycating rendering part, 
            // it just draws the ray on the overhead map to illustrate the raycasting process
            drawRayOnOverheadMap(wolf, verticalGrid, yIntersection);
            dist = distToVerticalGridBeingHit / wolf->fFishTable[castColumn];

            xOffset = (int)yIntersection % TILE_SIZE;

            double ratio = wolf->fPlayerDistanceToTheProjectionPlane / dist;
            bottomOfWall = (ratio * wolf->fPlayerHeight + wolf->fProjectionPlaneYCenter);
            double scale = (wolf->fPlayerDistanceToTheProjectionPlane * WALL_HEIGHT / dist);
            topOfWall = bottomOfWall - scale;

//            if (DEBUG)
//            {
//                console.log("castColumn="+castColumn+" using distToVerticalGridBeingHit");
//            }
        }

        // correct distance (compensate for the fishbown effect)
        //dist /= this.fFishTable[castColumn];
        // projected_wall_height/wall_height = fPlayerDistToProjectionPlane/dist;
        //int projectedWallHeight=(this.WALL_HEIGHT*this.fPlayerDistanceToTheProjectionPlane/dist);
        //bottomOfWall = this.fProjectionPlaneYCenter+(projectedWallHeight*0.5);
        //topOfWall = this.fProjectionPlaneYCenter-(projectedWallHeight*0.5);

//        if (DEBUG)
//        {
//            console.log("castColumn="+castColumn+" distance="+dist);
//        }


        // Add simple shading so that farther wall slices appear darker.
        // use arbitrary value of the farthest distance.  
        dist = floor(dist);

        // Trick to give different shades between vertical and horizontal (you could also use different textures for each if you wish to)
        if (isVerticalHit)
            drawWallSliceRectangleTinted(wolf, castColumn, topOfWall, 1, (bottomOfWall-topOfWall) + 1, xOffset, wolf->baseLightValue / (dist));
        else
            drawWallSliceRectangleTinted(wolf, castColumn, topOfWall, 1, (bottomOfWall-topOfWall) + 1, xOffset, (wolf->baseLightValue - 50) / (dist));



        wolf->bytesPerPixel = 4;
        int projectionPlaneCenterY = wolf->fProjectionPlaneYCenter;
        int lastBottomOfWall = floor(bottomOfWall);
        int lastTopOfWall = floor(topOfWall);

        //*************
        // FLOOR CASTING at the simplest!  Try to find ways to optimize this, you can do it!
        //*************
        if (fFloorTextureBuffer != 2147483647)
        {
            // find the first bit so we can just add the width to get the
            // next row (of the same column)
/
/
/
/
/
/
/
/
//
/
/
/
/
//
//
/
/
/
            int targetIndex = lastBottomOfWall * (offscreenCanvasPixels.width*bytesPerPixel)+(bytesPerPixel*castColumn);
            for (int row=lastBottomOfWall;row<this.PROJECTIONPLANEHEIGHT;row++)
            {

                int straightDistance=(this.fPlayerHeight)/(row-projectionPlaneCenterY)*
                                     this.fPlayerDistanceToTheProjectionPlane;

                int actualDistance=straightDistance*
                                   (this.fFishTable[castColumn]);

                int yEnd = Math.floor(actualDistance * this.fSinTable[castArc]);
                int xEnd = Math.floor(actualDistance * this.fCosTable[castArc]);

                // Translate relative to viewer coordinates:
                xEnd+=this.fPlayerX;
                yEnd+=this.fPlayerY;


                // Get the tile intersected by ray:
                int cellX = Math.floor(xEnd / this.TILE_SIZE);
                int cellY = Math.floor(yEnd / this.TILE_SIZE);
                //console.log("cellX="+cellX+" cellY="+cellY);

                //Make sure the tile is within our map
                if ((cellX<this.MAP_WIDTH) &&
                    (cellY<this.MAP_HEIGHT) &&
                    cellX>=0 && cellY>=0)
                {
                    // Find offset of tile and column in texture
                    int tileRow = Math.floor(yEnd % this.TILE_SIZE);
                    int tileColumn = Math.floor(xEnd % this.TILE_SIZE);
                    // Pixel to draw
                    int sourceIndex=(tileRow*this.fFloorTextureBuffer.width*bytesPerPixel)+(bytesPerPixel*tileColumn);

                    // Cheap shading trick
                    int brighnessLevel=(150/(actualDistance));
                    int red=Math.floor(this.fFloorTexturePixels[sourceIndex]*brighnessLevel);
                    int green=Math.floor(this.fFloorTexturePixels[sourceIndex+1]*brighnessLevel);
                    int blue=Math.floor(this.fFloorTexturePixels[sourceIndex+2]*brighnessLevel);
                    int alpha=Math.floor(this.fFloorTexturePixels[sourceIndex+3]);

                    // Draw the pixel
                    this.offscreenCanvasPixels.data[targetIndex]=red;
                    this.offscreenCanvasPixels.data[targetIndex+1]=green;
                    this.offscreenCanvasPixels.data[targetIndex+2]=blue;
                    this.offscreenCanvasPixels.data[targetIndex+3]=alpha;

                    // Go to the next pixel (directly under the current pixel)
                    targetIndex+=(bytesPerPixel*this.offscreenCanvasPixels.width);
                }
            }
        }
//        //*************
//        // CEILING CASTING at the simplest!  Try to find ways to optimize this, you can do it!
//        //*************
//        if (this.fCeilingTextureBuffer!=undefined)
//        {
//            //console.log("this.fCeilingTexturePixels[0]="+this.fCeilingTexturePixels[0]);
//            // find the first bit so we can just add the width to get the
//            // next row (of the same column)
//
//
//            int targetIndex=lastTopOfWall*(this.offscreenCanvasPixels.width*bytesPerPixel)+(bytesPerPixel*castColumn);
//            for (int row=lastTopOfWall;row>=0;row--)
//            {
//                int ratio=(this.WALL_HEIGHT-this.fPlayerHeight)/(projectionPlaneCenterY-row);
//
//                int diagonalDistance=Math.floor((this.fPlayerDistanceToTheProjectionPlane*ratio)*
//                                                (this.fFishTable[castColumn]));
//
//                int yEnd = Math.floor(diagonalDistance * this.fSinTable[castArc]);
//                int xEnd = Math.floor(diagonalDistance * this.fCosTable[castArc]);
//
//                // Translate relative to viewer coordinates:
//                xEnd+=this.fPlayerX;
//                yEnd+=this.fPlayerY;
//
//                // Get the tile intersected by ray:
//                int cellX = Math.floor(xEnd / this.TILE_SIZE);
//                int cellY = Math.floor(yEnd / this.TILE_SIZE);
//                //console.log("cellX="+cellX+" cellY="+cellY);
//
//                //Make sure the tile is within our map
//                if ((cellX<this.MAP_WIDTH) &&
//                    (cellY<this.MAP_HEIGHT) &&
//                    cellX>=0 && cellY>=0)
//                {
//
//                    // Find offset of tile and column in texture
//                    int tileRow = Math.floor(yEnd % this.TILE_SIZE);
//                    int tileColumn = Math.floor(xEnd % this.TILE_SIZE);
//                    // Pixel to draw
//                    int sourceIndex=(tileRow*this.fCeilingTextureBuffer.width*bytesPerPixel)+(bytesPerPixel*tileColumn);
//                    //console.log("sourceIndex="+sourceIndex);
//                    // Cheap shading trick
//                    int brighnessLevel=(100/diagonalDistance);
//                    int red=Math.floor(this.fCeilingTexturePixels[sourceIndex]*brighnessLevel);
//                    int green=Math.floor(this.fCeilingTexturePixels[sourceIndex+1]*brighnessLevel);
//                    int blue=Math.floor(this.fCeilingTexturePixels[sourceIndex+2]*brighnessLevel);
//                    int alpha=Math.floor(this.fCeilingTexturePixels[sourceIndex+3]);
//
//                    // Draw the pixel
//                    this.offscreenCanvasPixels.data[targetIndex]=red;
//                    this.offscreenCanvasPixels.data[targetIndex+1]=green;
//                    this.offscreenCanvasPixels.data[targetIndex+2]=blue;
//                    this.offscreenCanvasPixels.data[targetIndex+3]=alpha;
//
//                    // Go to the next pixel (directly above the current pixel)
//                    targetIndex-=(bytesPerPixel*this.offscreenCanvasPixels.width);
//                }
//            }
//        }
//
//        // TRACE THE NEXT RAY
//        castArc+=1;
//        if (castArc>=this.ANGLE360)
//            castArc-=this.ANGLE360;
    }

}

int main(int argc, char *argv[])
{
    new_wolf *wolf;

    wolf = (new_wolf*)malloc(sizeof(new_wolf));



    wolf->fPlayerX = 768/2;
    wolf->fPlayerY = 1024/2;
    wolf->fPlayerArc = ANGLE60;
    wolf->fPlayerDistanceToTheProjectionPlane = 1024 / 2 / tan(3.14 / 180 * 30);
    wolf->fPlayerHeight =32;
    wolf->fPlayerSpeed = 16;


    wolf->fProjectionPlaneYCenter = PROJECTIONPLANEHEIGHT/2;

    wolf->fKeyUp=0;
    wolf->fKeyDown=0;
    wolf->fKeyLeft=0;
    wolf->fKeyRight=0;

    wolf->fBackgroundImageArc=0;

    wolf->baseLightValue=180;
    wolf->baseLightValueDelta=1;

//    this.fMap=[];
//    MAP_WIDTH=12;
//    MAP_HEIGHT=12;

    return (0);
}

//int     main(int argc, char *argv[])
//{
//   t_wolf *wolf;
//
//   if (argc == 2)
//   {
//      wolf = (t_wolf*)malloc(sizeof(t_wolf));
//       ft_bzero(wolf, sizeof(t_wolf));
//       wolf->name = argv[1];
//       ft_read(wolf);
//       if (ft_valid(wolf))
//           ft_error(2, wolf);
//         ft_free_mas(wolf->full_map);
//         ft_init_all(wolf);
//         ft_game(wolf);
//   }
//   else
//       ft_putendl("___Error___\nMany arguments or wrong map selection\n"
//                  "./wolf3d maps/...");
//   system("leaks wolf3d");
//   return (0);
//}