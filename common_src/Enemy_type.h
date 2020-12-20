#ifndef __ENEMY_TYPE__
#define __ENEMY_TYPE__

class Texture;

class Enemy_type{
protected:
	Texture &texture_drawer;
public:
	Enemy_type(Texture &texture_drawer);
    virtual void call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) = 0;
    virtual ~Enemy_type(){};
};

class Dog : public Enemy_type{
public:
	Dog(Texture &texture_drawer);
	virtual void call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	~Dog();
};

class Guard : public Enemy_type{
public:
	Guard(Texture &texture_drawer);
	virtual void call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	~Guard();
};

class SS : public Enemy_type{
public:
	SS(Texture &texture_drawer);
	virtual void call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	~SS();
};

class Officer : public Enemy_type{
public:
	Officer(Texture &texture_drawer);
	virtual void call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	~Officer();
};

class Mutant : public Enemy_type{
public:
	Mutant(Texture &texture_drawer);
	virtual void call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame) override;
	~Mutant();
};


#endif
