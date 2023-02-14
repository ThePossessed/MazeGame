// Copyright Epic Games, Inc. All Rights Reserved.


#include "MazeGameGameModeBase.h"

AMazeGameGameModeBase::AMazeGameGameModeBase()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
    PrimaryActorTick.bAllowTickOnDedicatedServer = false;

    DefaultPawnClass = APlayerCharacter::StaticClass();

}