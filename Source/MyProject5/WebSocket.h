// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IWebSocket.h"
#include "WebSocket.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UWebSocket : public UGameInstance
{
	GENERATED_BODY()

public: 

	virtual void Init() override;
	virtual void Shutdown() override;
	FString myId;
	TSharedPtr<IWebSocket> WebSocket;

	UFUNCTION()
	void displayLight();

	UFUNCTION()
		void displayLight_On();

	FTimerHandle TimerHandle_displayLight;

	FTimerHandle TimerHandle_displayLight_On;

	void ToggleLigthWebSocket();

	int count = 0;

	
	
};
