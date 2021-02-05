#include "EnemyType.h"

#include "texture.h"


EnemyType::EnemyType(Texture *texture_drawer, CharacterType enemy_type): texture_drawer(texture_drawer),frames_shooting(0) , enemy_type(enemy_type){}


CharacterType EnemyType::getType(){
	return enemy_type;
}

void EnemyType::updateShooting(){
	if(frames_shooting>0){//si es mayor que 0, estoy disparando
		frames_shooting++;
		if(frames_shooting>MAX_SHOOTING_FRAMES){//Si es 0, terminé de disparar(lo muestro 10 frames nomas)
			frames_shooting=0;
		}
	}
}
//--------------------------------------------------------------------------------------------------------
Dog::Dog(Texture *texture_drawer):EnemyType(texture_drawer,dog) {}
void Dog::callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->showDog(texture,frame%3,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->showDog(texture,frame%3,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
void Dog::shoot(SoundPlayer& soundPlayer, float distance){
	frames_shooting++;
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::DOG_BITE,
		distance);	
}
Dog::~Dog(){}
//--------------------------------------------------------------------------------------------------------

Guard::Guard(Texture *texture_drawer):EnemyType(texture_drawer,guard){}
void Guard::callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->showGuard(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->showGuard(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
void Guard::shoot(SoundPlayer& soundPlayer, float distance){
	frames_shooting++;
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::PISTOL_SHOOT,
		distance);	
}
Guard::~Guard(){}
//--------------------------------------------------------------------------------------------------------

SS::SS(Texture *texture_drawer):EnemyType(texture_drawer,ss){}
void SS::callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->showSs(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->showSs(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
void SS::shoot(SoundPlayer& soundPlayer, float distance){
	frames_shooting++;
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::MACHINEGUN_SHOOT,
		distance);	
}
SS::~SS(){}
//--------------------------------------------------------------------------------------------------------

Officer::Officer(Texture *texture_drawer):EnemyType(texture_drawer,officer){}
void Officer::callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->showOfficer(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->showOfficer(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
void Officer::shoot(SoundPlayer& soundPlayer, float distance){
	frames_shooting++;
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::CHAINGUN_SHOOT,
		distance);	
}
Officer::~Officer(){}
//--------------------------------------------------------------------------------------------------------

Mutant::Mutant(Texture *texture_drawer):EnemyType(texture_drawer,mutant) {}
void Mutant::callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->showMutant(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->showMutant(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
void Mutant::shoot(SoundPlayer& soundPlayer, float distance){
	frames_shooting++;
	
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::ROCKET_LAUNCHER,
		distance);	
}
Mutant::~Mutant(){}
