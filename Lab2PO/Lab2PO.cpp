#include "chunk.h"
#include <iostream>

int main()
{
	fefu_laboratory_two::ChunkList<int, 2> chunkList;

	// Вставка элементов
	for (int i = 1; i <= 10; ++i)
		chunkList.insert(i);

	//Вывод элементов
	auto chunk = chunkList.chbegin();
	for (int i = 0; i < chunkList.count(); i++)
	{
		for (int j = 0; j < (*chunk)->count; j++)
			std::cout << (*chunk)->data[j] << '\n';

		chunk = &(*chunk)->Next;
		std::cout << '\n';
	}

	//удаление элементов
	chunkList.erase(1);
	chunkList.erase(4);
	chunkList.erase(9);

	//Вывод после удаления
	chunk = chunkList.chbegin();
	for (int i = 0; i < chunkList.count(); i++)
	{
		for (int j = 0; j < (*chunk)->count; j++)
			std::cout << (*chunk)->data[j] << '\n';
		
		chunk = &(*chunk)->Next;
		std::cout << '\n';
	}

	//удаление всех элементов
	chunkList.clear();
	std::cout << chunkList.count();
}