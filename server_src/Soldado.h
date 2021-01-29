#ifndef __SOLDADO__
#define __SOLDADO__

class Arma;
class Cuchillo;
class Pistola;
class Ametralladora;
class CanionDeCadena;
class Lanzacohetes;
#include "Arma.h"
#include <set>
#include <vector>
#include <atomic>

class Soldado {
	protected:
	int &balas;

    public:
    Soldado(int &balas): balas(balas) { }
	virtual int disparar(Player *jugador, std::map<int, Player*>&) = 0;
	virtual void soltarArma(Player *jugador) = 0;
	virtual bool estaListo() = 0;
	virtual int numeroArma() const = 0;
    void obtenerEnemigosCercanos(std::map<int, Player*>& enemigos,
       Player* jugador, std::set<std::pair<int, Player*>>& jugadores);
};



class Perro: public Soldado {
	private:
	Cuchillo cuchillo;
	
	public:
	Perro(int& n);
	int disparar(Player *jugador, std::map<int, Player*>&) override;
	void soltarArma(Player *jugador) override;
	bool estaListo() override;
	int numeroArma() const;
};


class Guardia: public Soldado {
	private:
	Pistola pistola;
	
	public:
	Guardia(int& balas);
	int disparar(Player *jugador, std::map<int, Player*>&) override;
	void soltarArma(Player *jugador) override;
	bool estaListo() override;
	int numeroArma() const;
};


class SS: public Soldado {
	private:
	Ametralladora ametralladora;
	bool tieneArma;
	
	public:
	SS(int &balas);
	bool agregarArma(Ametralladora *ametralladora);
	int disparar(Player *jugador, std::map<int, Player*>&) override;	
	void soltarArma(Player *jugador) override;
	bool estaListo() override;
	int numeroArma() const;
};


class Oficial: public Soldado {
	private:
	CanionDeCadena canion;
	bool tieneArma;
	
	public:
	Oficial(int &balas);
	bool agregarArma(CanionDeCadena *canion);
	int disparar(Player *jugador, std::map<int, Player*>&) override;
	void soltarArma(Player *jugador) override;
	bool estaListo() override;
	int numeroArma() const;
};


class Mutante: public Soldado {
	private:
	Lanzacohetes lanzacohetes;
	bool tieneArma;
	
	public:
	Mutante(int &balas);
	bool agregarArma(Lanzacohetes *lanzacohetes);
	int disparar(Player *jugador, std::map<int, Player*>&) override;	
	void soltarArma(Player *jugador) override;
	bool estaListo() override;
	int numeroArma() const;
};



class EstadoSoldado {
	private:
	Player *jugador;
	Soldado *soldado;
	Perro perro;
	Guardia guardia;
	SS ss;
	Oficial oficial;
	Mutante mutante;
	Soldado *soldado_anterior;
	std::atomic<int> arma_actual;
	
	public:
	explicit EstadoSoldado(Player *jugador, int& balas);
	int armaActual() const;
	bool agregarArma(Arma* arma);
	void cambiarArma(int numero_arma);
	void soltarArma();
	int disparar(std::map<int, Player*>& enemigos);
	void recargarBalas();
};


#endif
