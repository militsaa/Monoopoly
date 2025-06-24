#include "BoardPrinter.h"
#include "cellStr.h"
#include <iostream>

void printBoard(const Vector<Field*>& fields, int width)
{
	int total = fields.getSize();
	int side = total / 4;

	for (int i = 0; i <= side; ++i) {
		std::cout << "|" << cellStr(fields[i], width);
	}
	std::cout << "|\n";

	for (int i = 0; i < side - 1; ++i) {
		std::cout << "|" << cellStr(fields[total - 1 - i], width);

		for (int j = 0; j < side - 1; ++j) {
			for (int k = 0; k < width; ++k)
				std::cout << " ";
			std::cout << "|";
		}

		std::cout << cellStr(fields[side + 1 + i], width) << "|\n";
	}

	for (int i = side * 3; i >= side * 2; --i) {
		std::cout << "|" << cellStr(fields[i], width);
	}
	std::cout << "|\n";
}
