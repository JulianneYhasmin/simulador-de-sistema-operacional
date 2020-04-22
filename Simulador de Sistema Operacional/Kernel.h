#pragma once
#include <vector>
#include <list>
#include "Processo.h"
#include "Escalonador.h"
#include "CPU.h"
#include <iostream>
class Kernel
{
private:
	CPU* cpu;
	int quantidade_processos;
	list <Processo> process_control_table;
	Escalonador* escalonador;
	int tipoEscalonador;
	
	//Escalonador* escalonador;
public:
	Kernel(int numero_cores, int quantidade_processos, int tipoEscalonador ) {
		this->cpu = new CPU(numero_cores);
		this->quantidade_processos = quantidade_processos;
		escalonador = new Escalonador();
		this->tipoEscalonador = tipoEscalonador;
	}
	Kernel() {
		this->cpu = new CPU(0);
		this->quantidade_processos = 0;
		escalonador = new Escalonador();
	}
	
	void run() {	
		while (true) {
			Sleep(1000);
			escalonador = new Escalonador(process_control_table,tipoEscalonador, cpu);

		}	
	
	}
	void criadorDeProcessos() {
		int i = 0;
		while (i < quantidade_processos) {
			Processo* p = new Processo();
			p = gerarProcessoRandomico(i);
			process_control_table.push_back(*p);
			i++;
		}
	}

	void imprimeTabelaProcessos() {
		for (list<Processo>::iterator it = process_control_table.begin(); it != process_control_table.end(); it++) {
			(it)->imprimeValor();
		}
	}
	// Cria o processo randomico
	Processo* gerarProcessoRandomico(int id) {
		int tempoT;
		tempoT = 1 + rand() % 19;

		Processo* randomico = new Processo(id, tempoT, "Pronto");
		return randomico;
	}
	void kill_process() {


	}


};

