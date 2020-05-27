#pragma once
#include <string.h>
#include <string>
#include <iostream>
using namespace std;

class Processo
{
private:
	int process_id;
	int total_time; // em segundos
	int remaining_time; // em segundos
	string state; 
public:
	Processo(int id, int tempoTot, string estado) {
		this->process_id = id;
		total_time = tempoTot;
		remaining_time = tempoTot;
		this->state = estado;
	}
	Processo(int id, int tempoTot,int tempoRest, string estado) {
		this->process_id = id;
		total_time = tempoTot;
		remaining_time = tempoRest;
		this->state = estado;
	}
	Processo() {
		this->process_id = 0;
		total_time = 0;
		remaining_time = 0;
		this->state = "";
	}
	bool operator==(const Processo *outro) const
	{
		return outro->process_id == this->process_id;
	}
	void imprimeValor() {
		cout << "[ " << process_id << ", " << state << ", " << total_time << ", " << remaining_time << " ]";
	}
	void setId(int id) {
		this->process_id = id;
	}
	int getId() {
		return process_id;
	}
	void setTempoTotal(int tempoTotal) {
		this->total_time = tempoTotal;
	}
	int getTempoTotal() {
		return total_time;
	}
	void setTempoRestante(int tempoRestante) {
		this->remaining_time = tempoRestante;
	}
	int getTempoRestante() {
		return remaining_time;
	}
	void setEstado(string estado) {
		this->state = estado;
	}
	string getEstado() {
		return state;
	}

};

