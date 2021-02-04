#include "GunType.h"

#include "texture.h"


GunType::GunType(Texture *texture_drawer,time_t fire_rate): 
		texture_drawer(texture_drawer), fire_rate(fire_rate) {}
time_t GunType::getFireRate(){
	return fire_rate;
}
//--------------------------------------------------------------------------------------------------------
Knife::Knife(Texture *texture_drawer):GunType(texture_drawer, 1000/2) {}	//frecuencia. 0.5 segundos
void Knife::callDrawer(int frame){
	texture_drawer->showKnife(frame);
}
void Knife::playWeaponSound(SoundPlayer& soundPlayer, float distance){
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::DOG_BITE, distance);
}
Knife::~Knife(){}
//--------------------------------------------------------------------------------------------------------

Gun::Gun(Texture *texture_drawer):GunType(texture_drawer,1000/3){}		//frecuencia: 0.33 segundos
void Gun::callDrawer(int frame){
	texture_drawer->showGun(frame);
}
void Gun::playWeaponSound(SoundPlayer& soundPlayer, float distance){
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::PISTOL_SHOOT, distance);
}
Gun::~Gun(){}
//--------------------------------------------------------------------------------------------------------

MachineGun::MachineGun(Texture *texture_drawer):GunType(texture_drawer, 1000/0.3){} //frecuencia: 3.33 segundos
void MachineGun::callDrawer(int frame){
	texture_drawer->showMachineGun(frame);
}
void MachineGun::playWeaponSound(SoundPlayer& soundPlayer, float distance){
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::MACHINEGUN_SHOOT, distance);	
}
MachineGun::~MachineGun(){}
//--------------------------------------------------------------------------------------------------------

ChainGun::ChainGun(Texture *texture_drawer):GunType(texture_drawer, 1000/10){}
void ChainGun::callDrawer(int frame){
	texture_drawer->showChainGun(frame);
}
void ChainGun::playWeaponSound(SoundPlayer& soundPlayer, float distance){
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::CHAINGUN_SHOOT, distance);	
}
ChainGun::~ChainGun(){}
