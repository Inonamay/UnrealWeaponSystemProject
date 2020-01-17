#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitLocator.h"
#include "BulletBase.generated.h"
UCLASS()
class UE4GAME_API ABulletBase : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* ProjectileMesh;
	
public:	
	ABulletBase();
	UStaticMeshComponent* GetProjectileMesh();
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		TSubclassOf<class AHitLocator> DebugLocator;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
	float HitDamage;
	void CreateDebugLocator(FVector Location);
	void CreateDebugLocator(FVector Location, AActor* AttachmentActor);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
	float LifeTime = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
		float Force = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
		bool Gravity = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
		bool StopsMovingAfterCollision = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
		float TimeAliveAfterBounces = 0.1f;
	void Launch();
	UFUNCTION(BlueprintCallable)
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Properties")
		int HitsBeforeDestroyed = 1;
};
