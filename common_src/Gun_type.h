#ifndef __GUN_TYPE__
#define __GUN_TYPE__

class Texture;

//Los distintos tipos de armas que puede tener el jugador
class Gun_type{
protected:
	Texture &texture_drawer;
public:
	Gun_type(Texture &texture_drawer);
    virtual void call_drawer(int frameframe) = 0;
    virtual ~Gun_type(){};
};

class Knife : public Gun_type{
public:
	Knife(Texture &texture_drawer);
	virtual void call_drawer(int frame) override;
	~Knife();
};

class Gun : public Gun_type{
public:
	Gun(Texture &texture_drawer);
	virtual void call_drawer(int frame) override;
	~Gun();
};

class Machine_gun : public Gun_type{
public:
	Machine_gun(Texture &texture_drawer);
	virtual void call_drawer(int frame) override;
	~Machine_gun();
};

class Chain_gun : public Gun_type{
public:
	Chain_gun(Texture &texture_drawer);
	virtual void call_drawer(int frame) override;
	~Chain_gun();
};

#endif
