// Copyright 2025. Team Unique Turtle ; https://github.com/biomaticals. All rights reserved.
// All contents cannot be copied, distributed, revised.

#pragma once

#include "CoreMinimal.h"
#include "Common/HUtilityHelpers.h"

#define UT_LOG(CategoryName, Verbosity, Format, ...) \
	UE_LOG(CategoryName, Verbosity, TEXT("%hs(%d)"), __FUNCTION__, __LINE__); \
	UE_LOG(CategoryName, Verbosity, Format, ##__VA_ARGS__);

#define CHECK_REPLIACTE_COMPONENT() UKismetSystemLibrary::IsStandalone(this) == false && IsA(UActorComponent::StaticClass()) && Cast<UActorComponent>(this)->GetIsReplicated()

#define UT_LOG_OWNER_ROLE(CategoryName, Verbosity, RPCType) \
	UE_LOG(CategoryName, Verbosity, TEXT("Owner LocalRole = %s, RemoteRole = %s\n, Call "#RPCType" RPC function"), \
	GetOwner() ? *HUtilityHelpers::EnumToString((uint8)(GetOwner()->GetLocalRole()), TEXT("/Script/Engine.ENetRole")) : TEXT("Invalid"), \
	GetOwner() ? *HUtilityHelpers::EnumToString((uint8)(GetOwner()->GetRemoteRole()), TEXT("/Script/Engine.ENetRole")) : TEXT("Invalid"));

DECLARE_LOG_CATEGORY_EXTERN(HLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(HCharacterLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(HCharacterCustomizationLog, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(HSaveGameLog, Log, All); 