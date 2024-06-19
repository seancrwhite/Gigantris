// Fill out your copyright notice in the Description page of Project Settings.


#include "PolyominoGen.h"
#include "string"

UFUNCTION()
TArray<FString> UPolyominoGen::CalcStringArray(int pieceSize)
{
	UPROPERTY()
	int** tArray;

	UE_LOG(LogTemp, Display, TEXT("Generating piece of size %i"), pieceSize);

	if (FMath::RandRange(0, 14) == 0) 
	{
		UE_LOG(LogTemp, Display, TEXT("Forcing line piece"));
		tArray = new int* [1];
		tArray[0] = new int[pieceSize];
		for (int i = 0; i < pieceSize; i++) tArray[0][i] = 1;
		for (int i = 1; i < pieceSize; i++)
		{
			tArray[i] = new int[pieceSize];
			for (int j = 0; j < pieceSize; j++)
				tArray[i][j] = 0;
		}
	}
	else 
	{
		tArray = UPolyominoGen::BuildBlockArray(pieceSize);

		
		// calculate unique number based on seed generrated from the rotated array
	}
	
	return UPolyominoGen::BuildStringArrayFromInts(pieceSize, tArray);
}

int** UPolyominoGen::BuildBlockArray(int pieceSize)
{
	UE_LOG(LogTemp, Display, TEXT("Building block array"));

	UPROPERTY()
	int** tArray = new int* [pieceSize];
	for (int i = 0; i < pieceSize; i++)
	{
		tArray[i] = new int[pieceSize];
		for (int j = 0; j < pieceSize; j++)
			tArray[i][j] = 0;
	}

	tArray[0][0] = 1;

	UPROPERTY()
	int blocksInserted = 1;
	UPROPERTY()
	int** coords = new int* [pieceSize];

	coords[0] = new int[2];

	coords[0][0] = 0;
	coords[0][1] = 0;

	while (blocksInserted < pieceSize)
	{
		UPROPERTY()
		bool inserted = false;
		while (!inserted)
		{
			UPROPERTY()
			int idx = FMath::RandRange(0, blocksInserted - 1);
			UPROPERTY()
			int* coord = coords[idx];
			UPROPERTY()
			int row = coord[1];
			UPROPERTY()
			int col = coord[0];

			UPROPERTY()
			int left = 1, right = 1, up = 1, down = 1;

			UPROPERTY()
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
				UE_LOG(LogTemp, Error, TEXT("Hit failsafe in BuildBlockArray"));
				break;
			}
		}
	}

	return tArray;
}

TArray<FString> UPolyominoGen::BuildStringArrayFromInts(int pieceSize, int** tArray)
{
	UE_LOG(LogTemp, Display, TEXT("Building string array"));
	TArray<FString> StringArray;

	for (int i = 0; i < pieceSize; i++)
	{
		UPROPERTY()
		bool cont = false;
		UPROPERTY()
		std::string ret = "";

		for (int j = 0; j < pieceSize; j++)
		{
			if (tArray[i][j]) cont = true;
			ret += std::to_string(tArray[i][j]);
		}
		if (cont)
			StringArray.Emplace(UTF8_TO_TCHAR(ret.c_str()));
		else
			break;
	}

	for (FString N : StringArray) {
		UE_LOG(LogTemp, Display, TEXT("%s"), *N);
	}
	return StringArray;
}

// TODO use if have time, otherwise delete
void Rotate(int pieceSize, int** tArray) {
	// find flattest side(s)
	UPROPERTY()
	int leftSize = 0, rightSize = 0, topSize = 0, bottomSize = 0;

	for (int i = 0; i < pieceSize; i++)
	{
		if (tArray[i][0] == 1) leftSize++;
		if (tArray[i][pieceSize] == 1) rightSize++;
		if (tArray[0][i] == 1) bottomSize++;
		if (tArray[pieceSize][i] == 1) topSize++;
	}
	UPROPERTY()
	int min = leftSize, max = leftSize;

	if (rightSize < min) min = rightSize;
	if (topSize < min) min = topSize;
	if (bottomSize < min) min = bottomSize;
	if (rightSize > max) max = rightSize;
	if (topSize > max) max = topSize;
	if (bottomSize > max) max = bottomSize;

	// rotate array so flattest side is on bottom
	//    in case of 3, put least flat side on top
	if (max == bottomSize) {} // if the bottom is already the flattest, do nothing
	else if (max == rightSize)
	{
		// TODO rotate 90
	}
	else if (max == topSize)
	{
		// TODO rotate 180
	}
	else if (max == leftSize)
	{
		// TODO rotate 270
	}

	// calculate rotations available based on flattest sides
	//    if 2 -> 2 rotations (0 and 90)
	//    if 4 -> 1 rotation  (0)
	//    else -> 4 rotations (0, -90, 180, and 90)
	UPROPERTY()
	int numFlatSides = 0;
	if (max == bottomSize) numFlatSides++;
}
