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
void decrementa(Processo *p, int tempo)
{
	while (tempo > 0)
	{
		p->setTempoRestante(p->getTempoRestante()-1);
		Sleep(1000);
	}
}
*/
class Escalonador
{
private:
	list <Processo> *finalizados;
	list <Processo> *prontos;
	int tipoEscalonador;
	CPU* cores;
	//CPU *cores; // quantidade de cores definido no simulador
				// pense em uma forma de criar uma lista desse tamanho aqui

public:
	
	//thread decrementa(decrementa,prontos ,1);

	Escalonador(list <Processo> *tabelaProcessos, int tipoEsc, CPU *cores) {
		this->cores = cores;
		prontos = tabelaProcessos;
		this->tipoEscalonador = tipoEsc;
		this->cores = cores;
	}
	Escalonador() {
		prontos =NULL;
		this->cores = NULL;
		finalizados = new Processo();
		this->tipoEscalonador = 0;
		cores = NULL;
	}
	//CPU *cores; // Representa os cores de uma CPU por meio de uma 
				  // Estrutura de dados
	// ready_queue // Fila dos processos prontos para execução
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
	}
	
	// Primeiro que entra é o primeiro que sai
	void FIFO() {
		//list<Processo>::iterator it = prontos->begin();
		//thread tempo(decrementa, );

	}
	void RoundRobin() {

	}
	void SJF() {

	}
};

