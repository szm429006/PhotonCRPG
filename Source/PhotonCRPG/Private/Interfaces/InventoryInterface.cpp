// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InventoryInterface.h"
#include "UI/Inventory/InventorySlot.h"

// Add default functionality here for any IInventoryInterface functions that are not pure virtual.

UUserWidget* IInventoryInterface::GetInfoPanel()
{
	return nullptr;
}

void IInventoryInterface::ShowInfoPanel(UInventorySlot* HoverItem)
{
    StartHoverTick();
}

void IInventoryInterface::HideInfoPanel()
{
    EndHoverTick();
}

void IInventoryInterface::StartHoverTick()
{
}

void IInventoryInterface::OnHovering()
{
}

void IInventoryInterface::EndHoverTick()
{
}
