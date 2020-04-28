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
        tipEscal:
        cout << "Selecione o tipo de escalonador: " << endl;
        cout << "1 -FIFO " << endl;
        cout << "2 -SJF " << endl;
        cout << "3 -RR " << endl;
        cin >> escalonador;
        if (escalonador < 1 || escalonador>3) {
            cout << "Digite 1, 2 ou 3 para selecionar o escalonador." << endl;
            goto tipEscal;
        }
        if (escalonador == 3) {
            correcao_quantum:
            cout << "Digite o valor do Quantum: ";
            cin >> quantum;
            if (2 > quantum || quantum > 20) {
                cout << "\n Por favor digite um valor entre 2 e 20." << endl;
                goto correcao_quantum;
            }
        }
        

        cout << "Digite a quantidade de Processos: " << endl;
        cin >> quantidade_processos;

        corrige_numCores:
        cout << "Digite a quantidade de CORES: " << endl;
        cin >> numero_cores;
        if (64 < numero_cores || numero_cores < 1) {
            cout << "VALOR INVALIDO TENTE UM NUMERO ENTRE 1 E 64." << endl;
            goto corrige_numCores;
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
        quantum =0; // em segundos, dentro do escalonador ou kernel eu preciso ajustar o tempo
        numero_cores = 0;
        quantidade_processos = 0;
        escalonador = 0;
        k = new Kernel(quantum);
    }

    ~Simulador() {
        // free(k);
    }
};


