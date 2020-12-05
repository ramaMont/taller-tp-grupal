#ifndef __PROTOCOL__
#define __PROTOCOL__



class Protocol{
public:
    enum action { MOVE, SHOOT, LOAD, PICKUP, OPEN,
            SHOOTED, ADDKILL, ADDPOINTS, ENDGAME };

    enum direction{ FORWARD, BACKWARD, LEFT, RIGHT,
            ROTATE_LEFT, ROTATE_RIGHT};
    explicit Protocol(int id);
    explicit Protocol(int id, enum direction);
    Protocol::action getAction();
    Protocol::direction getDirection();
    void moveInDirection(Protocol::direction direction);
    int getId();
    ~Protocol();
private:
    Protocol::action _action;
    int id;
    Protocol::direction _direction;
    int damage;
};

#endif
