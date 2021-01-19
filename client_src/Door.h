#ifndef __DOOR__
#define __DOOR__

#include <string>
#include "Posicionable.h"
class Ray;

class Door : public Posicionable{
private:
	int current_frame;
	std::string state;

public:
    explicit Door(Coordinates posicion);

	void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

	bool is_opening();

	void update_frame(); 

	void opening();

	int get_limit_wall();

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y);

};

#endif
