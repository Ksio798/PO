#include "chunk.h"
#include <iostream>

int main()
{
    fefu_laboratory_two::ChunkList<int, 5> chunkList;

    // Вставка элементов
    for (int i = 1; i <= 10; ++i)
        chunkList.insert(i);


    // Вывод содержимого после вставки
    for (const auto& chunk : chunkList)
    {
        for (const auto& value : chunk.data)
            std::cout << value << " ";

        std::cout << '\n';
    }

    // Удаление элементов
    chunkList.erase(2);
    chunkList.erase(5);
    chunkList.erase(8);

    // Вывод содержимого после удалений
    std::cout<< '\n';
    for (const auto& chunk : chunkList)
    {
        for (const auto& value : chunk.data)
            std::cout << value << " ";

        std::cout << '\n';
    }
}