#pragma once
#include <string>
#include "MemoryBlock.h"
#include <list>
using namespace std;
class MemoryManager
{
private:
	list<MemoryBlock> memory; // RAM
	list<MemoryBlock> free_blocks_list; // ponteiro para o primeiro bloco de memoria livre
	int total_memory; //quantidade de momoria instalada no sistema em bytes
	int memory_overhead; // quantidade de memoria usada pelo memory_manager
	int available_memory; // memoria livre e disponivel (available = total -occupied - overhead)
	int occupied_memory; // total de memoria ocupada por processos
	// statistics_table

public:
	MemoryBlock* malloc(int nBytes) {
		MemoryBlock *d;
		return d;
	}

	void free() {

	}
	void set_allocation_algorithm(int algoritimoAlocao) {

	}

	// checa se é possivel resolver uma requisição de memória por x bytes
	bool check_free_memory(int xBytes) {
		return true;
	}

	void first_fit() {

	}

	void best_fit() {

	}

	void quick_fit() {

	}



};

