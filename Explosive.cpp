// Fill out your copyright notice in the Description page of Project Settings.

#include "Explosive.h"
#include "Main.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"

AExplosive::AExplosive()
{
	Damage = 15.f;
}

void AExplosive::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	//UE_LOG(LogTemp, Warning, TEXT("Explosive::OnOverlapBegin()"));

	if (OtherActor)
	{
		AMain* Main = Cast<AMain>(OtherActor); // if OtherActor is not AMain, Main variable is filled with NULL
		AEnemy* Enemy = Cast<AEnemy>(OtherActor);

		USphereComponent* Comp = Cast<USphereComponent>(OtherComp);

		if ( (Enemy && Comp != Enemy->AgroSphere) || Main )
		{
			if (OverlapParticles)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OverlapParticles, GetActorLocation(), FRotator(0.f), true);
			}

			if (OverlapSound)
			{
				UGameplayStatics::PlaySound2D(this, OverlapSound);
			}

			//Main->DecrementHealth(Damage);
			UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, DamageTypeClass);
			Destroy();
		}
	}
	
}

void AExplosive::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	UE_LOG(LogTemp, Warning, TEXT("Explosive::OnOverlapEnd()"));
}
