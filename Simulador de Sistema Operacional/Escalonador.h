#pragma once
#include <string>
#include "CPU.h"
#include "Processo.h"
#include <thread>
#include <windows.h>
//run) crie uma tarefa que fa�a a execu��o do tipo de escalonador
// tred que decrementa o tempo
// o usu�rio vai escolher o escalonador, e vai passar como parametro para
// essa tarefa, dentro dela ser� executado o processo
using namespace std;
/*void decrementa(Processo *p, int tempo)
{
	while (tempo > 0)
	{
		p->setTempoRestante(p->getTempoRestante()-1);
		Sleep(1000);
	}
}*/
class Escalonador
{
private:
	list <Processo> finalizados;
	CPU *cores; // quantidade de cores definido no simulador
				// pense em uma forma de criar uma lista desse tamanho aqui

public:
	list <Processo> prontos;
	//thread decrementa(decrementa,prontos ,1);


	Escalonador(list <Processo> tabelaProcessos) {
		prontos = tabelaProcessos;
	}
	//CPU *cores; // Representa os cores de uma CPU por meio de uma 
				  // Estrutura de dados
	// ready_queue // Fila dos processos prontos para execu��o
	void setAlgoritimoEscalonador(int algoritimo) {
		if (algoritimo == 1) {

		}
		if (algoritimo == 2) {

		}
		if (algoritimo == 3) {

		}
	}
	// Primeiro que entra � o primeiro que sai
	void FIFO() {

	}
	void RoundRobin() {

	}
	void SJF() {

	}
};

