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
    int processor_cores_number; // quantidade de cores
    int batch_process_init; // quantidade de processos inicial
    int scheduling_algorithm;
    Kernel* k = new Kernel();
public:

    void menu() {
        tipEscal:
        cout << "Selecione o tipo de escalonador: " << endl;
        cout << "1 -FIFO " << endl;
        cout << "2 -SJF " << endl;
        cout << "3 -RR " << endl;
        cin >> scheduling_algorithm;
        if (scheduling_algorithm < 1 || scheduling_algorithm>3) {
            cout << "Digite 1, 2 ou 3 para selecionar o escalonador." << endl;
            goto tipEscal;
        }
        if (scheduling_algorithm == 3) {
            correcao_quantum:
            cout << "Digite o valor do Quantum: ";
            cin >> quantum;
            if (2 > quantum || quantum > 20) {
                cout << "\n Por favor digite um valor entre 2 e 20." << endl;
                goto correcao_quantum;
            }
        }
        

        cout << "Digite a quantidade de Processos: " << endl;
        cin >> batch_process_init;

        corrige_numCores:
        cout << "Digite a quantidade de CORES: " << endl;
        cin >> processor_cores_number;
        if (64 < processor_cores_number || processor_cores_number < 1) {
            cout << "VALOR INVALIDO TENTE UM NUMERO ENTRE 1 E 64." << endl;
            goto corrige_numCores;
        }
        k = new Kernel(processor_cores_number, batch_process_init, scheduling_algorithm, quantum);
        k->criadorDeProcessos();
        k->imprimeTabelaProcessos();
        k->run();
        //thread runKernel(Escalonador::run);
        //runKernel.join();
        k->kill_process();
    }
    Simulador() {
        quantum =0; // em segundos, dentro do escalonador ou kernel eu preciso ajustar o tempo
        processor_cores_number = 0;
        batch_process_init = 0;
        scheduling_algorithm = 0;
        k = new Kernel(quantum);
    }

    ~Simulador() {
         delete(k);
    }
};


