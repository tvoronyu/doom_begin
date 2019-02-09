#include "wolf3d.h"

long double  *creatMasInt(int count)
{
	long double *mas;
	int index;

	index = 0; 
	mas = NULL;
	mas = (long double*)malloc(sizeof(long double) * count);
	while (index < count)
		mas[index++] = 0;
	return (mas);
}


double  arcToRad(double arcAngle)
{
	// console.log("7");
	return ((arcAngle * 3.14) / ANGLE180);    
}

void	t_init(t_wolf *wolf)
{
	// console.log("test");
	// // loadWallTexture(); YES
	// // loadFloorTexture(); YES
	// // loadCeilingTexture(); YES
	int i;
	long double radian;
	wolf->fSinTable = creatMasInt(ANGLE360+1);
	wolf->fISinTable = creatMasInt(ANGLE360+1);
	wolf->fCosTable = creatMasInt(ANGLE360+1);
	wolf->fICosTable = creatMasInt(ANGLE360+1);
	wolf->fTanTable = creatMasInt(ANGLE360+1);
	wolf->fITanTable = creatMasInt(ANGLE360+1);
	wolf->fFishTable = creatMasInt(ANGLE360+1);
	wolf->fXStepTable = creatMasInt(ANGLE360+1);
	wolf->fYStepTable = creatMasInt(ANGLE360+1);

	// console.log(fISinTable);

	for (i = 0; i <= ANGLE360; i++)
	{
		// Populate tables with their radian values.
		// (The addition of 0.0001 is a kludge to avoid divisions by 0. Removing it will produce unwanted holes in the wall when a ray is at 0, 90, 180, or 270 degree angles)
		radian = arcToRad(i) + (0.0001);
		wolf->fSinTable[i] = sin(radian);
		wolf->fISinTable[i] = (1.0 / (wolf->fSinTable[i]));
		wolf->fCosTable[i] = cos(radian);
		wolf->fICosTable[i] = (1.0 / (wolf->fCosTable[i]));
		wolf->fTanTable[i] = tan(radian);
		wolf->fITanTable[i] = (1.0 / wolf->fTanTable[i]);

		// Next we crate a table to speed up wall lookups.
		// 
		//  You can see that the distance between walls are the same
		//  if we know the angle
		//  _____|_/next xi______________
		//       |
		//  ____/|next xi_________   slope = tan = height / dist between xi's
		//     / |
		//  __/__|_________  dist between xi = height/tan where height=tile size
		// old xi|
		//                  distance between xi = x_step[view_angle];
		
		
		
		// Facing LEFT
		if (i >= ANGLE90 && i < ANGLE270)
		{
			wolf->fXStepTable[i] = (TILE_SIZE / wolf->fTanTable[i]);
			if (wolf->fXStepTable[i] > 0)
				wolf->fXStepTable[i] = -wolf->fXStepTable[i];
		}
		// facing RIGHT
		else
		{
			wolf->fXStepTable[i] = (TILE_SIZE / wolf->fTanTable[i]);
			if (wolf->fXStepTable[i] < 0)
				wolf->fXStepTable[i] = -wolf->fXStepTable[i];
		}

		// FACING DOWN
		if (i >= ANGLE0 && i < ANGLE180)
		{
			wolf->fYStepTable[i] = (TILE_SIZE * wolf->fTanTable[i]);
			if (wolf->fYStepTable[i] < 0)
				wolf->fYStepTable[i] = -wolf->fYStepTable[i];
		}
		// FACING UP
		else
		{
			wolf->fYStepTable[i] = (TILE_SIZE * wolf->fTanTable[i]);
			if (wolf->fYStepTable[i] > 0)
				wolf->fYStepTable[i] = -wolf->fYStepTable[i];
		}
		// printf("%Lf\n", wolf->fYStepTable[i]);
	}

	// Create table for fixing FISHBOWL distortion
	for (i = -ANGLE30; i <= ANGLE30; i++)
	{
		radian = arcToRad(i);
		// we don't have negative angle, so make it start at 0
		// this will give range from column 0 to 319 (PROJECTONPLANEWIDTH) since we only will need to use those range
		wolf->fFishTable[i + (int)ANGLE30] = (1.0 / cos(radian));
	}

    // CREATE A SIMPLE MAP.
	// Use string for elegance (easier to see).  W=Wall, O=Opening
    
	char *map3 = "WWWWWWWWWWWWWWWWWWWWWOOOOOOOOOOOOOOOOOOWWOOWOWOWOOOWOOWWOWOWWOOOOOOOWOOWOOOOWWOWWOOWOWOOWOOWOOWWWWOWWOOWOWWOWOOWOOWOOWOWWOOWOOWOWOOWOOWOOWOWWOOOWOWOWOOWOOOOOWOWWOOOWOWOWOOWOOWOOWOWWOOOWWWOWOOWOOWWWWOWWOOOOOOOOOOOOOOOOOOWWOOWOWOWOOOWOOWWOWOWWOOOOOOOWOOWOOOOOWOWWOOWOWOWOOOWOOWWOWOWWOOOOOOOWOOWOOOOOWOWWOOWOWOWOOOWOOWWOWOWWOOOOOOOWOOOOOOOOWOWWOOWOWOWOOOWOOWWOWOWWOOOOOOOOOOWOOOOOOOWWWWWWWWWWWWWWWWWWWWW";
	// Remove spaces and tabs
	wolf->fMap = map3;
	// console.log(map3);
    // fMap=map3.replace(/\s+/g, '');
    // console.log(fMap);
	// MAP_WIDTH=20;
	// MAP_HEIGHT=20; 		
}

//*******************************************************************//
//* Draw map on the right side
//*******************************************************************//
// drawOverheadMap : function()
// {
// 	// console.log("13");
// 	fMinimapWidth=5;
// 	for (var r=0; r<MAP_HEIGHT; r++)
// 	{
// 		for (var c=0; c<MAP_WIDTH; c++)
// 		{
// 			var cssColor="white";
// 			if (fMap.charAt(r*MAP_WIDTH+c)!="O")
// 			{
// 				drawFillRectangle(PROJECTIONPLANEWIDTH+(c*fMinimapWidth),
// 					(r*fMinimapWidth), fMinimapWidth, fMinimapWidth, 0, 0,0, 255);
// 			}
// 			else
// 			{
// 				drawFillRectangle(PROJECTIONPLANEWIDTH+(c*fMinimapWidth),
// 					(r*fMinimapWidth), fMinimapWidth, fMinimapWidth, 255, 255,255, 255);
// 			}
// 		}
// 	}
// 	// Draw player position on the overhead map
// 	fPlayerMapX=PROJECTIONPLANEWIDTH+((fPlayerX/TILE_SIZE) * fMinimapWidth);
// 	fPlayerMapY=((fPlayerY/TILE_SIZE) * fMinimapWidth);
	
// },


// rgbToHexColor : function(red, green, blue) 
// {
// 	var result="#"+
// 		red.toString(16).toLocaleString('en-US', {minimumIntegerDigits: 2, useGrouping:false})+""+
// 		green.toString(16).toLocaleString('en-US', {minimumIntegerDigits: 2, useGrouping:false})+""+
// 		blue.toString(16).toLocaleString('en-US', {minimumIntegerDigits: 2, useGrouping:false});
// 	return result;
// }