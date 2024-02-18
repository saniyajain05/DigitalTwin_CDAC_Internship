// Fill out your copyright notice in the Description page of Project Settings.


#include "WebSocket.h"
#include "WebSocketsModule.h"
#include "LightSwitchButton.h"
#include "MyProject5Character.h"
#include <iostream>
#include <windows.h>
#include "Kismet/GameplayStatics.h"



void UWebSocket::Init() {

	Super::Init();



	if (!FModuleManager::Get().IsModuleLoaded("WebSockets")) {

		FModuleManager::Get().LoadModule("WebSckets");
	}


	WebSocket = FWebSocketsModule::Get().CreateWebSocket("ws://localhost:8080");

	WebSocket->OnConnected().AddLambda([]() {

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Successfully Connected");

		});

	WebSocket->OnConnectionError().AddLambda([](const FString& Error) {

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, Error);
		});

	WebSocket->OnClosed().AddLambda([](int32 StatusCode, const FString& Reason, bool bWasClean) {

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, bWasClean ? FColor::Green : FColor::Red, "Connection Closed" + Reason);
		});

	WebSocket->OnMessage().AddLambda([this](const FString& MessageString) {


		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Recived Message: " + MessageString);

		if (MessageString.Contains("assigned id: ")) {
			TArray<FString> Substrings;
			int32 Start = 0;
			int32 End = 0;

			while ((End = MessageString.Find(":", ESearchCase::IgnoreCase, ESearchDir::FromStart, Start)) != INDEX_NONE)
			{
				Substrings.Add(MessageString.Mid(Start, End - Start));
				Start = End + 1;
			}

			// Push the last substring (or the only substring if no delimiter is found)
			Substrings.Add(MessageString.Mid(Start));

			myId = Substrings[1];
		}


		
		if (MessageString.Contains("Action")) {

			if (MessageString.Contains("OFF")) {
				displayLight();
			}
			else if (MessageString.Contains("ON")){
				displayLight_On();
			}


			/*if (!MessageString.Contains(myId)) {

				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Now I need to switch it on ");

			}
			else {
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "DoNothingThisisMe!!");
			}*/
		}

		
		});

	WebSocket->OnMessageSent().AddLambda([](const FString& MessageString) {

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Sent Message: " + MessageString);
		});

	WebSocket->Connect();

	
		
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle_displayLight, this, &UWebSocket::displayLight, 10.0f, true, 3);
	
	
	
}





void UWebSocket::Shutdown() {

	if (WebSocket->IsConnected()) {
		WebSocket->Close();
	}
	Super::Shutdown();

}

void UWebSocket::displayLight() {

	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALightSwitchButton::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		ALightSwitchButton* LightSwitchButton = Cast<ALightSwitchButton>(FoundActors[0]);

		if (LightSwitchButton) {


				LightSwitchButton->SwitchOff();

				// Handle the case when casting to ALightSwitchButton fails
				//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Found");

				//GetWorld()->GetTimerManager().SetTimer(TimerHandle_displayLight_On, this, &UWebSocket::displayLight_On, 5.0f, false);


		}
	}
	else
	{
		// Handle the case when no ALightSwitchButton instance is found in the level
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "No ALightSwitchButton instance found in the level");
	}

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "Light");

		count++;

		if (count >= 7)
		{
			// You can stop the timer here if you want to ensure it doesn't keep repeating.
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_displayLight);
		}
}

void UWebSocket::displayLight_On() {

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALightSwitchButton::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		ALightSwitchButton* LightSwitchButton = Cast<ALightSwitchButton>(FoundActors[0]);

		if (LightSwitchButton) {


			LightSwitchButton->SwitchOn();

			// Handle the case when casting to ALightSwitchButton fails
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Purple, "Found");

		


		}
	}
}



