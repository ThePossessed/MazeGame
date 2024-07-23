// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MazeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MAZEGAME_API UMazeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UMazeGameInstance();

	UFUNCTION(BlueprintCallable)
	void SetMazeSize(int32 size);

	UFUNCTION(BlueprintCallable)
	int32 GetMazeSize();
	
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int32 MazeSize;
};
