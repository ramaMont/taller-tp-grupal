#ifndef __PROTOCOL__
#define __PROTOCOL__

enum accion { MOVE, SHOOT, LOAD, PICKUP, OPEN,
        SHOOTED, ADDKILL, ADDPOINTS, ENDGAME };

enum direction{ FORWARD, BACKWARD, LEFT, RIGHT,
        ROTATE_LEFT, ROTATE_RIGHT};

struct Protocol{
    enum accion accion;
    int id;
    enum direction direction;
    int damage;
} PW2D;

#endif
