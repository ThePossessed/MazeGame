// Fill out your copyright notice in the Description page of Project Settings.
#include "Maze.h"
#include "Math/UnrealMathUtility.h"
// Sets default values
AMaze::AMaze()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floor"));
	RootComponent = Floor;
}

// Called when the game starts or when spawned
void AMaze::BeginPlay()
{
	Super::BeginPlay();
	GenerateMaze();
}

// Called every frame
void AMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMaze::AddPassage(TArray<int32> a, TArray<int32> b)
{
	if ((b[0] - a[0] == 1) && (b[1] == a[1])) passages[a[0]][a[1]][EAST] = true;
	else if ((b[0] - a[0] == -1) && (b[1] == a[1])) passages[a[0]][a[1]][WEST] = true;
	else if ((b[1] - a[1] == 1) && (b[0] == a[0])) passages[a[0]][a[1]][NORTH] = true;
	else if ((b[1] - a[1] == -1) && (b[0] == a[0])) passages[a[0]][a[1]][SOUTH] = true;
}

TArray<int32> AMaze::ChooseRandomlyFrom(TArray<TArray<int32>> list)
{
	if (list.Num() == 0) return {-10, -10};
	int index = FMath::RandRange(0, list.Num() - 1);
	return list[index];
}

TArray<int32> AMaze::ExpandLocation(TArray<int32> here, int32 direction)
{
	TArray<int32> there = {0, 0};
	there[X] = here[X] + OFFSETS[direction][X];
	there[Y] = here[Y] + OFFSETS[direction][Y];
	if (unexplored.Find(there) != INDEX_NONE) 
	{
		AddPassage(here, there);
		return there;
	} 
	else return {-10, -10};
}

TArray<int32> AMaze::ExpandMaze()
{
	TArray<int32> here;
	if (lastExploredLocation[0] == -10 && lastExploredLocation[1] == -10) here = ChooseRandomlyFrom(frontier);
	else here = lastExploredLocation;

	int32 direction = FMath::RandRange(0, 3);
	for (int32 i = 0; i < 4; i++) 
	{
		TArray<int32> there = ExpandLocation(here, direction); 
		if (!(there[0] == -10 && there[1] == -10))
		{
			frontier.Insert(there, 0);
			unexplored.Remove(there);
			return there;
		}
		direction = (direction + 1) % 4;
	}
	done.Insert(here, 0);
	frontier.Remove(here);
	return {-10, -10};
}

void AMaze::GenerateMaze()
{
	TArray<TArray<bool>> passage;
	passage.Init({false, false, false, false}, MAZE_SIZE);
	passages.Init(passage, MAZE_SIZE);

	frontier = {{ 0, 0 }};
	lastExploredLocation = {-10, -10};

	int32 i = 0;
	for (int x = 0; x < MAZE_SIZE; x++) 
	{
		for (int y = 0; y < MAZE_SIZE; y++) 
		{
			unexplored.Insert({ x, y }, 0);
			i++;
		}
	}
	unexplored.Remove({0, 0});

	SpawnCorner();

	while (unexplored.Num() > 0) 
	{
		lastExploredLocation = ExpandMaze();
	}

	SpawnWalls();
}

void AMaze::SpawnCorner()
{
	FVector SpawnLocation;
	SpawnLocation.X = 0.0;
	SpawnLocation.Y = 0.0;
	SpawnLocation.Z = height / 2;

	FRotator SpawnRotation;
	SpawnRotation.Roll = 0.0;
	SpawnRotation.Pitch = 0.0;
	SpawnRotation.Yaw = 0.0;

	for (int i = 0; i < MAZE_SIZE + 1; i++)
	{
		for (int j = 0; j < MAZE_SIZE + 1; j++)
		{
			SpawnLocation.X = i * wallWidth * (1 + passageWidthToWallWidthRatio) + wallWidth / 2;
			SpawnLocation.Y = j * wallWidth * (1 + passageWidthToWallWidthRatio) + wallWidth / 2;
			GetWorld()->SpawnActor<AActor>(CornerClass, SpawnLocation, SpawnRotation);
		}
	}
}

void AMaze::SpawnWalls()
{
	FVector SpawnLocation;
	SpawnLocation.X = 0.0;
	SpawnLocation.Y = 0.0;
	SpawnLocation.Z = height / 2;

	FRotator SpawnRotation;
	SpawnRotation.Roll = 0.0;
	SpawnRotation.Pitch = 0.0;

	for (int i = 0; i < MAZE_SIZE; i++)
	{
		SpawnRotation.Yaw = 90.0;
		if (i != 0)
		{
			SpawnLocation.X = wallWidth * (i * (1 + passageWidthToWallWidthRatio) + passageWidthToWallWidthRatio / 2 + 1);
			SpawnLocation.Y = wallWidth / 2;
			GetWorld()->SpawnActor<AActor>(WallClass, SpawnLocation, SpawnRotation);
		}

		SpawnLocation.X = wallWidth * (i * (1 + passageWidthToWallWidthRatio) + passageWidthToWallWidthRatio / 2 + 1);
		SpawnLocation.Y = mapLength - wallWidth / 2;
		GetWorld()->SpawnActor<AActor>(WallClass, SpawnLocation, SpawnRotation);

		SpawnRotation.Yaw = 0.0;
		SpawnLocation.X = wallWidth / 2;
		SpawnLocation.Y = wallWidth * (i * (1 + passageWidthToWallWidthRatio) + passageWidthToWallWidthRatio / 2 + 1);
		GetWorld()->SpawnActor<AActor>(WallClass, SpawnLocation, SpawnRotation);

		if (i != MAZE_SIZE - 1)
		{
			SpawnLocation.X = mapLength - wallWidth / 2;
			SpawnLocation.Y = wallWidth * (i * (1 + passageWidthToWallWidthRatio) + passageWidthToWallWidthRatio / 2 + 1);
			GetWorld()->SpawnActor<AActor>(WallClass, SpawnLocation, SpawnRotation);
		}
	}
	for (int x = 0; x < passages.Num(); x++)
	{
		for (int y = 0; y < passages.Num(); y++)
		{
			if (!(passages[x][y][NORTH] || ((y + 1 < passages.Num()) && passages[x][y + 1][SOUTH])))
			{
				SpawnRotation.Yaw = 90.0;
				SpawnLocation.X = wallWidth * (x * (1 + passageWidthToWallWidthRatio) + passageWidthToWallWidthRatio / 2 + 1);
				SpawnLocation.Y = (y + 1) * wallWidth * (1 + passageWidthToWallWidthRatio) + wallWidth / 2;
				GetWorld()->SpawnActor<AActor>(WallClass, SpawnLocation, SpawnRotation);
			}
			if (!(passages[x][y][EAST] || ((x + 1 < passages.Num()) && passages[x + 1][y][WEST])))
			{
				if (!((x == passages.Num() - 1) && (y == passages.Num() - 1)))
				{
					SpawnRotation.Yaw = 0.0;
					SpawnLocation.X = (x + 1) * wallWidth * (1 + passageWidthToWallWidthRatio) + wallWidth / 2;
					SpawnLocation.Y = wallWidth * (y * (1 + passageWidthToWallWidthRatio) + passageWidthToWallWidthRatio / 2 + 1);
					GetWorld()->SpawnActor<AActor>(WallClass, SpawnLocation, SpawnRotation);
				}
			}
		}
	}
}
