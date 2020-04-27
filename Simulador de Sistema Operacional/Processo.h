#pragma once
#include <string.h>
#include <string>
#include <iostream>
using namespace std;

class Processo
{
private:
	int id;
	int tempoTotal; // em segundos
	int tempoRestante; // em segundos
	string estado;
public:
	Processo(int id, int tempoTot, string estado) {
		this->id = id;
		tempoTotal = tempoTot;
		tempoRestante = tempoTot;
		this->estado = estado;
	}
	Processo(int id, int tempoTot,int tempoRest, string estado) {
		this->id = id;
		tempoTotal = tempoTot;
		tempoRestante = tempoRest;
		this->estado = estado;
	}
	Processo() {
		this->id = 0;
		tempoTotal = 0;
		tempoRestante = 0;
		this->estado = "";
	}
	inline bool operator==(const Processo& outro) const
	{
		return outro.id == this->id;
	}
	void imprimeValor() {
		cout << "[ " << id << ", " << tempoTotal << ", " << estado<< ", " << tempoRestante << " ]";
	}
	void setId(int id) {
		this->id = id;
	}
	int getId() {
		return id;
	}
	void setTempoTotal(int tempoTotal) {
		this->tempoTotal = tempoTotal;
	}
	int getTempoTotal() {
		return tempoTotal;
	}
	void setTempoRestante(int tempoRestante) {
		this->tempoRestante = tempoRestante;
	}
	int getTempoRestante() {
		return tempoRestante;
	}
	void setEstado(string estado) {
		this->estado = estado;
	}
	string getEstado() {
		return estado;
	}

};

