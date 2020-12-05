#ifndef __PROTOCOL__
#define __PROTOCOL__

enum action { MOVE, SHOOT, LOAD, PICKUP, OPEN,
        SHOOTED, ADDKILL, ADDPOINTS, ENDGAME };

enum direction{ FORWARD, BACKWARD, LEFT, RIGHT,
        ROTATE_LEFT, ROTATE_RIGHT};

class Protocol{
private:
    enum action action;
    int id;
    enum direction direction;
    int damage;
public:
    explicit Protocol(int id);
    enum action getAction();
    enum direction getDirection();
    void setDirection(enum direction);
    int getId();
    ~Protocol();
};

#endif
