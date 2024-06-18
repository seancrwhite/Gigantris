// Fill out your copyright notice in the Description page of Project Settings.


#include "PolyominoGen.h"
#include "string"

TArray<FString> UPolyominoGen::CalcStringArray(int pieceSize)
{
	int** tArray = new int*[pieceSize];
	for (int i = 0; i < pieceSize; i++)
	{
		tArray[i] = new int[pieceSize];
		for (int j = 0; j < pieceSize; j++)
			tArray[i][j] = 0;
	}

	tArray[0][0] = 1;
	int blocksInserted = 1;
	int** coords = new int*[pieceSize];
	coords[0] = new int[2];

	coords[0][0] = 0;
	coords[0][1] = 0;

	// while less then n 1's exist in array, do
	//    randomly select existing 1
	//    find Von Neumann neighborhood for that one
	//    randomly place point in one of the 0s
	//    repeat
	while (blocksInserted < pieceSize)
	{
		bool inserted = false;
		while (!inserted)
		{
			int idx = FMath::RandRange(0, blocksInserted - 1);
			int* coord = coords[idx];
			int row = coord[1];
			int col = coord[0];

			int left = 1, right = 1, up = 1, down = 1;

			int start = FMath::RandRange(0, 3);
			switch (start) // TODO: clean this up if we have time
			{
			case 0:
				if (col - 1 >= 0)
				{
					down = tArray[col - 1][row];
					if (down == 0) {
						tArray[col - 1][row] = 1;
						coords[blocksInserted] = new int[2];
						coords[blocksInserted][0] = col - 1;
						coords[blocksInserted][1] = row;
						blocksInserted++;
						inserted = true;
					}
				}
				break;
			case 1:
				if (row + 1 < pieceSize)
				{
					right = tArray[col][row + 1];
					if (right == 0) {
						tArray[col][row + 1] = 1;
						coords[blocksInserted] = new int[2];
						coords[blocksInserted][0] = col;
						coords[blocksInserted][1] = row + 1;
						blocksInserted++;
						inserted = true;
					}
				}
				break;
			case 2:
				if (col + 1 < pieceSize)
				{
					up = tArray[col + 1][row];
					if (up == 0) {
						tArray[col + 1][row] = 1;
						coords[blocksInserted] = new int[2];
						coords[blocksInserted][0] = col + 1;
						coords[blocksInserted][1] = row;
						blocksInserted++;
						inserted = true;
					}
				}
				break;
			case 3:
				if (row - 1 >= 0)
				{
					left = tArray[col][row - 1];
					if (left == 0) {
						tArray[col][row - 1];
						coords[blocksInserted] = new int[2];
						coords[blocksInserted][0] = col;
						coords[blocksInserted][1] = row - 1;
						blocksInserted++;
						inserted = true;
					}
				}
				break;
			default:
				break;
			}
		}
	}

	
	// find flattest side(s)
	
	// calculate rotations available based on flattest sides
	//    if 2 -> 2 rotations (0 and 90)
	//    if 4 -> 1 rotation  (0)
	//    else -> 4 rotations (0, -90, 180, and 90)
	
	// rotate array so flattest side is on bottom
	//    in case of 3, put least flat side on top
	
	// calculate unique number based on seed generrated from the rotated array

	return UPolyominoGen::BuildStringArrayFromInts(pieceSize, tArray);
}

TArray<FString> UPolyominoGen::BuildStringArrayFromInts(int pieceSize, int** tArray)
{
	TArray<FString> StringArray;

	for (int i = 0; i < pieceSize; i++)
	{
		bool cont = false;
		std::string ret = "";

		for (int j = 0; j < pieceSize; j++)
		{
			int value = tArray[i][j];
			if (value) cont = true;
			ret += std::to_string(value);
		}
		if (cont)
			StringArray.Emplace(UTF8_TO_TCHAR(ret.c_str()));
		else
			break;
	}

	return StringArray;
}
