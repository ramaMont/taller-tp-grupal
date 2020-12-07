#ifndef __PROTOCOL__
#define __PROTOCOL__

#include <cstdint>

struct __attribute__ ((packed)) Protocol {
public:
    enum action : std::uint16_t { MOVE, SHOOT, LOAD, PICKUP, OPEN,
            SHOOTED, ADDKILL, ADDPOINTS, ENDGAME };

    enum direction : std::uint16_t { FORWARD, BACKWARD, LEFT, RIGHT,
            ROTATE_LEFT, ROTATE_RIGHT};
    
    Protocol() = default;
    explicit Protocol(int id);
    explicit Protocol(int id, Protocol::direction direction);
    Protocol::action getAction();
    Protocol::direction getDirection();
    void moveInDirection(Protocol::direction direction);
    void serialize();
    void unSerialize();
    int getId();
    ~Protocol();
private:
    Protocol::action _action;
    std::uint16_t id;
    Protocol::direction _direction;
    std::uint16_t damage;
};

#endif
