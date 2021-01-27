#ifndef __PROTOCOL__
#define __PROTOCOL__

#include <cstdint>
#include <tuple>

struct __attribute__((packed)) Protocol {
public:
    enum action : std::uint16_t { MOVE, SHOOT, LOAD, PICKUP, OPEN, OPENING,
            CLOSING, CLOSE, SHOOTED, ADDKILL, ADDPOINTS, ENDGAME, SET_ID,
            JOIN_GAME, CREATE_GAME, OK, ERROR, ADD_PLAYER, LAUNCH_GAME, BEGIN,
            END, NONE, REMOVE, RESURRECT, DIE, CONFIG };

    enum direction : std::uint16_t { FORWARD, BACKWARD, LEFT, RIGHT,
            ROTATE_LEFT, ROTATE_RIGHT, STAY};
    
    Protocol();
    explicit Protocol(int id);
    explicit Protocol(int user_id, int map_id);
    explicit Protocol(int user_id, int danio, Protocol::action action);
    explicit Protocol(int user_id, int map_id, int game_id);
    explicit Protocol(int id, Protocol::direction direction);
    explicit Protocol(int config_number, float config_value);
    explicit Protocol(Protocol::action action, int user_id, Protocol::direction direction, int map_id, int pos_x, int pos_y);
    Protocol::action getAction();
    Protocol::direction getDirection();
    void moveInDirection(Protocol::direction direction);
    void serialize();
    void unSerialize();
    int getId();
    int getMapId();
    int getUserId();
    int getGameId();
    int getDamage();
    int getConfId();
    int getBotsCty();
    float getConfiguration();
    std::tuple<int, int> getPosition() const;
    void setAction(Protocol::action action);
    ~Protocol();
private:
    Protocol::action _action;
    std::uint16_t id;
    Protocol::direction _direction;
    std::uint16_t damage;
    std::uint16_t _game_id;
    float _float_aux;
};

#endif
