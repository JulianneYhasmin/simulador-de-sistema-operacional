#pragma once
#include <string>
#include "CPU.h"
#include "Processo.h"
#include <thread>
#include <windows.h>
//run) crie uma tarefa que faça a execução do tipo de escalonador
// tred que decrementa o tempo
// o usuário vai escolher o escalonador, e vai passar como parametro para
// essa tarefa, dentro dela será executado o processo
using namespace std;
/*
void decrementa(int tempo)
{
	//int tempo = p->getTempoTotal();
	while (tempo > 0)
	{
		tempo--;
		Sleep(1000);
	}
}
*/

class Scheduler
{
private:
	list <Processo> finalizados;
	list <Processo> ready_queue; // fila de aptos
	int tipoEscalonador;
	CPU *cpu;
	int quantum;
	int numeroCores;

public:
	
	Scheduler(list <Processo> tabelaProcessos, int tipoEsc, CPU *cores,int numeroCores,int quantum) {
		this->cpu = cores;
		insert_process(tabelaProcessos);
		this->tipoEscalonador = tipoEsc;
		this->numeroCores = numeroCores;
		this->quantum = quantum;
	}
	Scheduler(int quantum) {
		ready_queue = list<Processo>();
		this->cpu = new CPU();
		finalizados = list<Processo>();
		this->tipoEscalonador = 0;
		cpu = new CPU();
		this->quantum = quantum;
	}



	void insert_process(list <Processo> lista) {
		list<Processo>::iterator it = lista.begin();
		Processo *p = new Processo();
			//cout << "\n--------------APTOS ---------------------- " << endl;
			while (it != lista.end()) {
				p = new Processo((it)->getId(), (it)->getTempoTotal(), (it)->getEstado());
				ready_queue.push_back(*p);
				it++;
			}		
	}
	

	//seleciona o escalonador de processos de acordo com o tipo
	void set_scheduling_algorithm() {
		if (tipoEscalonador == 1) {
			FIFO();
		}
		if (tipoEscalonador == 2) {
			SJF();
		}
		if (tipoEscalonador == 3) {
			RoundRobin();
		}
	}
	void run() {
	//	thread escalonador(escalonadorDeProcessos);
	//	escalonador.join();
		cout << "\n-------------------- FILA DE APTOS DO ESCALONADOR ----------------------" << endl;
		imprimeListas(ready_queue);
		set_scheduling_algorithm();
		cout << "\n-------------------- FILA DE FINALIZADOS DO ESCALONADOR ----------------------" << endl;
		imprimeListas(finalizados);
		
	}
	void imprimeListas(list<Processo> lista) {
		
		list<Processo>::iterator it = lista.begin();
		for (it; it != lista.end(); it++) {
			(it)->imprimeValor();
		}
		
	}

	//Metodo usado para escalonar um processo e iniciar sua execução num core de processamento
	void insereFIFO_RR(list<Processo> lista) {//Retira da lista de prontos e coloca na lista de cores
		cout << "\n------------------------------TESTE----------------------------------- " << endl;
		int tamanhoListaCores = cpu->cores.size();
		list<Processo>::iterator it = lista.begin();
		Processo* p = new Processo();
		int numTemporarioCores = numeroCores;
		
		if (lista.size()<numeroCores) {
			numTemporarioCores = ready_queue.size();
		}
		
		while (tamanhoListaCores != numTemporarioCores) {
			p = new Processo((it)->getId(), (it)->getTempoTotal(),(it)->getTempoRestante(), "Rodando");
			cpu->cores.push_back(*p);// Insere nos meus cores
			it++;
			ready_queue.pop_front();//Remove o primeiro elemento da minha lista de prontos
			tamanhoListaCores++;
		}
		delete(p);
	}
	Processo* execucaoCORES(Processo *core) {
		int tempoRestante = core->getTempoRestante();
		core->setTempoRestante(tempoRestante-1);
		return core;
	}

	CPU* deschedule_process(Processo *core, CPU* rodando) { // REMOVE FIFO e RR
		//list<Processo>::iterator it = cpu->cores.begin();
		if (core->getTempoRestante() == 0) {
			// Atualizando os dados do core terminado
			//core->setTempoRestante(0);
			core->setEstado("Finalizado");
			finalizados.push_back(*core);
			rodando->cores.pop_back();
			if (ready_queue.size() > 0) {	//			
				list<Processo>::iterator it2 = ready_queue.begin();
				Processo* core2 = new Processo((it2)->getId(), (it2)->getTempoTotal(), (it2)->getTempoTotal(), "Rodando");
				rodando->cores.push_back(*core2);
				ready_queue.pop_front();
				delete(core2);
			}
			return rodando;
		}
		return rodando;
	}

	void executaFIFO() {
		list<Processo>::iterator it = cpu->cores.begin();
		CPU* rodando = new CPU();
		Processo* core ;
		for (it = cpu->cores.begin(); it != cpu->cores.end(); it++) {
			core = new Processo((it)->getId(), (it)->getTempoTotal(), (it)->getTempoRestante(), "Rodando");
			core = execucaoCORES(core);// executa 1 segundo
			rodando->cores.push_back(*core);
			deschedule_process(core, rodando);
			
			delete(core);
		}
		// atualiza os  cores
		cpu->cores = rodando->cores;
		delete(rodando);
		
	}

	void executaRR(int tempo) {
		list<Processo>::iterator it = cpu->cores.begin();
		CPU* rodando = new CPU();
		Processo* core;
		if (tempo == 0) {
			for (it = cpu->cores.begin(); it != cpu->cores.end(); it = cpu->cores.begin()) {				
				core = new Processo((it)->getId(), (it)->getTempoTotal(), (it)->getTempoRestante(), "Pronto");
				ready_queue.push_back(*core);
				cpu->cores.pop_front();
			}
		}
		if(tempo>0) {		
		for (it = cpu->cores.begin(); it != cpu->cores.end(); it++) {
			core = new Processo((it)->getId(), (it)->getTempoTotal(), (it)->getTempoRestante(), "Rodando");
			// executa 1 segundo
			core = execucaoCORES(core);
			rodando->cores.push_back(*core);
			// se o processo terminou
			rodando = deschedule_process(core, rodando);
			delete(core);			
		}
		cpu->cores = rodando->cores;		
		}
		delete(rodando);
	}

	// Primeiro que entra é o primeiro que sai
	void FIFO() {
		insereFIFO_RR(ready_queue);
		int cont = 0;
		while (cpu->cores.size() > 0) {
			cout << "\nT" << cont << endl;
			cont++;
			// Esse metodo faz a inclusão e exclusão durante o periodo da execução
			executaFIFO();
			Sleep(1000);
			cout << "\nFILA DE APTOS: ";
			imprimeListas(ready_queue);
			cout << endl << endl;
			cout << "CORES: ";
			imprimeListas(cpu->cores);
			cout << endl << endl;
			cout << "FINALIZADOS: ";
			imprimeListas(finalizados);
			cout << endl << endl;

		}
	}

	void RoundRobin() {
		insereFIFO_RR(ready_queue);
		int tempo = 0;
		int cont = 0;
		while (cpu->cores.size() > 0) {
			// Esse metodo faz a inclusão e exclusão durante o periodo da execução
			tempo = quantum;
			cout << "\n --- " << cont << " ---" << endl;
			cont++;
			while (tempo >= 0 && cpu->cores.size()>0)
			{
				executaRR(tempo);
				if (tempo == 0) {
					if (ready_queue.size() != 0) {
						insereFIFO_RR(ready_queue);
					}
				}
				
				Sleep(1000);
				cout << "\nFILA DE APTOS: ";
				imprimeListas(ready_queue);
				cout << endl << endl;
				cout << endl << "QUANTUM: " << tempo << endl;
				cout << "CORES: ";
				imprimeListas(cpu->cores);
				cout << endl << endl;
				cout << "FINALIZADOS: ";
				imprimeListas(finalizados);
				cout << endl << endl;
				tempo--;
			}
		}

	}
	void SJF() {

	}
};



