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

	Escalonador(list <Processo> tabelaProcessos, int tipoEsc, CPU *cores,int numeroCores,int quantum) {
		this->cpu = cores;
		inserirProcesso(tabelaProcessos);
		this->tipoEscalonador = tipoEsc;
		this->numeroCores = numeroCores;
		this->quantum = quantum;
	}
	Escalonador(int quantum) {
		prontos = list<Processo>();
		this->cpu = new CPU();
		finalizados = list<Processo>();
		this->tipoEscalonador = 0;
		cpu = new CPU();
		this->quantum = quantum;
	}



	void inserirProcesso(list <Processo> lista) {
		list<Processo>::iterator it = lista.begin();
		Processo *p = new Processo();
			//cout << "\n--------------APTOS ---------------------- " << endl;
			while (it != lista.end()) {
				p = new Processo((it)->getId(), (it)->getTempoTotal(), (it)->getEstado());
				prontos.push_back(*p);
				it++;
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

	void insereFIFO_RR(list<Processo> lista) {//Retira da lista de prontos e coloca na lista de cores
		cout << "\n----------------------------------------------------------------- " << endl;
		int tamanhoListaCores = cpu->cores.size();
		list<Processo>::iterator it = lista.begin();
		Processo* p = new Processo();
		int numTemporarioCores = numeroCores;
		while (tamanhoListaCores != numTemporarioCores) {
			if (lista.size()<numeroCores) {
				numTemporarioCores = prontos.size();
			}
			p = new Processo((it)->getId(), (it)->getTempoTotal(),(it)->getTempoRestante(), "Rodando");
			cpu->cores.push_back(*p);// Insere nos meus cores
			prontos.pop_front();//Remove o primeiro elemento da minha lista de prontos
			it++;
			tamanhoListaCores++;
		}
		delete(p);
	}
	Processo* execucaoCORES(Processo *core) {
		int tempoRestante = core->getTempoRestante();
		core->setTempoRestante(tempoRestante-1);
		return core;
	}
	list<Processo> removeFIFO(list <Processo> lista) {
		list<Processo>::iterator it = cpu->cores.begin();
	}
	void executaFIFO() {
		list<Processo>::iterator it = cpu->cores.begin();
		CPU* rodando = new CPU();
		Processo* core ;
		for (it = cpu->cores.begin(); it != cpu->cores.end(); it++) {
			core = new Processo((it)->getId(), (it)->getTempoTotal(), (it)->getTempoRestante(), "Rodando");
			core = execucaoCORES(core);// executa 1 segundo
			rodando->cores.push_back(*core);
			if (core->getTempoRestante() == 0) {
				// Atualizando os dados do core terminado
				//core->setTempoRestante(0);
				core->setEstado("Finalizado");
				finalizados.push_back(*core);
				rodando->cores.pop_back();				
				if (prontos.size()>0) {	//			
				list<Processo>::iterator it2 = prontos.begin();
				Processo* core2 = new Processo((it2)->getId(), (it2)->getTempoTotal(), (it2)->getTempoTotal(),"Rodando");
				rodando->cores.push_back(*core2);
				prontos.pop_front();
				delete(core2);
				}
	
			}

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
				prontos.push_back(*core);
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
			if (core->getTempoRestante() == 0) {
				core->setTempoRestante(0);
				core->setEstado("Finalizado");
				finalizados.push_back(*core);
				rodando->cores.pop_back();
				if (prontos.size() > 0) {
					list<Processo>::iterator it2 = prontos.begin();
					Processo* core2 = new Processo((it2)->getId(), (it2)->getTempoTotal(), (it2)->getTempoRestante(), "Rodando");
					rodando->cores.push_back(*core2);
					prontos.pop_front();
					delete(core2);
				}
			}

			delete(core);			
		}
		cpu->cores = rodando->cores;		
		}
		delete(rodando);
	}
	void escalonaRR() {
		insereFIFO_RR(prontos);
		int tempo = 0;
		int cont = 0;
		while (cpu->cores.size() > 0) {
			// Esse metodo faz a inclusão e exclusão durante o periodo da execução
			tempo = quantum;
			cout << "\n --- " << cont <<" ---" << endl;
			cont++;
			while (tempo >= 0)
			{
				executaRR(tempo);
				if (tempo == 0) {
					if (prontos.size() != 0) {
						insereFIFO_RR(prontos);
					}					
				}
				Sleep(1000);
				cout << "\nFILA DE APTOS: ";
				imprimeListas(prontos);
				cout << endl << endl;
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
	void escalonaFIFO() {
		insereFIFO_RR(prontos);
		int cont = 0;
		while (cpu->cores.size()>0) {
			cout << "\nT" << cont << endl;
			cont++;
			// Esse metodo faz a inclusão e exclusão durante o periodo da execução
			executaFIFO();
			Sleep(1000);
			cout << "\nFILA DE APTOS: ";
			imprimeListas(prontos);
			cout << endl << endl;
			cout << "CORES: ";
			imprimeListas(cpu->cores);
			cout << endl << endl;
			cout << "FINALIZADOS: ";
			imprimeListas(finalizados);
			cout << endl << endl;
			
		}	
	}

	// Primeiro que entra é o primeiro que sai
	void FIFO() {
		escalonaFIFO();
	}
	void RoundRobin() {
		escalonaRR();

	}
	void SJF() {

	}
};



