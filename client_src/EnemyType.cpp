#include "EnemyType.h"

#include "texture.h"


EnemyType::EnemyType(Texture *texture_drawer, CharacterType enemy_type): 
	texture_drawer(texture_drawer),frames_shooting(0) , enemy_type(enemy_type){}


CharacterType EnemyType::getType(){
	return enemy_type;
}

void EnemyType::updateShooting(){
	if(frames_shooting>0){//si es mayor que 0, estoy disparando
		frames_shooting++;
		if(frames_shooting>MAX_SHOOTING_FRAMES){
			frames_shooting=0;
		}
	}
}
//---------------------------------------------------------------------------
Dog::Dog(Texture *texture_drawer):EnemyType(texture_drawer,dog) {}
void Dog::callDrawer(int first_x_pixel,int first_number_line_texture,\
								int last_x_pixel, int last_number_texture,\
									float distance_player_plane, int texture, int state){
	bool is_shooting = frames_shooting!=0;
	texture_drawer->showDog(first_x_pixel,
			first_number_line_texture,last_x_pixel,
				last_number_texture,distance_player_plane,
									texture,state%3,is_shooting);
}
void Dog::shoot(SoundPlayer& soundPlayer, float distance){
	frames_shooting++;
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::DOG_BITE,
		distance);	
}
Dog::~Dog(){}
//---------------------------------------------------------------------------

Guard::Guard(Texture *texture_drawer):EnemyType(texture_drawer,guard){}
void Guard::callDrawer(int first_x_pixel,int first_number_line_texture,\
								int last_x_pixel, int last_number_texture,\
									float distance_player_plane, int texture, int state){
	bool is_shooting = frames_shooting!=0;
	texture_drawer->showGuard(first_x_pixel,
			first_number_line_texture,last_x_pixel,
				last_number_texture,distance_player_plane,
									texture,state%4,is_shooting);
}
void Guard::shoot(SoundPlayer& soundPlayer, float distance){
	frames_shooting++;
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::PISTOL_SHOOT,
		distance);	
}
Guard::~Guard(){}
//---------------------------------------------------------------------------

SS::SS(Texture *texture_drawer):EnemyType(texture_drawer,ss){}
void SS::callDrawer(int first_x_pixel,int first_number_line_texture,\
								int last_x_pixel, int last_number_texture,\
									float distance_player_plane, int texture, int state){
	bool is_shooting = frames_shooting!=0;
	texture_drawer->showSs(first_x_pixel,
			first_number_line_texture,last_x_pixel,
				last_number_texture,distance_player_plane,
									texture,state%4,is_shooting);
}
void SS::shoot(SoundPlayer& soundPlayer, float distance){
	frames_shooting++;
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::MACHINEGUN_SHOOT,
		distance);	
}
SS::~SS(){}
//---------------------------------------------------------------------------

Officer::Officer(Texture *texture_drawer):EnemyType(texture_drawer,officer){}
void Officer::callDrawer(int first_x_pixel,int first_number_line_texture,\
								int last_x_pixel, int last_number_texture,\
									float distance_player_plane, int texture, int state){
	bool is_shooting = frames_shooting!=0;
	texture_drawer->showOfficer(first_x_pixel,
			first_number_line_texture,last_x_pixel,
				last_number_texture,distance_player_plane,
								texture,state%4,is_shooting);
}
void Officer::shoot(SoundPlayer& soundPlayer, float distance){
	frames_shooting++;
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::CHAINGUN_SHOOT,
		distance);	
}
Officer::~Officer(){}
//---------------------------------------------------------------------------

Mutant::Mutant(Texture *texture_drawer):EnemyType(texture_drawer,mutant) {}
void Mutant::callDrawer(int first_x_pixel,int first_number_line_texture,\
								int last_x_pixel, int last_number_texture,\
									float distance_player_plane, int texture, int state){
	bool is_shooting = frames_shooting!=0;
	texture_drawer->showMutant(first_x_pixel,
		first_number_line_texture, last_x_pixel,
			last_number_texture,distance_player_plane,
							texture,state%4,is_shooting);
}
void Mutant::shoot(SoundPlayer& soundPlayer, float distance){
	frames_shooting++;
	
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::ROCKET_LAUNCHER,
		distance);	
}
Mutant::~Mutant(){}
