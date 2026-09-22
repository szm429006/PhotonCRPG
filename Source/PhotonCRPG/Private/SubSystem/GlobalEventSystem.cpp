// Fill out your copyright notice in the Description page of Project Settings.


#include "SubSystem/GlobalEventSystem.h"

void UGlobalEventSystem::Deinitialize()
{
    Super::Deinitialize();
    OnInteractFinishDelegate.Clear();
}

void UGlobalEventSystem::BroadcastInteractFinish() const
{
    if (OnInteractFinishDelegate.IsBound())
    {
        OnInteractFinishDelegate.Broadcast();
    }
}
