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
	int numeroCores;
	int quantum;
	
	//Escalonador* escalonador;
public:
	Kernel(int numero_cores, int quantidade_processos, int tipoEscalonador, int quantum) {
		this->cpu = new CPU();
		this->quantidade_processos = quantidade_processos;
		escalonador = new Escalonador(quantum);
		this->tipoEscalonador = tipoEscalonador;
		numeroCores = numero_cores;
		this->quantum = quantum;
		
	}
	Kernel(int quantum) {
		this->cpu = new CPU();
		this->quantidade_processos = 0;
		process_control_table = list<Processo>();
		escalonador = new Escalonador(quantum);
		quantidade_processos = 0;
		tipoEscalonador = 0;
	}
	Kernel() {
		this->cpu = new CPU();
		this->quantidade_processos = 0;
		escalonador = new Escalonador(0);
		quantidade_processos = 0;
		tipoEscalonador = 0;
		numeroCores = 0;
	}
	
	void run() {	
			Sleep(1000);
			escalonador = new Escalonador(process_control_table,tipoEscalonador, cpu,numeroCores, quantum);
			escalonador->run();
			
	
	}
	void criadorDeProcessos() {
		int i = 0;
		Processo* p = new Processo();
		while (i < quantidade_processos) {
			p = gerarProcessoRandomico(i);
			process_control_table.push_back(*p);
			i++;
		}
		delete(p);
	}

	void imprimeTabelaProcessos() {
		cout << "---------------------- TABELA DE PROCESSOS -----------------------------" << endl;
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
		process_control_table.clear();
		delete(escalonador);
	}


};

