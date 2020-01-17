// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ShapeComponent.h"
#include "Components/BoxComponent.h"
#include "AOEComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4GAME_API UAOEComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAOEComponent();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AOEShape)
	int OverlapDamage = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AOEShape)
	bool bTriggersOnImpact = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AOEShape)
	bool bTickableDamage = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AOEShape)
		float TickRate = 1.0f;
	UFUNCTION(BlueprintCallable)
		void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void Impact(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UBoxComponent* GetAreaComponent();
	UBoxComponent* ComponentRef;
private:
	void DamageTick();
	FTimerHandle TickDamageTimerHandle;
public:	
	// Called every frame

		
};
