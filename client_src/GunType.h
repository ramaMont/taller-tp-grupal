#ifndef __GUN_TYPE__
#define __GUN_TYPE__

#include <thread>
#include <chrono>
#include <iostream>
#include <sys/time.h>
#include "SoundPlayer.h"

class Texture;
#include "CharacterValues.h"
//Los distintos tipos de armas que puede tener el jugador
class GunType{
protected:
	Texture *texture_drawer;
	int frames_per_shot;
	bool allows_continuous_shooting;
	CharacterType enemy_type;

public:
	explicit GunType(Texture *texture_drawer, int frames_per_shot, 
		bool allows_continuous_shooting, CharacterType enemy_type);

	CharacterType getType();

    //Pre:-
    // Llamo a su respectivo metodo encargadao de dibujar	
    virtual void callDrawer(int frame) = 0;

    //Pre:-
    // Devuelve la cantidad de frames que dura el disparo del arma
    int getFramesPerShot();

    bool allowsContinuousShooting();

	virtual void playWeaponSound(SoundPlayer& soundPlayer, float distance) = 0;
    virtual ~GunType(){}
};

class Knife : public GunType{
public:
	explicit Knife(Texture *texture_drawer);
	virtual void callDrawer(int frame) override;
	virtual void playWeaponSound(SoundPlayer& soundPlayer, 
		float distance) override;
	~Knife();
};

class Gun : public GunType{
public:
	explicit Gun(Texture *texture_drawer);
	virtual void callDrawer(int frame) override;
	virtual void playWeaponSound(SoundPlayer& soundPlayer, 
		float distance) override;
	~Gun();
};

class MachineGun : public GunType{
public:
	explicit MachineGun(Texture *texture_drawer);
	virtual void callDrawer(int frame) override;
	virtual void playWeaponSound(SoundPlayer& soundPlayer, 
		float distance) override;
	~MachineGun();
};

class ChainGun : public GunType{
public:
	explicit ChainGun(Texture *texture_drawer);
	virtual void callDrawer(int frame) override;
	virtual void playWeaponSound(SoundPlayer& soundPlayer, 
		float distance) override;
	~ChainGun();
};

class RocketLauncher : public GunType{
public:
	explicit RocketLauncher(Texture *texture_drawer);
	virtual void callDrawer(int frame) override;
	virtual void playWeaponSound(SoundPlayer& soundPlayer, 
		float distance) override;
	~RocketLauncher();
};

#endif
