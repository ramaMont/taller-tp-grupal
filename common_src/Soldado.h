#ifndef __SOLDADO__
#define __SOLDADO__

#include <vector>
#include "Arma.h"

class Soldado {
	protected:
	int &balas;

    public:
    Soldado(int &balas): balas(balas) { }
	virtual void disparar(Jugador *jugador, std::vector<Jugador*>&) = 0;
	virtual void soltarArma(Jugador *jugador) = 0;
	virtual bool estaListo() = 0;
    void obtenerEnemigosCercanos(std::vector<Jugador*>& enemigos,
       Jugador* jugador, std::set<std::pair<int, Jugador*>>& jugadores);
};



class Perro: public Soldado {
	private:
	Cuchillo cuchillo;
	
	public:
	Perro(int& n);
	void disparar(Jugador *jugador, std::vector<Jugador*>&) override;
	void soltarArma(Jugador *jugador) override;
	bool estaListo() override;
};


class Guardia: public Soldado {
	private:
	Pistola pistola;
	
	public:
	Guardia(int& balas);
	void disparar(Jugador *jugador, std::vector<Jugador*>&) override;
	void soltarArma(Jugador *jugador) override;
	bool estaListo() override;
};


class SS: public Soldado {
	private:
	Ametralladora *ametralladora;
	
	public:
	SS(int &balas);
	bool agregarArma(Ametralladora *ametralladora);
	void disparar(Jugador *jugador, std::vector<Jugador*>&) override;	
	void soltarArma(Jugador *jugador) override;
	bool estaListo() override;
};


class Oficial: public Soldado {
	private:
	CanionDeCadena *canion;
	
	public:
	Oficial(int &balas);
	bool agregarArma(CanionDeCadena *canion);
	void disparar(Jugador *jugador, std::vector<Jugador*>&) override;
	void soltarArma(Jugador *jugador) override;
	bool estaListo() override;
};


class Mutante: public Soldado {
	private:
	Lanzacohetes *lanzacohetes;
	
	public:
	Mutante(int &balas);
	bool agregarArma(Lanzacohetes *lanzacohetes);
	void disparar(Jugador *jugador, std::vector<Jugador*>&) override;	
	void soltarArma(Jugador *jugador) override;
	bool estaListo() override;
};



class EstadoSoldado {
	private:
	Jugador *jugador;
	Soldado *soldado;
	Perro perro;
	Guardia guardia;
	SS ss;
	Oficial oficial;
	Mutante mutante;
	Soldado *soldado_anterior;
	
	public:
	explicit EstadoSoldado(Jugador *jugador, int& balas);
	bool agregarArma(Arma* arma);
	void cambiarArma(int numero_arma);
	void soltarArma();
	void disparar(std::vector<Jugador*>& enemigos);
	void recargarBalas();
};


#endif
