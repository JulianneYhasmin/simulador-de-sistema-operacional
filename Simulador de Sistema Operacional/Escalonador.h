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
	CPU *cores;
	int quantum;
	int numeroCores;
	//CPU *cores; // quantidade de cores definido no simulador
				// pense em uma forma de criar uma lista desse tamanho aqui

public:
	
	//thread decrementa(decrementa,prontos ,1);

	Escalonador(list <Processo> tabelaProcessos, int tipoEsc, CPU *cores,int numeroCores) {
		this->cores = cores;
		inserirProcesso(tabelaProcessos,0);
		this->tipoEscalonador = tipoEsc;
		this->numeroCores = numeroCores;
	}
	Escalonador(int quantum) {
		prontos = list<Processo>();
		this->cores = new CPU();
		finalizados = list<Processo>();
		this->tipoEscalonador = 0;
		cores = new CPU();
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
				cores->cores.push_back(*p);
				prontos.pop_front();
				it++;
				i++;
			}
		}
		
		
	}
	//Metodo usado para escalonar um processo e iniciar sua execução num core de processamento
	void schedule_process(Processo *p) {
		cores->cores.push_back(*p);
		//thread decrementa(&decrementa, cores->cores.begin()->getTempoTotal());
		//decrementa.join();

	}
	void setAlgoritimoEscalonador(int algoritimo) {
	//	tipoEscalonador = algoritimo;
	}
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
		imprimeFilaAptos();
		escalonadorDeProcessos();
		imprimeFilaAptos();
		
	}
	void imprimeFilaAptos() {
		cout << "\nFILA DE APTOS DO ESCALONADOR" << endl;
		list<Processo>::iterator it = prontos.begin();
		for (it; it != prontos.end(); it++) {
			(it)->imprimeValor();
		}
		
	}

	void insereFIFO(list<Processo> lista) {
		cout << "\n--------------CORES ---------------------- " << endl;
		int i = 0;
		//Processo* p = new Processo();
		//list<Processo>::iterator it = prontos.begin();
		//int i = 0;
		list<Processo>::iterator it = lista.begin();
		Processo* p = new Processo();
		while (i != numeroCores) {
			p = new Processo((it)->getId(), (it)->getTempoTotal(), "Rodando");
			p->imprimeValor();
			cores->cores.push_back(*p);
			prontos.pop_front();
			it++;
			i++;
		}
		
	}
	void removeFIFO() {
		list<Processo>::iterator it = cores->cores.begin();
		int i = 0;
		while (i != numeroCores) {
		
			it++;
			i++;
		}
	}
	void decrementa(int tempo) {
		while (tempo > 0) {
			tempo--;
			Sleep(1000);
		}
		//return tempo;
	}
	void verificaCores() {
		int tamanho = 0;
			tamanho =cores->cores.size();
		while (tamanho < numeroCores) {
			list<Processo>::iterator it = prontos.begin();
			//cores->cores.push_back(*it);
			//Processo* p = new Processo();
			//inserirProcesso(prontos, 1); //se 1 == lista de cores se não (0) lista de prontos(apstos)
			insereFIFO(prontos);
			//decrementa(cores->cores.begin()->getTempoTotal());
			tamanho = cores->cores.size();
		}
		
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



