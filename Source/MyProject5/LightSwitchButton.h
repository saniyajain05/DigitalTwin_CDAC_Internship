// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSwitchButton.generated.h"

UCLASS()
class MYPROJECT5_API ALightSwitchButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitchButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
		class UPointLightComponent* PointLight;

	// declare sphere comp
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
		class USphereComponent* LightSphere;

	// declare light intensity variable
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
		float LightIntensity;

	// declare ToggleLight function
	UFUNCTION(BlueprintCallable, Category = "Light Switch")
		void ToggleLight();

	FTimerHandle ToggleTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Light")
		float ToggleInterval;

	UFUNCTION(BlueprintCallable, Category = "Light Switch")
		void SwitchOn();

	UFUNCTION(BlueprintCallable, Category = "Light Switch")
		void SwitchOff();

};

