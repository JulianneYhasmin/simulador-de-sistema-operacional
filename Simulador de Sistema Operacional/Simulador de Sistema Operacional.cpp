// Simulador de Sistema Operacional.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include "Processo.h"
#include "Kernel.h"
#include "CPU.h"

using namespace std;
// Cria o processo de forma randomica, recebendo apenas o id
/*Processo criador_randomico_processos(int seq) {
    Processo *t = new Processo();
    return t;
}*/

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
        
        /**/
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
        k = new Kernel(numero_cores, quantidade_processos, escalonador);
        k->criadorDeProcessos();
        k->imprimeTabelaProcessos();

   }
    Simulador() {
        quantum = 2 + rand() % 18; // em segundos, dentro do escalonador ou kernel eu preciso ajustar o tempo
        numero_cores = 0;
        quantidade_processos = 0;
        escalonador = 0;
        k = new Kernel();
    }

    ~Simulador() {
       // free(k);
    }
};

int main()
{
    Simulador* s = new Simulador();
    // Criador de processos randomicos
    s->menu();
    return 0;
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
