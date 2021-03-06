#ifndef TEXTURE_H
#define TEXTURE_H

#include "window.h"
#include <vector>
#include <map>
#include <string>
#include <utility>

#include <SDL2/SDL_ttf.h>

enum Colors { black, white};

class Texture {
private:
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> wall_textures;
    std::map<int,SDL_Texture*> sprites;
    std::vector<SDL_Texture*> enemies;
    std::vector<SDL_Texture*> shooting_effect;
    std::vector<SDL_Texture*> bar_guns;
    SDL_Texture* rocket_explosion;
    SDL_Texture* face_health;
    SDL_Texture* guns;
    SDL_Texture* door;
    SDL_Texture* key_door;
    SDL_Texture* dead_bar;
    SDL_Texture* life_bar;
    SDL_Texture* key;
    SDL_Texture* ending_background;
    int info_bar_height;
    int height;
    int width;
    SDL_Rect showableTexture;
    TTF_Font* wolfensteinFont;

    std::string texture_path;

    // Carga todas las texturas de paredes
    void addWallTexture(std::string new_texture);

    // Carga todas las texturas de sprites
    void addSpriteTexture(std::string new_texture);

    // Carga todas las texturas de efectos de disparo
    void addShootingEffectTexture(std::string new_texture);

    // Carga todas las texturas de enemigos
    void addEnemyTexture(std::string new_texture);

    // Carga todas las texturas de enemigos muertos
    void addDeadEnemyTexture(std::string new_texture);

    // Carga todas las texturas de las armas
    void addTexture(SDL_Texture** texture,std::string new_texture,int r, int g, int b);

    // Carga todas las texturas de la barra de vidas
    void addLifeBarTexture(SDL_Texture** texture,std::string new_texture);

    // Carga las caras de la vida
    void addFaceHealth();

    void addBarGuns(std::string new_texture);

    void addEndingBackground();
    
    void addKeyTexture();

    /*Grafica los pixeles solicitados de la 
    textura recibida en la posicion recibida*/
    void genericShow(SDL_Texture* texture, int first_x_pixel, \
    				int cant_x_pixels, int first_y_pixel, int cant_y_pixel,\
        			int windows_x_pos, int length_x, int windows_y_pos, int lenght_y);

    /*configura los parametros y llama al 
    generic_show para graficar toda el arma*/
    void showWeapon(int frame_gun, int current_gun);

    // Muestra el texto de la barra de estado
    void showText(Colors selected_color, std::string text, \
    				int letter_width, int letter_height, int x_pos, int y_pos);

    /*configura los parametros y llama al generic_
    show para graficar una unica linea de pixeles de la pared*/
    void showWall(SDL_Texture* texture,int x_pixel, \
    				float distance_player_plane, int number_line_texture);

    /*configura los parametros y llama al generic_show
     para graficar la parte visible del enemigo*/
    void showEnemy(int num_enemy,int first_x_pixel, \
    				int first_number_line_texture,int last_x_pixel, \
    				int last_number_line_texture,float distance_player_plane, \
    				int frame, int state, bool shooting);

    void showFaceHealth(int portion_health);
    
    void showKeys(bool has_key_1, bool has_key_2);

    void showRanking(std::vector<std::pair<int,int>> &ordered_players_kills, \
    					std::vector<std::pair<int,int>> &ordered_players_points, \
    					std::vector<std::pair<int,int>> &ordered_players_bullets);

    void destoyVectorTextures(std::vector<SDL_Texture*> &texture_vector);

public:
    explicit Texture(const Window& window);

    Texture(const Texture&) = delete;
    Texture(Texture&& other) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&& other);

    //Muestra la barra de vida
    void showLifeBar(int id, unsigned int score, int lives, int health, \
    						int portion_health, int ammo, bool has_key_1, bool has_key_2);


    //Muestra la barra cuando está muerto
    void showDeadBar(int id, unsigned int score);

    /*configura los parametros y llama al 
    generic_show para graficar la parte visible del sprite*/
    void showSprite(int first_x_pixel,int first_number_line_texture, \
    						int last_x_pixel, int last_number_line_texture, \
    						float distance_player_plane,int texture);


    /*configura los parametros y llama al 
    generic_show para graficar la explosion del misil*/
    void showExplosion(int first_x_pixel,int first_number_line_texture, \
                            int last_x_pixel, int last_number_line_texture, \
                            float distance_player_plane,int texture);

    //llama al show enemy con la textura del perro
	void showDog(int first_x_pixel,int first_number_line_texture, \
							int last_x_pixel, int last_number_line_texture, \
							float distance_player_plane,int frame, int state, bool shooting);

    //llama al show enemy con la textura del guardia
	void showGuard(int first_x_pixel,int first_number_line_texture, \
							int last_x_pixel, int last_number_line_texture, \
							float distance_player_plane,int frame, int state, bool shooting);

    //llama al show enemy con la textura del oficial
	void showOfficer(int first_x_pixel,int first_number_line_texture, \
							int last_x_pixel, int last_number_line_texture, \
							float distance_player_plane,int frame, int state, bool shooting);

    //llama al show enemy con la textura del ss
	void showSs(int first_x_pixel,int first_number_line_texture, \
							int last_x_pixel, int last_number_line_texture, \
							float distance_player_plane,int frame, int state, bool shooting);

    //llama al show enemy con la textura del mutante
	void showMutant(int first_x_pixel,int first_number_line_texture, \
							int last_x_pixel, int last_number_line_texture, \
							float distance_player_plane,int frame, int state, bool shooting);

    //llama al show wall con la textura de la pared gris
	void showWallGreystone(int pos_x,float distance_player_plane, \
							int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared azul
	void showWallBluestone(int pos_x,float distance_player_plane, \
							int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared purplestone
	void showWallPurplestone(int pos_x,float distance_player_plane, \
							int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared de colores
	void showWallColorstone(int pos_x,float distance_player_plane, \
							int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared agila
	void showWallEagle(int pos_x,float distance_player_plane, \
							int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared mohosa
	void showWallMossy(int pos_x,float distance_player_plane, \
							int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared de ladrillo
	void showWallRedbrick(int pos_x,float distance_player_plane, \
							int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared de madera
	void showWallWood(int pos_x,float distance_player_plane,\
							int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la puerta azul
    void showDoor(int x_pixel,float distance_player_plane, \
    						int number_line_texture);

    //llama al show wall con la textura de la puerta con llave
    void showKeyDoor(int x_pixel,float distance_player_plane, \
                            int number_line_texture);

    //llama al show weapon con la textura del cuchillo
	void showKnife(int frame_gun);

    //llama al show weapon con la textura de la pistola
	void showGun(int frame_gun);

    //llama al show weapon con la textura de la ametralladora
	void showMachineGun(int frame_gun);

    //llama al show weapon con la textura del cañon de cadena
	void showChainGun(int frame_gun);

	//llama al show weapon con la textura del lanza misiles
	void showRocketLauncher(int frame_gun);

    void showWinningScreen( \
    	std::vector<std::pair<int,int>> &ordered_players_kills, \
    	std::vector<std::pair<int,int>> &ordered_players_points, \
    	std::vector<std::pair<int,int>> &ordered_players_bullets);

    void showLoosingScreen(int winnder_id, \
    	std::vector<std::pair<int,int>> &ordered_players_kills, \
    	std::vector<std::pair<int,int>> &ordered_players_points, \
    	std::vector<std::pair<int,int>> &ordered_players_bullets,\
        bool have_winner);

    void showDisconnectedScreen();

    // Destruye las texturas iniciadas
    ~Texture();
};

#endif
