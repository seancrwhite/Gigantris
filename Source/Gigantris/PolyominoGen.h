// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PolyominoGen.generated.h"

/**
 * 
 */
UCLASS()
class GIGANTRIS_API UPolyominoGen : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
private:
	static TArray<FString> BuildStringArrayFromInts(int pieceSize, int** tArray);
	static int** BuildBlockArray(int pieceSize);
public:
	UFUNCTION(BlueprintCallable, DisplayName = "Calculate String Array", Category = "PolyominoGen")
	static TArray<FString> CalcStringArray(const int pieceSize);
};
