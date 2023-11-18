#include <nds.h>
#include <gl2d.h>
using namespace std;
//#include "Platform.h"

//ugly hack
typedef struct {
    int x;
    int y;
    int width;
    int height;
} Platform;


class Character {
public:
    int x, y;
    int vel, velx;
    bool grounded;
    bool isDashing;
    int PlayerColor, PlayerColor2;
    int dashDuration;
    bool onTurn;
    int frame;
    int lastDPadPressTime;

    Character() {
        // Initialize variables here
        x = 128;
        y = 0;
        vel = 0;
        velx = 0;
        grounded = false;
        isDashing = false;
        PlayerColor = 142;
        PlayerColor2 = 255;
        dashDuration = 0;
        onTurn = false;
        frame = 0;
        lastDPadPressTime = 0;
    }

    void update(Platform platforms[], int num_platforms, int scrollX, int scrollY) {
        // Update character state here
        // Increment Frame Check by +1
        frame++;

        //check input
        scanKeys();
        uint32 keys = keysHeld();
        
        // Jump handling
        if((keysDown() & KEY_B)){
            vel = -100;
        }

        // Movement Handling
        handleMovement();

        for (int i = 0; i < num_platforms; i++){
            Platform p = platforms[i];
            if(collidesWith(p, scrollX, scrollY)){
                velx = 0;
                vel = 0;
                grounded = true;
            }
        }


    } 


    void draw(const glImage* playerSprite) {
        // Draw character here
        if (!onTurn){
            glSprite(x, y, GL_FLIP_NONE, playerSprite);
        }else{
            glSprite(x, y, GL_FLIP_H, playerSprite);
        }
    }

    void handleMovement(){
        if(keysHeld() & KEY_LEFT){
    onTurn = false;
    if((keysDown() & KEY_LEFT) && (frame - lastDPadPressTime <= 30))
    {
        velx = -3;
        isDashing = true;
        //dashDuration = 30;  // Set dash duration
    }
    else if(!isDashing){
        velx = -2;
    }
    if(keysDown() & KEY_LEFT) {
        lastDPadPressTime = frame;
    } 	
    if(isDashing && (keysHeld() & KEY_RIGHT)){
        isDashing = false;
    }
}
else if(keysHeld() & KEY_RIGHT) {
    onTurn = true;
    if((keysDown() & KEY_RIGHT) && (frame - lastDPadPressTime <= 30))
    {
        velx = 3;
        isDashing = true;
        //dashDuration = 30;  // Set dash duration
    }
    else if(!isDashing){
        velx = 2;
    }
    if(keysDown() & KEY_RIGHT) {
        lastDPadPressTime = frame;
    }
    if(isDashing && (keysHeld() & KEY_LEFT)){
        isDashing = false;
    }
} 

if(!(keysHeld() & KEY_LEFT) && !(keysHeld() & KEY_RIGHT)){
    isDashing = false;
    velx = 0;
}
}

    bool collidesWith(Platform p, int scrollX, int scrollY) {
    // Calculate the player's screen coordinates
    int player_screen_x = x - scrollX;
    int player_screen_y = y - scrollY;

    // Calculate the platform's screen coordinates
    int platform_screen_x = p.x - scrollX;
    int platform_screen_y = p.y - scrollY;

    // Check for intersection
    if(player_screen_x < platform_screen_x + p.width && 
       player_screen_x + 16 > platform_screen_x && 
       player_screen_y < platform_screen_y + p.height && 
       player_screen_y + 16 > platform_screen_y) {
        return true;
    }

    return false;
}


};
