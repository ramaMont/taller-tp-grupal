#ifndef __WALL__
#define __WALL__

#include "Cl_Posicionable.h"

class Wall : public Cl_Posicionable{

public:
    explicit Wall(Coordinates posicion);

	Intersected_object colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

	virtual void draw(int ray, float distance, int number_line_texture,bool wall_side_y) = 0;

};

class Wall_greystone final : public Wall{

public:
	Wall_greystone(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;
};

class Wall_bluestone final : public Wall{

public:
	Wall_bluestone(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};

class Wall_purplestone final : public Wall{

public:
	Wall_purplestone(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};


class Wall_colorstone final : public Wall{

public:
	Wall_colorstone(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};

class Wall_eagle final : public Wall{

public:
	Wall_eagle(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};

class Wall_mossy final : public Wall{

public:
	Wall_mossy(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};


class Wall_redbrick final : public Wall{

public:
	Wall_redbrick(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};

class Wall_wood final : public Wall{

public:
	Wall_wood(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};


#endif
