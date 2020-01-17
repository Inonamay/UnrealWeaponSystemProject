#pragma once

#include "CoreMinimal.h"
#include "EventActorComponent.h"
#include "WeaponBase.h"
#include "Components/ActorComponent.h"
#include "SingleFiringComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API USingleFiringComponent : public UEventActorComponent
{
	GENERATED_BODY()

public:	
	USingleFiringComponent();

protected:
	virtual void BeginPlay() override;
	AWeaponBase* WeaponActor;

public:	

	UFUNCTION(BlueprintCallable, Category = "Weapon Events")
	void OnFirePressed();

	UFUNCTION(BlueprintCallable, Category = "Weapon Events")
	void OnFireReleased();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Fire Mode")
	float FireCooldown;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Fire Mode")
	float FireCooldownAccu;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Fire Mode")
	bool FireState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Weapon Fire Mode")
	float TriggerPower = 1.0f;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
