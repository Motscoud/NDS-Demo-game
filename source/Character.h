// Character.h

#ifndef CHARACTER_H
#define CHARACTER_H

//#include "Platform.h"
#include <nds.h>
#include <gl2d.h>
#include <vector>
#include "Character.h"
#include "Platform.h" // Include this if Platform is defined in another file
using namespace std;

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

    Character();

    void update(Platform platforms[], int num_platforms, int scrollX, int scrollY);
    void draw(glImage* sprite);
    void handleMovement();
    bool collidesWith(Platform p);
};

#endif // CHARACTER_H
