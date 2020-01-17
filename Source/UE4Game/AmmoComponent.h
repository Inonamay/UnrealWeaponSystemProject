#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletBase.h"
#include "EventActorComponent.h"
#include "AmmoComponent.generated.h"
USTRUCT(BlueprintType)
struct FMagazines
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		TSubclassOf<class ABulletBase> bulletType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		int MagazineSize = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
		int LoadedAmmo = 1;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class UE4GAME_API UAmmoComponent : public UEventActorComponent
{
	GENERATED_BODY()

public:	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	TArray<FMagazines> Magazines;

	UFUNCTION(BlueprintCallable)
	void OnFire();

	UFUNCTION(BlueprintCallable)
	void OnFireSuccess();
	
	UFUNCTION(BlueprintCallable)
	int Reload(int AvailableAmmo, int BulletIndex = 0);
	//BulletIndex : index of the bullet you want to check in Bullets 
	//UseCount : # of ammo to use
	//RemainingAmmo : # of ammo remaining post method
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	bool UseAmmoAndGetRemaining(int BulletIndex, int UseCount, int& RemainingAmmo);
	TSubclassOf<class ABulletBase> GetCurrentAmmo(int BulletIndex = 0);
	//BulletIndex : index of the bullet you want to check in Bullets 
	//UseCount : # of ammo to use
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	bool UseAmmo();

	bool TestAmmo(int BulletIndex = 0, int UseCount = 1);
		

	int GetCurrentAmmoIndex() { return CurrentAmmo; };
	void SetCurrentAmmoIndex(int index = 0);
private:
	int CurrentAmmo = 0;
	int NumberOfAmmoToUse = 1;
	bool UseAmmoImpl(int BulletIndex, int UseCount);
	bool Validate(int BulletIndex);

	void EventDispatch(bool Result);
};
