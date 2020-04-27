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

class Escalonador
{
private:
	list <Processo> finalizados;
	list <Processo> prontos;
	int tipoEscalonador;
	CPU *cpu;
	int quantum;
	int numeroCores;
	//CPU *cores; // quantidade de cores definido no simulador
				// pense em uma forma de criar uma lista desse tamanho aqui

public:
	
	//thread decrementa(decrementa,prontos ,1);

	Escalonador(list <Processo> tabelaProcessos, int tipoEsc, CPU *cores,int numeroCores) {
		this->cpu = cores;
		inserirProcesso(tabelaProcessos,0);
		this->tipoEscalonador = tipoEsc;
		this->numeroCores = numeroCores;
	}
	Escalonador(int quantum) {
		prontos = list<Processo>();
		this->cpu = new CPU();
		finalizados = list<Processo>();
		this->tipoEscalonador = 0;
		cpu = new CPU();
		this->quantum = quantum;
	}



	void inserirProcesso(list <Processo> lista, int listaLocal) {
		int i = 0;
		list<Processo>::iterator it = lista.begin();
		Processo *p = new Processo();
		if (listaLocal == 0) {
			//cout << "\n--------------APTOS ---------------------- " << endl;
			while (it != lista.end()) {
				p = new Processo((it)->getId(), (it)->getTempoTotal(), (it)->getEstado());

				//p->imprimeValor();
				prontos.push_back(*p);
				it++;
			}
		}
		if (listaLocal == 1) {
			cout << "\n--------------CORES ---------------------- " << endl;
			int i = 0;
			while (i!=numeroCores) {
				p = new Processo((it)->getId(), (it)->getTempoTotal(), (it)->getEstado());
				p->imprimeValor();
				cpu->cores.push_back(*p);
				prontos.pop_front();
				it++;
				i++;
			}
		}
		
		
	}
	//Metodo usado para escalonar um processo e iniciar sua execução num core de processamento
	void schedule_process(Processo *p) {
		cpu->cores.push_back(*p);
		//thread decrementa(&decrementa, cores->cores.begin()->getTempoTotal());
		//decrementa.join();

	}
	void setAlgoritimoEscalonador(int algoritimo) {
	//	tipoEscalonador = algoritimo;
	}
	//seleciona o escalonador de processos de acordo com o tipo
	void escalonadorDeProcessos() {
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
		imprimeListas(prontos);
		escalonadorDeProcessos();
		cout << "\n-------------------- FILA DE FINALIZADOS DO ESCALONADOR ----------------------" << endl;
		imprimeListas(finalizados);
		
		
	}
	void imprimeListas(list<Processo> lista) {
		
		list<Processo>::iterator it = lista.begin();
		for (it; it != lista.end(); it++) {
			(it)->imprimeValor();
		}
		
	}

	void insereFIFO(list<Processo> lista) {
		cout << "\n----------------- CORES ---------------------- " << endl;
		int i = cpu->cores.size();
		list<Processo>::iterator it = lista.begin();
		Processo* p = new Processo();
		while (i != numeroCores) {
			p = new Processo((it)->getId(), (it)->getTempoTotal(), "Rodando");
			p->imprimeValor();
			cpu->cores.push_back(*p);
			prontos.pop_front();
			it++;
			i++;
		}
	}
	Processo* execucaoCORES(Processo *core) {
		int tempoRestante = core->getTempoRestante();
		core->setTempoRestante(tempoRestante-1);
		return core;
	}
	void removeFIFO() {
		list<Processo>::iterator it = cpu->cores.begin();
		int i = 0;
		while (i != numeroCores) {
		
			it++;
			i++;
		}
	}
	void verificaCORE() {
		list<Processo>::iterator it = cpu->cores.begin();
		CPU* rodando = new CPU();
		Processo* core ;
		for (it = cpu->cores.begin(); it != cpu->cores.end(); it++) {
			core = new Processo((it)->getId(), (it)->getTempoTotal(), (it)->getTempoRestante(), "Rodando");
			core = execucaoCORES(core);
			rodando->cores.push_back(*core);
			if (core->getTempoRestante() == 0) {
				core->setTempoRestante(0);
				core->setEstado("Finalizado");
				finalizados.push_back(*core);
				rodando->cores.pop_back();				
				if (prontos.size()>0) {				
				list<Processo>::iterator it2 = prontos.begin();
				Processo* core2 = new Processo((it2)->getId(), (it2)->getTempoTotal(),"Rodando");
				rodando->cores.push_back(*core2);
				prontos.pop_front();
				}
	
			}

			delete(core);
		}
		
		cpu->cores = rodando->cores;
		cout << "\nCORES EXECUTANDO" << endl;
		imprimeListas(cpu->cores);
		delete(rodando);
		
	}

	void verificaCores() {
		
		insereFIFO(prontos);
		while (cpu->cores.size()>0) {
			verificaCORE();
			Sleep(1000);
			
		}
		
		/*
		
		//tamanho = prontos.size();
		list<Processo>::iterator it = cpu->cores.begin();
					
			Processo* core = new Processo((it)->getId(), (it)->getTempoTotal(), "Rodando");
			//tamanho = prontos.size();
			while (cpu->cores.size()>0) {

			
			core = execucaoCORES(core);
			cpu->cores.erase(it);
			cpu->cores.insert(it,*core);
			
			if (core->getTempoRestante() == 0) {
				core->setTempoRestante(0);
				core->setEstado("Finalizado");
				finalizados.push_back(*core);
				cpu->cores.erase(it);

			}
			it++;
			
			cout << "\nCORE EXECUTADO" << endl;
			imprimeListas(cpu->cores);	
			}*/
		
	}

	// Primeiro que entra é o primeiro que sai
	void FIFO() {
		Processo* p = new Processo();
		//list<Processo>::iterator it = prontos.begin();
		verificaCores();
		
		// decrementa.join();
		
	}
	void RoundRobin() {

	}
	void SJF() {

	}
};



