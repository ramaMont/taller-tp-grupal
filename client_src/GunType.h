#ifndef __GUN_TYPE__
#define __GUN_TYPE__

#include <thread>
#include <chrono>
#include <iostream>
#include <sys/time.h>

class Texture;

//Los distintos tipos de armas que puede tener el jugador
class GunType{
protected:
	Texture *texture_drawer;
	time_t fire_rate;
public:
	GunType(Texture *texture_drawer,time_t fire_rate);
    virtual void callDrawer(int frame) = 0;
    time_t getFireRate();
    virtual ~GunType(){};
};

class Knife : public GunType{
public:
	Knife(Texture *texture_drawer);
	virtual void callDrawer(int frame) override;
	~Knife();
};

class Gun : public GunType{
public:
	Gun(Texture *texture_drawer);
	virtual void callDrawer(int frame) override;
	~Gun();
};

class MachineGun : public GunType{
public:
	MachineGun(Texture *texture_drawer);
	virtual void callDrawer(int frame) override;
	~MachineGun();
};

class ChainGun : public GunType{
public:
	ChainGun(Texture *texture_drawer);
	virtual void callDrawer(int frame) override;
	~ChainGun();
};

#endif
