#ifndef __ENEMY_TYPE__
#define __ENEMY_TYPE__

class Texture;
#include "SoundPlayer.h"
#include "CharacterValues.h"

const int MAX_SHOOTING_FRAMES = 10;

//Los distintos tipos de enemigos
class EnemyType{
protected:
	Texture *texture_drawer;
	int frames_shooting;
	CharacterType enemy_type;
public:
	EnemyType(Texture *texture_drawer, CharacterType enemy_type);

    //Pre:-
    // aumento en 1 el frame de disparo	
	virtual void shoot(SoundPlayer& soundPlayer, float distance) = 0;

	CharacterType getType();

    //Pre:-
    // Actualiza el frame de disparo, si es 0 no estoy disparando, si es 10 terminé de disparar
	void updateShooting();

    //Pre:-
    // Llamo a su respectivo metodo encargadao de dibujar	
	virtual void callDrawer(int first_x_pixel,int first_number_line_texture,int last_x_pixel, int last_number_line_texture,float distance_player_plane, int texture, int state) = 0;
    virtual ~EnemyType(){};
};

class Dog : public EnemyType{
public:
	Dog(Texture *texture_drawer);
	virtual void callDrawer(int first_x_pixel,int first_number_line_texture,int last_x_pixel, int last_number_line_texture,float distance_player_plane, int texture, int state) override;
	virtual void shoot(SoundPlayer& soundPlayer, float distance) override;
	~Dog();
};

class Guard : public EnemyType{
public:
	Guard(Texture *texture_drawer);
	virtual void callDrawer(int first_x_pixel,int first_number_line_texture,int last_x_pixel, int last_number_line_texture,float distance_player_plane, int texture, int state) override;
	virtual void shoot(SoundPlayer& soundPlayer, float distance) override;
	~Guard();
};

class SS : public EnemyType{
public:
	SS(Texture *texture_drawer);
	virtual void callDrawer(int first_x_pixel,int first_number_line_texture,int last_x_pixel, int last_number_line_texture,float distance_player_plane, int texture, int state) override;
	virtual void shoot(SoundPlayer& soundPlayer, float distance) override;
	~SS();
};

class Officer : public EnemyType{
public:
	Officer(Texture *texture_drawer);
	virtual void callDrawer(int first_x_pixel,int first_number_line_texture,int last_x_pixel, int last_number_line_texture,float distance_player_plane, int texture, int state) override;
	virtual void shoot(SoundPlayer& soundPlayer, float distance) override;
	~Officer();
};

class Mutant : public EnemyType{
public:
	Mutant(Texture *texture_drawer);
	virtual void callDrawer(int first_x_pixel,int first_number_line_texture,int last_x_pixel, int last_number_line_texture,float distance_player_plane, int texture, int state) override;
	virtual void shoot(SoundPlayer& soundPlayer, float distance) override;
	~Mutant();
};


#endif
