#pragma once
#include <list> 
#include "Processo.h"

using namespace std;
class CPU
{
private:
	
public:
//	list<Processo>* cores;

/*	CPU() {

	}
*/
	Processo** cores;
	CPU(int tamanho) {
		cores = new Processo*[tamanho];
	}
	
};

