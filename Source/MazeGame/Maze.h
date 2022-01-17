// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Maze.generated.h"

UCLASS()
class MAZEGAME_API AMaze : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMaze();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	const int32 MAZE_SIZE = 21;

	TArray<TArray<TArray<bool>>> passages;
	TArray<TArray<int32>> done;
	TArray<TArray<int32>> frontier;
	TArray<TArray<int32>> unexplored;
	TArray<int32> lastExploredLocation;

	const int32 wallWidth = 100;
	const int32 passageWidthToWallWidthRatio = 2;
	const int32 mapLength = wallWidth * (MAZE_SIZE * passageWidthToWallWidthRatio + MAZE_SIZE + 1);
	const int32 height = 400;

	const int32 EAST = 1;
	const int32 NORTH = 0;
	const int32 SOUTH = 2;
	const int32 WEST = 3;

	const int32 X = 0;
	const int32 Y = 1;

	const int32 OFFSETS[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

	void AddPassage(TArray<int32> a, TArray<int32> b);
	TArray<int32> ChooseRandomlyFrom(TArray<TArray<int32>> list);
	TArray<int32> ExpandLocation(TArray<int32> here, int32 direction);
	TArray<int32> ExpandMaze();
	void GenerateMaze();
	void SpawnCorner();
	void SpawnWalls();

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Floor;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> WallClass;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> CornerClass;

};
