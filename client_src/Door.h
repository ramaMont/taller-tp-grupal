#ifndef __DOOR__
#define __DOOR__

#include <string>
#include <Character.h>
#include "Posicionable.h"
class Ray;

class Door : public Posicionable{
private:
	int current_frame;
	std::string state;
	Character* character;

public:
    explicit Door(Coordinates posicion);

    void add(Character* character) override;

    void remove() override;

    void spottedEnemy();

	void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

	void setState(std::string new_state);

	void updateFrame(); 

	void opening();

	int getLimitWall();

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y);

};

#endif
