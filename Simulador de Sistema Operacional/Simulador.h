#pragma once
#include <string>
#include "CPU.h"
#include "Kernel.h"
#include "Processo.h"
#include <thread>
#include <iostream>

using namespace std;

class Simulador {

private:
    int quantum; // em segundos, dentro do escalonador ou kernel eu preciso ajustar o tempo
    int numero_cores;
    int quantidade_processos;
    int escalonador;
    Kernel* k = new Kernel();
public:


    void menu() {
        cout << "Selecione o tipo de escalonador: " << endl;
        cout << "1 -FIFO " << endl;
        cout << "2 -SJF " << endl;
        cout << "3 -RR " << endl;
        cin >> escalonador;


        cout << "Digite a quantidade de Processos: " << endl;
        cin >> quantidade_processos;
        if (20 < quantidade_processos || quantidade_processos < 2) {
            cout << "VALOR INVALIDO TENTE UM NUMERO ENTRE 2 E 20." << endl;

        }

        cout << "Digite a quantidade de CORES: " << endl;
        cin >> numero_cores;
        if (64 < numero_cores || numero_cores < 1) {
            cout << "VALOR INVALIDO TENTE UM NUMERO ENTRE 1 E 64." << endl;

        }
        k = new Kernel(numero_cores, quantidade_processos, escalonador, quantum);
        k->criadorDeProcessos();
        k->imprimeTabelaProcessos();
        k->run();
        //thread runKernel(Escalonador::run);
        //runKernel.join();
        k->kill_process();
    }
    Simulador() {
        quantum = 2 + rand() % 18; // em segundos, dentro do escalonador ou kernel eu preciso ajustar o tempo
        numero_cores = 0;
        quantidade_processos = 0;
        escalonador = 0;
        k = new Kernel(quantum);
    }

    ~Simulador() {
        // free(k);
    }
};


