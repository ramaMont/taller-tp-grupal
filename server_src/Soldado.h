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

class Soldado {
	protected:
	int &balas;

    public:
    Soldado(int &balas): balas(balas) { }
	virtual void disparar(Player *jugador, std::map<int, Player*>&) = 0;
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
	void disparar(Player *jugador, std::map<int, Player*>&) override;
	void soltarArma(Player *jugador) override;
	bool estaListo() override;
	int numeroArma() const;
};


class Guardia: public Soldado {
	private:
	Pistola pistola;
	
	public:
	Guardia(int& balas);
	void disparar(Player *jugador, std::map<int, Player*>&) override;
	void soltarArma(Player *jugador) override;
	bool estaListo() override;
	int numeroArma() const;
};


class SS: public Soldado {
	private:
	Ametralladora *ametralladora;
	
	public:
	SS(int &balas);
	bool agregarArma(Ametralladora *ametralladora);
	void disparar(Player *jugador, std::map<int, Player*>&) override;	
	void soltarArma(Player *jugador) override;
	bool estaListo() override;
	int numeroArma() const;
};


class Oficial: public Soldado {
	private:
	CanionDeCadena *canion;
	
	public:
	Oficial(int &balas);
	bool agregarArma(CanionDeCadena *canion);
	void disparar(Player *jugador, std::map<int, Player*>&) override;
	void soltarArma(Player *jugador) override;
	bool estaListo() override;
	int numeroArma() const;
};


class Mutante: public Soldado {
	private:
	Lanzacohetes *lanzacohetes;
	
	public:
	Mutante(int &balas);
	bool agregarArma(Lanzacohetes *lanzacohetes);
	void disparar(Player *jugador, std::map<int, Player*>&) override;	
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
	
	public:
	explicit EstadoSoldado(Player *jugador, int& balas);
	int armaActual() const;
	bool agregarArma(Arma* arma);
	void cambiarArma(int numero_arma);
	void soltarArma();
	void disparar(std::map<int, Player*>& enemigos);
	void recargarBalas();
};


#endif
