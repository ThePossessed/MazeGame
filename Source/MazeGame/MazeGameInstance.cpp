// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGameInstance.h"

// Sets default values
UMazeGameInstance::UMazeGameInstance()
{
    MazeSize = 12;
}

void UMazeGameInstance::SetMazeSize(int32 size)
{
    MazeSize = size;
}

int32 UMazeGameInstance::GetMazeSize()
{
    return MazeSize;
}