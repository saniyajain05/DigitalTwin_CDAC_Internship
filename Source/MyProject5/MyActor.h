// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class MYPROJECT5_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
		TSubclassOf<class UUserWidget> InputWidgetClass;

	UUserWidget* InputWidget;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void ReceiveUserInput(FString InputText);

};
