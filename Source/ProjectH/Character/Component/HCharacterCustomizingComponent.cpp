// Copy Rigts are in Team UniqueTurtle. 


#include "Character/Component/HCharacterCustomizingComponent.h"

UHCharacterCustomizingComponent::UHCharacterCustomizingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UHCharacterCustomizingComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UHCharacterCustomizingComponent::InitializeComponent()
{
	Super::InitializeComponent();

}

void UHCharacterCustomizingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHCharacterCustomizingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}