#ifndef __WALL__
#define __WALL__

#include <Posicionable.h>
#include "ray.h"

class Wall : public Posicionable{
public:
    explicit Wall(Coordinates posicion);

    //Pre:-
    // Le indica al rayo que colisionó con una pared
	void colisioned(Ray* ray,Coordinates coordinates_map,\
										bool first_triangle);

    //Pre:-
    // Llama a su respectivo dibujador de texturas
	virtual void draw(int ray, float distance, \
		int number_line_texture,bool wall_side_y) = 0;
};

class WallGreystone final : public Wall{
public:
	explicit WallGreystone(Coordinates posicion);
	void draw(int ray, float distance, \
		int number_line_texture,bool wall_side_y) override;
};

class WallBluestone final : public Wall{
public:
	explicit WallBluestone(Coordinates posicion);
	void draw(int ray, float distance, \
		int number_line_texture,bool wall_side_y) override;
};

class WallPurplestone final : public Wall{
public:
	explicit WallPurplestone(Coordinates posicion);
	void draw(int ray, float distance, \
		int number_line_texture,bool wall_side_y) override;
};


class WallColorstone final : public Wall{
public:
	explicit WallColorstone(Coordinates posicion);
	void draw(int ray, float distance, \
		int number_line_texture,bool wall_side_y) override;
};

class WallEagle final : public Wall{
public:
	explicit WallEagle(Coordinates posicion);
	void draw(int ray, float distance, \
		int number_line_texture,bool wall_side_y) override;
};

class WallMossy final : public Wall{
public:
	explicit WallMossy(Coordinates posicion);
	void draw(int ray, float distance, \
		int number_line_texture,bool wall_side_y) override;
};


class WallRedbrick final : public Wall{
public:
	explicit WallRedbrick(Coordinates posicion);
	void draw(int ray, float distance, \
		int number_line_texture,bool wall_side_y) override;
};

class WallWood final : public Wall{
public:
	explicit WallWood(Coordinates posicion);
	void draw(int ray, float distance, \
		int number_line_texture,bool wall_side_y) override;
};

#endif
