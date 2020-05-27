#pragma once
class MemoryBlock
{
private:
	int total_block_size;	// tamanho total do bloco em bytes
	int occupied_size;		// quantidade de bytes atualmente ocupada por um
							//processo
	int block_address;		//pelo que entendi é como o ID do bloco, preciso confirmar
	int next_free_block;	// o mesmo que o anterior só que o proximo livre
public:

};

