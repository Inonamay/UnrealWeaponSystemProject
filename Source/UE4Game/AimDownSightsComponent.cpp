#include "AimDownSightsComponent.h"
#include "WeaponBase.h"
// Sets default values for this component's properties
UAimDownSightsComponent::UAimDownSightsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UAimDownSightsComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAimDownSightsComponent::Aim()
{
	Owner->AddActorLocalOffset(Location);
	Owner->AddActorLocalRotation(Rotation);
}

void UAimDownSightsComponent::UnAim()
{
	Owner->SetActorRelativeLocation({0,0,0});
	Owner->SetActorRelativeRotation({0,0,0});;
}


// Called every frame
void UAimDownSightsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

