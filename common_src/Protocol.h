#ifndef __PROTOCOL__
#define __PROTOCOL__

#include <cstdint>

struct __attribute__ ((packed)) Protocol {
public:
    enum action : std::uint16_t { MOVE, SHOOT, LOAD, PICKUP, OPEN,
            SHOOTED, ADDKILL, ADDPOINTS, ENDGAME, SET_ID,
            JOIN_GAME, CREATE_GAME, OK, ERROR, ADD_PLAYER, LAUNCH_GAME, BEGIN, END };

    enum direction : std::uint16_t { FORWARD, BACKWARD, LEFT, RIGHT,
            ROTATE_LEFT, ROTATE_RIGHT};
    
    Protocol() = default;
    explicit Protocol(int id);
    explicit Protocol(int user_id, int map_id);
    explicit Protocol(int id, Protocol::direction direction);
    Protocol::action getAction();
    Protocol::direction getDirection();
    void moveInDirection(Protocol::direction direction);
    void serialize();
    void unSerialize();
    int getId();
    int getId2();
    void setAction(Protocol::action action);
    ~Protocol();
private:
    Protocol::action _action;
    std::uint16_t id;
    Protocol::direction _direction;
    std::uint16_t damage;
};

#endif
