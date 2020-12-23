#ifndef __WALL__
#define __WALL__

#include "Posicionable.h"

class Wall : public Posicionable{

public:
    explicit Wall(Texture &texture_drawer,Coordinates posicion);

	Intersected_object colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

	virtual void draw(int ray, float distance, int number_line_texture,bool wall_side_y) = 0;

};

class Wall_greystone final : public Wall{

public:
	Wall_greystone(Texture &texture_drawer,Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;
};

class Wall_bluestone final : public Wall{

public:
	Wall_bluestone(Texture &texture_drawer,Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};

class Wall_purplestone final : public Wall{

public:
	Wall_purplestone(Texture &texture_drawer,Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};


class Wall_colorstone final : public Wall{

public:
	Wall_colorstone(Texture &texture_drawer,Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};

class Wall_eagle final : public Wall{

public:
	Wall_eagle(Texture &texture_drawer,Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};

class Wall_mossy final : public Wall{

public:
	Wall_mossy(Texture &texture_drawer,Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};


class Wall_redbrick final : public Wall{

public:
	Wall_redbrick(Texture &texture_drawer,Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};

class Wall_wood final : public Wall{

public:
	Wall_wood(Texture &texture_drawer,Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};


#endif
