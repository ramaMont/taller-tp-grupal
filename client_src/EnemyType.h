#ifndef __ENEMY_TYPE__
#define __ENEMY_TYPE__

class Texture;

//Los distintos tipos de enemigos
class EnemyType{
protected:
	Texture *texture_drawer;
	int frames_shooting;
public:
	EnemyType(Texture *texture_drawer);
	void shoot();
	void updateShooting();
    virtual void callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) = 0;
    virtual ~EnemyType(){};
};

class Dog : public EnemyType{
public:
	Dog(Texture *texture_drawer);
	virtual void callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	~Dog();
};

class Guard : public EnemyType{
public:
	Guard(Texture *texture_drawer);
	virtual void callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	~Guard();
};

class SS : public EnemyType{
public:
	SS(Texture *texture_drawer);
	virtual void callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	~SS();
};

class Officer : public EnemyType{
public:
	Officer(Texture *texture_drawer);
	virtual void callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	~Officer();
};

class Mutant : public EnemyType{
public:
	Mutant(Texture *texture_drawer);
	virtual void callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	~Mutant();
};


#endif
