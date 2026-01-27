// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleReactive.h"

APuzzleReactive::APuzzleReactive()
{
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
}

