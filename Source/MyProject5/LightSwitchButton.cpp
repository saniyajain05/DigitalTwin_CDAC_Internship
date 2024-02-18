// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitchButton.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ALightSwitchButton::ALightSwitchButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LightIntensity = 3000.0f;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->Intensity = LightIntensity;
	PointLight->SetVisibility(true);
	PointLight->SetLightFColor(FColor::Red);
	PointLight->SetCastShadows(false);
	RootComponent = PointLight;

	LightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Light Sphere Component"));
	LightSphere->InitSphereRadius(300.0f);
	LightSphere->SetCollisionProfileName(TEXT("Trigger"));
	LightSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	LightSphere->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ALightSwitchButton::BeginPlay()
{
	Super::BeginPlay();

	//DrawDebugSphere(GetWorld(), GetActorLocation(), 350.0f, 50, FColor::Green, true, -1, 0, 2);
	
}

// Called every frame
void ALightSwitchButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALightSwitchButton::ToggleLight()
{
	PointLight->ToggleVisibility();
}

void ALightSwitchButton::SwitchOn()
{
	PointLight->SetIntensity(LightIntensity);
}

void ALightSwitchButton::SwitchOff()
{
	PointLight->SetIntensity(0.0f);
}