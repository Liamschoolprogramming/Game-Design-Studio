// Fill out your copyright notice in the Description page of Project Settings.


#include "GriefZone.h"

AGriefZone::AGriefZone()
{
	GriefEffect = CreateDefaultSubobject<UNiagaraComponent>("Grief Effect");
	RootComponent = GriefEffect;
}
