// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePlate.h"


// Sets default values for this component's properties
UPressurePlate::UPressurePlate()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPressurePlate::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ActorThatWins = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}


// Called every frame
void UPressurePlate::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwner()->IsOverlappingActor(ActorThatWins)){
		ChangeScene();
	}

	// ...
}

void UPressurePlate::ChangeScene()
{
	// ...
	UE_LOG(LogTemp, Error, TEXT("aaaaaaaaaaaaaaaaaa"));
}
