#ifndef __GUN_TYPE__
#define __GUN_TYPE__

#include <thread>
#include <chrono>
#include <iostream>
#include <sys/time.h>
#include "SoundPlayer.h"

class Texture;

//Los distintos tipos de armas que puede tener el jugador
class GunType{
protected:
	Texture *texture_drawer;
	time_t fire_rate;
public:
	GunType(Texture *texture_drawer,time_t fire_rate);

    //Pre:-
    // Llamo a su respectivo metodo encargadao de dibujar	
    virtual void callDrawer(int frame) = 0;

    //Pre:-
    // Devuelve la frecuencia de disparo del arma
    time_t getFireRate();
	virtual void playWeaponSound(SoundPlayer& soundPlayer, float distance) = 0;
    virtual ~GunType(){};
};

class Knife : public GunType{
public:
	Knife(Texture *texture_drawer);
	virtual void callDrawer(int frame) override;
	virtual void playWeaponSound(SoundPlayer& soundPlayer, 
		float distance) override;
	~Knife();
};

class Gun : public GunType{
public:
	Gun(Texture *texture_drawer);
	virtual void callDrawer(int frame) override;
	virtual void playWeaponSound(SoundPlayer& soundPlayer, 
		float distance) override;
	~Gun();
};

class MachineGun : public GunType{
public:
	MachineGun(Texture *texture_drawer);
	virtual void callDrawer(int frame) override;
	virtual void playWeaponSound(SoundPlayer& soundPlayer, 
		float distance) override;
	~MachineGun();
};

class ChainGun : public GunType{
public:
	ChainGun(Texture *texture_drawer);
	virtual void callDrawer(int frame) override;
	virtual void playWeaponSound(SoundPlayer& soundPlayer, 
		float distance) override;
	~ChainGun();
};

#endif
