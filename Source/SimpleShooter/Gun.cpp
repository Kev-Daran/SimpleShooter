// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#define OUT // out parameter

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root); 
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::ShootGun()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccessHit = GunTrace(Hit, ShotDirection);

	AController* OwnerController = GetOwnerController();
	if(OwnerController == nullptr) return;

	if(bSuccessHit)
	{
		// DrawDebugPoint(GetWorld(), Hit.Location, 10, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);

		if(Hit.GetActor() != nullptr)
		{	
			FPointDamageEvent DamageEvent(DamageOfGun, Hit, ShotDirection, nullptr);
		 	Hit.GetActor()->TakeDamage(DamageOfGun, DamageEvent, OwnerController, this);
		}
	}
}


bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if(OwnerController == nullptr) return false;

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	OwnerController->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);


	FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector()*MaxReach);
	ShotDirection = -PlayerViewPointRotation.Vector();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(OUT Hit, PlayerViewPointLocation, LineTraceEnd, ECollisionChannel::ECC_GameTraceChannel11, Params);
}

AController* AGun::GetOwnerController()
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if(OwnerPawn == nullptr) return nullptr;

	AController* OwnerController = OwnerPawn->GetController();

	return OwnerController;
}