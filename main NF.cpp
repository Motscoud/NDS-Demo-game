/*---------------------------------------------------------------------------------

	$Id: main.cpp,v 1.13 2008-12-02 20:21:20 dovoto Exp $

	Simple console print demo
	-- dovoto


---------------------------------------------------------------------------------*/
#include <nds.h>
#include <gl2d.h>
#include <stdio.h>
#include <algorithm>

using namespace std;

volatile int frame = 0;
int x = 128, y = 0;
// int p.x = 128, p.y = 170;
// int p.width = 32, p.height=32;
int gravity = 1;
int vel = 0;
int velx = 0;
bool grounded;
int scrollX = 0;
int deadZoneL = 0;
int deadZoneR = 160;
int scrollY = 0;
int deadZoneT = 64;
int deadZoneB = 144;
int jumpFrames = 0;
// //---------------------------------------------------------------------------------
// void Vblank() {
// //---------------------------------------------------------------------------------
// 	frame++;
// }

//Creating a type definition for the Platforms in game, this will allow us to make multiple of them.
typedef struct {
    int x;
    int y;
    int width;
    int height;
} Platform;
	
//Three Platforms in an Array.
//These make up the level
Platform platforms[] = {
    {0, 180, 4028, 64},
    {128, 120, 32, 16},
	{640, 128, 32, 16},
    {704, 96, 32, 16},
    {768, 64, 32, 16},
    {832, 128, 32, 16},
    {896, 96, 32, 16},
    {960, 64, 32, 16},
    {1024, 128, 32, 16},
	{1088, 96, 32, 16},
    {1152, 64, 32, 16},
    {1216, 128, 32, 16},
    {1280, 96, 32, 16},
    {1344, 64, 32, 16},
    {1408, 128, 32, 16},
    {1472, 96, 32, 16},
    {1536, 64, 32, 16},
    {1600, 128, 32, 16},
    {1664, 96, 32, 16},
    {1728, 64, 32, 16},
    {1792, 128, 32, 16},
    {1856, 96, 32, 16},
    {1920, 64, 32, 16},
    {1984, 128, 32, 16},
    {2048, 96, 32, 16}
};


//How many platforms are there, in a level there will be a lot of these.
int num_platforms = sizeof(platforms) / sizeof(Platform);

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	videoSetMode(MODE_5_3D);
	glScreen2D();
 
	while(1) {
		glBegin2D();

		vel += gravity;
		//y += vel;
		grounded = false;

		
		
		//checks keys
		scanKeys();
		//get current keys
		uint32 keys = keysHeld();

		if((keysDown() & KEY_B)){
 	   vel = -10;
		}

		// Update velx based on keys
	if(keys & KEY_LEFT){
    	velx = -2;
	}
	else if(keys & KEY_RIGHT) {
    	velx = 2;
	} else {
   	 velx = 0;
	}

// Update player's x position based on velx and deadzone
x += velx;
// Update player's y position based on vely and deadzone
y += vel;


// Vertical collision detection
for(int i = 0; i < num_platforms; i++){
    Platform p = platforms[i];
    int platform_screen_x = p.x - scrollX;
	int platform_screen_y = p.y - scrollY; // Calculate platform's screen x-coordinate
    if(x < platform_screen_x + p.width && x + 16 > platform_screen_x && y < platform_screen_y + p.height && y + 16 > platform_screen_y) {
        // Collision with the top of the platform
        if(y + 16 <= platform_screen_y + p.height && vel > 0) {
            y = platform_screen_y - 16;
            vel = 0;
            grounded = true;
        }
    }
}

// Horizontal collision detection
for(int i = 0; i < num_platforms; i++){
    Platform p = platforms[i];
    int platform_screen_x = p.x - scrollX; // Calculate platform's screen x-coordinate
	int platform_screen_y = p.y - scrollY; 
    if(x < platform_screen_x + p.width && x + 16 > platform_screen_x && y < platform_screen_y + p.height && y + 16 > platform_screen_y) {
        // Collision with the sides of the platform
        if(x + 16 <= platform_screen_x + p.width && velx > 0 && y + 16 <= platform_screen_y){
            x = platform_screen_x - 16;
            velx = 0;
        }
        else if(x >= platform_screen_x && velx < 0 && y + 16 <= platform_screen_y){
            x = platform_screen_x + p.width;
            velx = 0;
        }
    }
}


if (x < deadZoneL){
    x = deadZoneL;
    scrollX -= 2; // Scroll to the left
}
else if(x > deadZoneR) {
    x = deadZoneR;
    scrollX += 2; // Scroll to the right
}

// Update screen's y-coordinate based on player's y-coordinate
if (y < deadZoneT){
    scrollY -= 2; // Scroll upwards
}
else if(y > deadZoneB) {
    scrollY += 2; // Scroll downwards
}

// Ensure scrollX doesn't go below 0 or above the level width
scrollX = max(0, min(scrollX, 40289 - 256));

if(x - scrollX > 256) {
    x = 0;
    scrollX = 0;
}

		glBoxFilled(x, y, x+16, y+16, RGB15(142,255,255));
		//for loop for the platforms
		for (int i = 0; i < num_platforms; i++){
  		  Platform p = platforms[i];
  		  glBoxFilled(p.x - scrollX, p.y - scrollY, p.x+p.width - scrollX, p.y+p.height - scrollY, RGB15(255,255,255));
		}
   		 
		iprintf("\x1b[10;0HScrollx = %d",scrollX);
		
		glFlush(0);
		swiWaitForVBlank();
	}

	return 0;
}
