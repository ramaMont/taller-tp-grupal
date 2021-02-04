#include "GunType.h"

#include "texture.h"


GunType::GunType(Texture *texture_drawer, int frames_per_shot, bool allows_continuous_shooting): 
		texture_drawer(texture_drawer), frames_per_shot(frames_per_shot), allows_continuous_shooting(allows_continuous_shooting) {}

int GunType::getFramesPerShot(){
	return frames_per_shot;
}

bool GunType::allowsContinuousShooting(){
	return allows_continuous_shooting;
}
//--------------------------------------------------------------------------------------------------------
Knife::Knife(Texture *texture_drawer):GunType(texture_drawer, 30, false) {}	//frecuencia. 1 segundo (30 frames)
void Knife::callDrawer(int frame){
	texture_drawer->showKnife(frame/7);
}
void Knife::playWeaponSound(SoundPlayer& soundPlayer, float distance){
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::DOG_BITE, distance);
}
Knife::~Knife(){}
//--------------------------------------------------------------------------------------------------------

Gun::Gun(Texture *texture_drawer):GunType(texture_drawer, 30, false){}		//frecuencia. 1 segundo (30 frames)
void Gun::callDrawer(int frame){
	texture_drawer->showGun(frame/7);
}
void Gun::playWeaponSound(SoundPlayer& soundPlayer, float distance){
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::PISTOL_SHOOT, distance);
}
Gun::~Gun(){}
//--------------------------------------------------------------------------------------------------------

MachineGun::MachineGun(Texture *texture_drawer):GunType(texture_drawer, 9, true){} //frecuencia. 0.3 segundos (9 frames)
void MachineGun::callDrawer(int frame){
	texture_drawer->showMachineGun(frame/2);
}
void MachineGun::playWeaponSound(SoundPlayer& soundPlayer, float distance){
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::MACHINEGUN_SHOOT, distance);	
}
MachineGun::~MachineGun(){}
//--------------------------------------------------------------------------------------------------------

ChainGun::ChainGun(Texture *texture_drawer):GunType(texture_drawer, 3, true){} //frecuencia. 0.1 segundos (3 frames)
void ChainGun::callDrawer(int frame){
	texture_drawer->showChainGun(frame);
}
void ChainGun::playWeaponSound(SoundPlayer& soundPlayer, float distance){
	soundPlayer.playSoundAtDistance(SoundPlayer::sound_type::CHAINGUN_SHOOT, distance);	
}
ChainGun::~ChainGun(){}
