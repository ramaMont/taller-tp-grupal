#ifndef __PROTOCOL__
#define __PROTOCOL__

#include <cstdint>
#include <tuple>

class Protocol {
public:
    enum action : std::uint16_t { MOVE, SHOOT, LOAD, PICKUP, OPEN, OPENING,
            CLOSING, CLOSE, SHOOTED, ADDKILL, ADDPOINTS, ENDGAME, SET_ID,
            JOIN_GAME, CREATE_GAME, OK, ERROR, ADD_PLAYER, LAUNCH_GAME, BEGIN,
            END, NONE, REMOVE, RESURRECT, DIE, CONFIG, END_GAME_KILLS,
            END_GAME_POINTS, END_GAME_BULLETS, UPDATE_HEALTH, UPDATE_BULLETS,
            SWITCH_GUN, THROW, WINNER, OPEN_PASSAGE };

    enum direction : std::uint16_t { FORWARD, BACKWARD, LEFT, RIGHT,
            ROTATE_LEFT, ROTATE_RIGHT, STAY};

    struct __attribute__((packed)) NetworkProtocol {
        Protocol::action _action;
        std::uint16_t id;
        Protocol::direction _direction;
        std::uint16_t damage;
        std::uint16_t _game_id;
        float _float_aux;
    };
    
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
    Protocol::NetworkProtocol serialize() const;
    void unSerialize(const Protocol::NetworkProtocol& received_protocol);
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
    void setDamage(int danio);
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
