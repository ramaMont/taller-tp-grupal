#ifndef __WALL__
#define __WALL__

#include <Posicionable.h>
#include "ray.h"

class Wall : public Posicionable{

public:
    explicit Wall(Coordinates posicion);

    //Pre:-
    // Le indica al rayo que colisionó con una pared
	void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

    //Pre:-
    // Llama a su respectivo dibujador de texturas
	virtual void draw(int ray, float distance, int number_line_texture,bool wall_side_y) = 0;

};

class WallGreystone final : public Wall{

public:
	WallGreystone(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;
};

class WallBluestone final : public Wall{

public:
	WallBluestone(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};

class WallPurplestone final : public Wall{

public:
	WallPurplestone(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};


class WallColorstone final : public Wall{

public:
	WallColorstone(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};

class WallEagle final : public Wall{

public:
	WallEagle(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};

class WallMossy final : public Wall{

public:
	WallMossy(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};


class WallRedbrick final : public Wall{

public:
	WallRedbrick(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};

class WallWood final : public Wall{

public:
	WallWood(Coordinates posicion);

	void draw(int ray, float distance, int number_line_texture,bool wall_side_y) override;

};


#endif
