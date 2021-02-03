#ifndef __ENEMY_TYPE__
#define __ENEMY_TYPE__

class Texture;
#include "SoundPlayer.h"

//Los distintos tipos de enemigos
class EnemyType{
protected:
	Texture *texture_drawer;
	int frames_shooting;
public:
	EnemyType(Texture *texture_drawer);

    //Pre:-
    // aumento en 1 el frame de disparo	
	virtual void shoot(SoundPlayer& soundPlayer, float distance) = 0;

    //Pre:-
    // Actualiza el frame de disparo, si es 0 no estoy disparando, si es 10 terminé de disparar
	void updateShooting();

    //Pre:-
    // Llamo a su respectivo metodo encargadao de dibujar	
    virtual void callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) = 0;
    virtual ~EnemyType(){};
};

class Dog : public EnemyType{
public:
	Dog(Texture *texture_drawer);
	virtual void callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	virtual void shoot(SoundPlayer& soundPlayer, float distance) override;
	~Dog();
};

class Guard : public EnemyType{
public:
	Guard(Texture *texture_drawer);
	virtual void callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	virtual void shoot(SoundPlayer& soundPlayer, float distance) override;
	~Guard();
};

class SS : public EnemyType{
public:
	SS(Texture *texture_drawer);
	virtual void callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	virtual void shoot(SoundPlayer& soundPlayer, float distance) override;
	~SS();
};

class Officer : public EnemyType{
public:
	Officer(Texture *texture_drawer);
	virtual void callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	virtual void shoot(SoundPlayer& soundPlayer, float distance) override;
	~Officer();
};

class Mutant : public EnemyType{
public:
	Mutant(Texture *texture_drawer);
	virtual void callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	virtual void shoot(SoundPlayer& soundPlayer, float distance) override;
	~Mutant();
};


#endif
