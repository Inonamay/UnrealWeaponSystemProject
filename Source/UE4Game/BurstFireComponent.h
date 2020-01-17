#pragma once
#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Components/ActorComponent.h"
#include "BurstFireComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API UBurstFireComponent : public UEventActorComponent
{
	GENERATED_BODY()
	AWeaponBase* WeaponActor;
public:	

	UBurstFireComponent();

protected:
	virtual void BeginPlay() override;

public:	

	UFUNCTION(Category = "Fire Mode")
	void OnProjectilePrime();
		
};
