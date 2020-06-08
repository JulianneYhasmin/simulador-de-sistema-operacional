#pragma once
#include <string.h>
#include <string>
#include <iostream>
#include <list>
#include "MemoryBlock.h"
#include "Kernel.h"
using namespace std;

class Processo
{
private:
	int process_id;
	int total_time; // em segundos
	int remaining_time; // em segundos
	string state; 
	int total_memory_used; // quantidade total de memoria usada pelo processo
	list <MemoryBlock> memory_pointers; // endereços dos blocos de memoria desse processo

public:
	Processo(int id, int tempoTot, string estado) {
		this->process_id = id;
		total_time = tempoTot;
		remaining_time = tempoTot;
		this->state = estado;
		total_memory_used =0;
		memory_pointers = list<MemoryBlock>();
	}
	Processo(int id, int tempoTot,int tempoRest, string estado) {
		this->process_id = id;
		total_time = tempoTot;
		remaining_time = tempoRest;
		this->state = estado;
		total_memory_used=0;
		memory_pointers = list<MemoryBlock>();
	}
	Processo() {
		this->process_id = 0;
		total_time = 0;
		remaining_time = 0;
		this->state = "";
		total_memory_used=0;
		memory_pointers = list<MemoryBlock>();
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
	// Simula um pedido de memoria estatico
	// é executado quando o processo entra na fila de aptos
	// chama o malloc
	// gera um numero aleatorio que sera aquantidade de bytes da minha requisição
	// o retonro feito por esse metodo vai para lista de memory_pointers
	MemoryBlock* generate_random_static_memory_call() {
		Kernel* k =  new Kernel();
		int num = 1+ rand() % 4096;

		return k->memory_allocation(num);
	}
	void generate_random_dynamic_memory_call() {

	}

};

