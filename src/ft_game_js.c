#include "wolf3d.h"

void	drawWallSliceRectangleTinted(t_wolf *wolf, int x, int y, int width, double height, int xOffset, int brightnessLevel)
{
		// console.log("9");
		// wait until the texture loads
		// if (fWallTextureBuffer==undefined)
			// return;
		// printf("%d\n", xOffset);
		double dy = height;
		x = floor(x);
		y = floor(y);
		xOffset = floor(xOffset);
		wolf->bytesPerPixel=4;
		
		int sourceIndex = xOffset;
		int lastSourceIndex = sourceIndex + (256 * 256);
		
		//var targetCanvasPixels=this.canvasContext.createImageData(0, 0, width, height);
		int targetIndex = 1024 * y + x;
		
		// if (y < 0)
//			printf("%d\n", y);
		
		double heightToDraw = height;
		// clip bottom
		if (y + heightToDraw > 768)
			heightToDraw = 768 - y;

		
		int yError = 0;   


		
		// we need to check this, otherwise, program might crash when trying
		// to fetch the shade if this condition is true (possible if height is 0)
		if (heightToDraw < 0)
			return;

		// we're going to draw the first row, then move down and draw the next row
		// and so on we can use the original x destination to find out
		// the x position of the next row 
		// Remeber that the source bitmap is rotated, so the width is actually the
		// height

		// int i = 0;
		// int n = 0;

		// while (i < HEIGHT)
		// {
		// 	n = 0;
		// 	while (n < WIDTH)
		// 	{
		// 		unsigned int color = (256 * 256 * 100)+(256 * 255) + 255;
		// 		wolf->buf[i][n] = color;
		// 		n++;
		// 	}
		// 	i++;
		// }

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
			yError += height;
												  
			// dereference for faster access (especially useful when the same bit
			// will be copied more than once)

			// Cheap shading trick by using brightnessLevel (which doesn't really have to correspond to "brightness") 
			// to alter colors.  You can use logarithmic falloff or linear falloff to produce some interesting effect
			// int red = floor(this.fWallTexturePixels[sourceIndex] * brightnessLevel);
			// int green = floor(this.fWallTexturePixels[sourceIndex+1]*brightnessLevel);
			// int blue = floor(this.fWallTexturePixels[sourceIndex+2]*brightnessLevel);
			// int alpha = floor(this.fWallTexturePixels[sourceIndex+3]);
			// printf("%d\n", yError);
			unsigned int *pixels = (unsigned int *)wolf->sdl.wall[0]->pixels;
			unsigned int color = pixels[xOffset];
			// if (color < 4181811492)
			// 	printf("%u\n", color);
// printf("x = %d\n", x);
// printf("y = %d\n", y);
// printf("xOffset %d\n", xOffset);
// printf("width %d\n", width);
// printf("height %f\n", height);
// printf("brightnessLevel %d\n", brightnessLevel);
			// static int test;
			// // test = 0;
			// if (test > targetIndex)
			// {
			// 	test = targetIndex;
			// 	printf("%d\n", targetIndex);
			// }
			// if (targetIndex < 0)
			

			// printf("%d\n", color);
			// printf("%d\n", x);
			// printf("%d\n", y);
			// while there's a row to draw & not end of drawing area
			while (yError >= 256)
			{                  
				yError -= 256;
				wolf->buf_js[targetIndex] = color;
				// this.offscreenCanvasPixels.data[targetIndex]=red;
				// this.offscreenCanvasPixels.data[targetIndex+1]=green;
				// this.offscreenCanvasPixels.data[targetIndex+2]=blue;
				// this.offscreenCanvasPixels.data[targetIndex+3]=alpha;
				// targetIndex+=(bytesPerPixel*this.offscreenCanvasPixels.width);
				// clip bottom (just return if we reach bottom)
				heightToDraw--;
				if (heightToDraw<1)
					return;
			} 
			sourceIndex += 256;
			if (sourceIndex > lastSourceIndex)
				sourceIndex = lastSourceIndex;			
		}

	}


void	raycast(t_wolf *wolf)
{
	int verticalGrid;        // горизонтальная или вертикальная координата пересечения
	int horizontalGrid;      // теоретически это будет кратно TILE_SIZE
							 // , но какой-то трюк здесь может привести к
							 // значению на 1
	int distToNextVerticalGrid; // как далеко до следующей границы (это кратно
	int distToNextHorizontalGrid; // tile size)
	double xIntersection;  // пересечения х и у
	double yIntersection;
	double distToNextXIntersection;
	double distToNextYIntersection;

	int xGridIndex;        // текущая ячейка, в которой находится луч
	int yGridIndex;

	double distToVerticalGridBeingHit;      // расстояние пересечения x и y лучей от
	double distToHorizontalGridBeingHit;      // точки зрения

	int castArc, castColumn;
	int DEBUG = 0;
	
	castArc = wolf->fPlayerArc;
	// поле обзора составляет 60 градусов с точки зрения (направление игрока в середине)
	// 30  30
	//    ^
	//  \ | /
	//   \|/
	//    v
	// мы будем отслеживать лучи, начиная с самого левого луча
	castArc -= ANGLE30;
	// обернуть при необходимости
	if (castArc < 0)
	{
		castArc = ANGLE360 + castArc;
	}

	for (castColumn = 0; castColumn < PROJECTIONPLANEWIDTH; castColumn++)
	{
		// Луч находится между 0 и 180 градусами (1-й и 2-й квадрант).
		
		// Луч направлен вниз
		if (castArc > ANGLE0 && castArc < ANGLE180)
		{
			// усечь затем добавить, чтобы получить координату 
			//ПЕРВОЙ сетки (горизонтальная стена), которая находится 
			//перед игроком (это в пиксельных единицах) КРУГЛЫЙ ВНИЗ
			horizontalGrid = floor(wolf->fPlayerY / TILE_SIZE) * TILE_SIZE  + TILE_SIZE;

//			printf("%d\n", horizontalGrid/256);

			// вычислить расстояние до следующей горизонтальной стены
			distToNextHorizontalGrid = TILE_SIZE;

			double xtemp = wolf->fITanTable[castArc] * (wolf->fPlayerY - horizontalGrid);
			// мы можем получить вертикальное расстояние до этой стены
			// (horizontalGrid-playerY)
			// мы можем получить горизонтальное расстояние до этой стены
			// 1/tan(arc)*verticalDistance
			// найти х перехват к этой стене
			xIntersection = xtemp + wolf->fPlayerX;
			if (DEBUG)
			{				
				// console.log("castArc="+castArc+" in CHECKPOINT A, horizontalGrid="+horizontalGrid+" distToNextHorizontalGrid="+distToNextHorizontalGrid+
				// 	" xtemp="+xtemp+" xIntersection="+xIntersection);				
				printf("%s\n", "error");
			}				
		}
		// Иначе, луч направлен вверх
		else
		{
			horizontalGrid = floor(wolf->fPlayerY / TILE_SIZE) * TILE_SIZE;
			distToNextHorizontalGrid = -TILE_SIZE;

			double xtemp = wolf->fITanTable[castArc] * (wolf->fPlayerY - horizontalGrid);
			xIntersection = xtemp + wolf->fPlayerX;

			horizontalGrid--;
			if (DEBUG)
			{				
				// console.log("castArc="+castArc+" in CHECKPOINT B, horizontalGrid="+horizontalGrid+" distToNextHorizontalGrid="+distToNextHorizontalGrid+
				// 	" xtemp="+xtemp+" xIntersection="+xIntersection);	
				printf("%s\n", "error");			
			}
		}
		//ИЩУ ГОРИЗОНТАЛЬНУЮ СТЕНУ
		
		// Если луч направлен прямо вправо или влево, тогда игнорируйте его
		if (castArc == ANGLE0 || castArc == ANGLE180)
		{
			distToHorizontalGridBeingHit = 2147483647;
		}
		//иначе перемещайте луч, пока он не достигнет горизонтальной стены
		else
		{
			distToNextXIntersection = wolf->fXStepTable[castArc];
			while (1)
			{
				xGridIndex = floor(xIntersection / TILE_SIZE);
				yGridIndex = floor(horizontalGrid / TILE_SIZE);
//				if (xGridIndex > 1)
//                printf("1 %d\n", xGridIndex);
//                printf("2 %d\n", yGridIndex);
//                printf("3 %f\n", floor((wolf->fPlayerX + (wolf->fPlayerY - horizontalGrid) / tan(60 / 3.14 * 180)) / 256));
				int mapIndex = floor(yGridIndex * MAP_WIDTH + xGridIndex);
//				printf("%d\n", mapIndex);
				if (DEBUG)
				{										
					// console.log("fPlayerY="+fPlayerY+" fPlayerX="+fPlayerX+" castColumn="+castColumn+" castArc="+castArc+" xIntersection="+xIntersection+" horizontalGrid="+horizontalGrid+" xGridIndex="+xGridIndex+" yGridIndex="+yGridIndex+" mapIndex="+mapIndex);
					// console.log("fITanTable="+fITanTable[castArc]);
					printf("%s\n", "error");
				}
				
				// Если мы посмотрели так далеко за пределы диапазона карты, то выручите
				if ((xGridIndex >= MAP_WIDTH) ||
					(yGridIndex >= MAP_HEIGHT) ||
					xGridIndex < 0 || yGridIndex < 0)
				{
					distToHorizontalGridBeingHit = 2147483647;
						break;
				}
				// Если сетка не является открытием, остановите
				else if (wolf->fMap[mapIndex]!='O')
				{
					distToHorizontalGridBeingHit  = (wolf->fPlayerX - xIntersection) * wolf->fICosTable[castArc];
//					printf("%f\n", wolf->fICos)
//					printf("%f\n", distToHorizontalGridBeingHit);
					break;
				}
				// Остальное, продолжай искать. В этот момент 
				//луч не блокируется, распространите луч до следующей сетки
				else
				{
					xIntersection += distToNextXIntersection;
					horizontalGrid += distToNextHorizontalGrid;
				}
			}
		}


		//СЛЕДУЙТЕ за X RAY
		if (castArc < ANGLE90 || castArc > ANGLE270)
		{
			verticalGrid = TILE_SIZE + floor(wolf->fPlayerX / TILE_SIZE) * TILE_SIZE;
			distToNextVerticalGrid = TILE_SIZE;

			double ytemp = wolf->fTanTable[castArc] * (verticalGrid - wolf->fPlayerX);
			yIntersection = ytemp + wolf->fPlayerY;
			if (DEBUG)
			{				
				
				// console.log("castArc="+castArc+" in CHECKPOINT C, horizontalGrid="+horizontalGrid+" distToNextHorizontalGrid="+distToNextHorizontalGrid+
				// 	" ytemp="+ytemp+" yIntersection="+yIntersection);
				printf("%s\n", "error");				
			}
		}
		// RAY FACING LEFT
		else
		{
			verticalGrid = floor(wolf->fPlayerX / TILE_SIZE) * TILE_SIZE;
			distToNextVerticalGrid = -TILE_SIZE;

			double ytemp = wolf->fTanTable[castArc] * (verticalGrid - wolf->fPlayerX);
			yIntersection = ytemp + wolf->fPlayerY;

			verticalGrid--;
			if (DEBUG)
			{								
				// console.log("castArc="+castArc+" in CHECKPOINT D, horizontalGrid="+horizontalGrid+" distToNextHorizontalGrid="+distToNextHorizontalGrid+
				// 	" ytemp="+ytemp+" yIntersection="+yIntersection);	
				printf("%s\n", "error");				
			}
		}
		  // ИЩУ ВЕРТИКАЛЬНУЮ СТЕНУ
		if (castArc == ANGLE90 || castArc == ANGLE270)
		{
			distToVerticalGridBeingHit = 2147483647;
		}
		else
		{
			distToNextYIntersection = wolf->fYStepTable[castArc];
			while (1)
			{
				// вычислить текущую позицию карты для проверки
				xGridIndex = floor(verticalGrid / TILE_SIZE);
				yGridIndex = floor(yIntersection / TILE_SIZE);

				int mapIndex = floor(yGridIndex * MAP_WIDTH + xGridIndex);
				
				if (DEBUG)
				{
				// 	console.log("fPlayerY="+fPlayerY+" fPlayerX="+fPlayerX+" castColumn="+castColumn+" castArc="+castArc+" xIntersection="+xIntersection+" horizontalGrid="+horizontalGrid+" xGridIndex="+xGridIndex+" yGridIndex="+yGridIndex+" mapIndex="+mapIndex);
				// 	console.log("fITanTable="+fITanTable[castArc]);
					printf("%s\n", "error");
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

		// DRAW THE WALL SLICE //НАСТРОЙТЕ НАСТЕННЫЙ КУСОК
		double scaleFactor;
		double dist;
		double xOffset;
		double topOfWall;   // используется для вычисления верхней и нижней части ленты,
		double bottomOfWall;   // будет отправной точкой пола и потолка
		// определить, какой луч падает на более тесную стену.
		// если расстояние до стены ближе, расстояние будет меньше, чем
		// xDistance
		int isVerticalHit = 0;
		double distortedDistance = 0;
		if (distToHorizontalGridBeingHit < distToVerticalGridBeingHit)
		{
			// следующий вызов функции (drawRayOnMap ()) не является частью рендеринга, 
			// он просто рисует луч на верхней карте, чтобы проиллюстрировать процесс лучевого вещания
			// drawRayOnOverheadMap(xIntersection, horizontalGrid);
			dist = distToHorizontalGridBeingHit / wolf->fFishTable[castColumn];
//				dist_y /= convert_to_float(GLfishTable[GLcastColumn]);
			distortedDistance = dist;
			double ratio = wolf->fPlayerDistanceToTheProjectionPlane / dist;
			bottomOfWall = (ratio * wolf->fPlayerHeight + wolf->fProjectionPlaneYCenter);
			double scale = (wolf->fPlayerDistanceToTheProjectionPlane * WALL_HEIGHT / dist);	
			topOfWall = bottomOfWall - scale;
//			 printf("%f\n", topOfWall);
//			 printf("%f\n", bottomOfWall);
        /*dist_y /= convert_to_float(GLfishTable[GLcastColumn]);
        float ratio = GLplayerDistance/dist_y;
        bot_of_wall = (int)(ratio * GLplayerHeight + GLviewportCenter);
        scale = (int)(GLplayerDistance*GLwallHeight/dist_y);
        top_of_wall = bot_of_wall - scale;*/
		
			
			xOffset = (int)xIntersection % (int)TILE_SIZE;
			if (DEBUG)
			{				
				// console.log("castColumn="+castColumn+" using distToHorizontalGridBeingHit");
				printf("%s\n", "error");
			}
		}
		// иначе мы используем рентгеновское излучение (то есть вертикальная стена ближе, чем горизонтальная)
		else
		{
			isVerticalHit = 1;
			// следующий вызов функции (drawRayOnMap ()) не является частью лучевой визуализации,
			//он просто рисует луч на верхней карте, чтобы проиллюстрировать процесс лучевого вещания
			// drawRayOnOverheadMap(verticalGrid, yIntersection);
			dist = distToVerticalGridBeingHit / wolf->fFishTable[castColumn];

			xOffset = (int)yIntersection % (int)TILE_SIZE;
			
			double ratio = wolf->fPlayerDistanceToTheProjectionPlane / dist;
			bottomOfWall = (ratio * wolf->fPlayerHeight + wolf->fProjectionPlaneYCenter);
			double scale = (wolf->fPlayerDistanceToTheProjectionPlane * WALL_HEIGHT / dist);	
			topOfWall = bottomOfWall - scale;
			
			if (DEBUG)
			{				
				// console.log("castColumn="+castColumn+" using distToVerticalGridBeingHit");
				printf("%s\n", "error");
			}
		}

		// correct distance (compensate for the fishbown effect)
		//dist /= fFishTable[castColumn];
		// projected_wall_height/wall_height = fPlayerDistToProjectionPlane/dist;
		//var projectedWallHeight=(WALL_HEIGHT*fPlayerDistanceToTheProjectionPlane/dist);
		//bottomOfWall = fProjectionPlaneYCenter+(projectedWallHeight*0.5);
		//topOfWall = fProjectionPlaneYCenter-(projectedWallHeight*0.5);

		if (DEBUG)
		{				
			// console.log("castColumn="+castColumn+" distance="+dist);
			printf("%s\n", "error");
		}  
		
		
		// Добавьте простую штриховку, чтобы дальнейшие 
		//кусочки стены казались темнее. использовать произвольное значение дальнего расстояния.
		dist = floor(dist);

		// Трюк, чтобы дать разные оттенки между вертикальным и горизонтальным (вы также можете использовать разные текстуры для каждого, если хотите)
		if (isVerticalHit)
			drawWallSliceRectangleTinted(wolf, castColumn, topOfWall, 1, (bottomOfWall-topOfWall)+1, xOffset, wolf->baseLightValue/(dist));
		else
			drawWallSliceRectangleTinted(wolf, castColumn, topOfWall, 1, (bottomOfWall-topOfWall)+1, xOffset, (wolf->baseLightValue-50)/(dist));
			

		
		// wolf->bytesPerPixel=4;
		// int projectionPlaneCenterY = wolf->fProjectionPlaneYCenter;
		// int lastBottomOfWall = floor(bottomOfWall);
		// int lastTopOfWall = floor(topOfWall);
		
		// //*************
		// // FLOOR CASTING at the simplest!  Try to find ways to optimize this, you can do it!
		// //*************
		// // if (fFloorTextureBuffer != undefined)
		// // {
		// 	// find the first bit so we can just add the width to get the
		// 	// next row (of the same column)
		// 	int targetIndex = lastBottomOfWall * (1024 * wolf->bytesPerPixel) + (wolf->bytesPerPixel * castColumn);
		// 	for (int row = lastBottomOfWall; row < PROJECTIONPLANEHEIGHT; row++) 
		// 	{                          
				
		// 		double straightDistance = (wolf->fPlayerHeight) / (row - projectionPlaneCenterY) * 
		// 		wolf->fPlayerDistanceToTheProjectionPlane;
				
		// 		double actualDistance = straightDistance * (wolf->fFishTable[castColumn]);

		// 		int yEnd = floor(actualDistance * wolf->fSinTable[castArc]);
		// 		int xEnd = floor(actualDistance * wolf->fCosTable[castArc]);
	
		// 		// Translate relative to viewer coordinates:
		// 		xEnd += wolf->fPlayerX;
		// 		yEnd += wolf->fPlayerY;

				
		// 		// Get the tile intersected by ray:
		// 		int cellX = floor(xEnd / TILE_SIZE);
		// 		int cellY = floor(yEnd / TILE_SIZE);
		// 		//console.log("cellX="+cellX+" cellY="+cellY);
				
		// 		//Make sure the tile is within our map
		// 		if ((cellX < MAP_WIDTH) && (cellY < MAP_HEIGHT) && cellX >= 0 && cellY >= 0)
		// 		{            
		// 			// Find offset of tile and column in texture
		// 			int tileRow = floor(yEnd % TILE_SIZE);
		// 			int tileColumn = floor(xEnd % TILE_SIZE);
		// 			// Pixel to draw
		// 			int sourceIndex=(tileRow * 1024 * wolf->bytesPerPixel) + (wolf->bytesPerPixel * tileColumn);
					
		// 			// Cheap shading trick
		// 			double brighnessLevel = (150 / (actualDistance));
		// 			// int red = floor(fFloorTexturePixels[sourceIndex]*brighnessLevel);
		// 			// int green = floor(fFloorTexturePixels[sourceIndex+1]*brighnessLevel);
		// 			// int blue = floor(fFloorTexturePixels[sourceIndex+2]*brighnessLevel);
		// 			// int alpha = floor(fFloorTexturePixels[sourceIndex+3]);						
					
		// 			// Draw the pixel 
		// 			offscreenCanvasPixels.data[targetIndex]=red;
		// 			offscreenCanvasPixels.data[targetIndex+1]=green;
		// 			offscreenCanvasPixels.data[targetIndex+2]=blue;
		// 			offscreenCanvasPixels.data[targetIndex+3]=alpha;
					
		// 			// Go to the next pixel (directly under the current pixel)
		// 			targetIndex+=(bytesPerPixel*offscreenCanvasPixels.width);											
		// 		}                                                              
		// 	}	
		// }
		// //*************
		// // CEILING CASTING at the simplest!  Try to find ways to optimize this, you can do it!
		// //*************
		// if (fCeilingTextureBuffer!=undefined)
		// {
		// 	//console.log("fCeilingTexturePixels[0]="+fCeilingTexturePixels[0]);
		// 	// find the first bit so we can just add the width to get the
		// 	// next row (of the same column)

					
		// 	var targetIndex=lastTopOfWall*(offscreenCanvasPixels.width*bytesPerPixel)+(bytesPerPixel*castColumn);
		// 	for (var row=lastTopOfWall;row>=0;row--) 
		// 	{                          
		// 		var ratio=(WALL_HEIGHT-fPlayerHeight)/(projectionPlaneCenterY-row);

		// 		var diagonalDistance=Math.floor((fPlayerDistanceToTheProjectionPlane*ratio)*
		// 			(fFishTable[castColumn]));

		// 		var yEnd = Math.floor(diagonalDistance * fSinTable[castArc]);
		// 		var xEnd = Math.floor(diagonalDistance * fCosTable[castArc]);
	
		// 		// Translate relative to viewer coordinates:
		// 		xEnd+=fPlayerX;
		// 		yEnd+=fPlayerY;

		// 		// Get the tile intersected by ray:
		// 		var cellX = Math.floor(xEnd / TILE_SIZE);
		// 		var cellY = Math.floor(yEnd / TILE_SIZE);
		// 		//console.log("cellX="+cellX+" cellY="+cellY);
				  
		// 		//Make sure the tile is within our map
		// 		if ((cellX<MAP_WIDTH) &&   
		// 			(cellY<MAP_HEIGHT) &&
		// 			cellX>=0 && cellY>=0)
		// 		{            
				
		// 			// Find offset of tile and column in texture
		// 			var tileRow = Math.floor(yEnd % TILE_SIZE);
		// 			var tileColumn = Math.floor(xEnd % TILE_SIZE);
		// 			// Pixel to draw
		// 			var sourceIndex=(tileRow*fCeilingTextureBuffer.width*bytesPerPixel)+(bytesPerPixel*tileColumn);
		// 			//console.log("sourceIndex="+sourceIndex);
		// 			// Cheap shading trick
		// 			var brighnessLevel=(100/diagonalDistance);
		// 			var red=Math.floor(fCeilingTexturePixels[sourceIndex]*brighnessLevel);
		// 			var green=Math.floor(fCeilingTexturePixels[sourceIndex+1]*brighnessLevel);
		// 			var blue=Math.floor(fCeilingTexturePixels[sourceIndex+2]*brighnessLevel);
		// 			var alpha=Math.floor(fCeilingTexturePixels[sourceIndex+3]);						
					
		// 			// Draw the pixel 
		// 			offscreenCanvasPixels.data[targetIndex]=red;
		// 			offscreenCanvasPixels.data[targetIndex+1]=green;
		// 			offscreenCanvasPixels.data[targetIndex+2]=blue;
		// 			offscreenCanvasPixels.data[targetIndex+3]=alpha;
					
		// 			// Go to the next pixel (directly above the current pixel)
		// 			targetIndex-=(bytesPerPixel*offscreenCanvasPixels.width);											
		// 		}                                                              
		// 	}	
		// }				
			
		// TRACE THE NEXT RAY
		castArc+=1;
		if (castArc>=ANGLE360)
			castArc-=ANGLE360;
	}

}


void	ft_game_js(t_wolf *wolf)
{
	while (wolf->loop)
	{
		// drawOverheadMap(wolf);
		raycast(wolf);
		keys(wolf);
		 SDL_UpdateTexture(wolf->sdl.screen, NULL, wolf->buf, WIDTH << 2);
    SDL_RenderCopy(wolf->sdl.ren, wolf->sdl.screen, NULL, NULL);
    // SDL_RenderCopy(wolf->sdl.ren, wolf->sdl.font_text, NULL, &wolf->sdl.font_rect);
    SDL_RenderPresent(wolf->sdl.ren);
    // SDL_DestroyTexture(wolf->sdl.font_text);
    SDL_FreeSurface(wolf->sdl.font_surface);
    // TTF_CloseFont(wolf->sdl.font_ttf);
	}
}