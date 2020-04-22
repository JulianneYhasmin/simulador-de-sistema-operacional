#pragma once
#include <string>
#include "CPU.h"
#include "Kernel.h"
#include "Processo.h"
#include <thread>
#include <iostream>

using namespace std;
class Simulador
{

private:

int quantum = 5; // em segundos, dentro do escalonador ou kernel eu preciso ajustar o tempo
int numero_cores = 3;
int quantidade_processos = 1;
int escalonador;
public:

void menu() {
	cout << "Selecione o tipo de escalonador: " << endl;
	cout << "1 -FIFO " << endl;
	cout << "1 -SJF " << endl;
	cout << "3 -RR " << endl;
	cin >> escalonador;
	}


};

