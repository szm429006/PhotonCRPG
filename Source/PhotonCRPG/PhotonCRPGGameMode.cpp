// Copyright Epic Games, Inc. All Rights Reserved.

#include "PhotonCRPGGameMode.h"
#include "PhotonCRPGPlayerController.h"
#include "PhotonCRPGCharacter.h"
#include "Public/Function/GlobalFunc.h"
#include "SubSystem/UISystem.h"
#include "UI/GameUI.h"
#include "Function/GlobalFunc.h"
#include "UObject/ConstructorHelpers.h"
#include "SubSystem/SquadSystem.h"
#include "ArticyFlowPlayer.h"
#include "Interfaces/ArticyObjectWithMenuText.h"
#include "Interfaces/ArticyObjectWithDisplayName.h"
#include "Interfaces/ArticyObjectWithSpeaker.h"
#include "Interfaces/ArticyNode.h"
#include "SubSystem/DialogueSystem.h"


APhotonCRPGGameMode::APhotonCRPGGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = APhotonCRPGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/BP_Camera"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	ArticyPlayer = CreateDefaultSubobject<UArticyFlowPlayer>(TEXT("ArticyPlayer"));
	ArticyPlayer->OnPlayerPaused.AddDynamic(this, &APhotonCRPGGameMode::OnArticyPlayerPaused);
}

void APhotonCRPGGameMode::BeginPlay()
{
	Super::BeginPlay();
	UGlobalFunc::GetSubsystem<USquadSystem>()->LoadPlayer();
	UGlobalFunc::GetSubsystem<UUISystem>()->LoadUI<UGameUI>(TEXT("/Game/Widget/WBP_GameUI.WBP_GameUI_C"));
	//GEngine->GameViewport->GetWorld()->GetGameInstance()->GetSubsystem<UUISystem>()->LoadUI<UGameUI>();

	ArticyPlayer->OnBranchesUpdated.AddDynamic(this, &APhotonCRPGGameMode::OnArticyBranchesUpdated);
}

void APhotonCRPGGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::LevelTransition)
	{
		ArticyPlayer->OnPlayerPaused.Clear();
		ArticyPlayer->OnBranchesUpdated.Clear();
	}
}

void APhotonCRPGGameMode::ArticyPlayDialogueById(const int32 ArticyID) const
{
	FArticyId ID;
	ID.Low = ArticyID;
	ID.High = 16777216;
	ArticyPlayer->SetStartNodeById(ID);
}

void APhotonCRPGGameMode::ArticyPlayDialogue(const FArticyRef Ref) const
{
	ArticyPlayer->SetStartNode(Ref);
}

void APhotonCRPGGameMode::ArticyEndDialogue() const
{
	ArticyPlayer->FinishCurrentPausedObject(0);
}

void APhotonCRPGGameMode::OnArticyPlayerPaused(TScriptInterface<IArticyFlowObject> PausedOn)
{
	UGlobalFunc::GetSubsystem<UDialogueSystem>()->ShowDialogueItem(ArticyPlayer, PausedOn);
}

void APhotonCRPGGameMode::OnArticyBranchesUpdated(const TArray<FArticyBranch>& AvailableBranches)
{
	UGlobalFunc::GetSubsystem<UDialogueSystem>()->UpdateOptionItem(ArticyPlayer, AvailableBranches);
}
