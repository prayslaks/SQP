#include "SkyViewComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SkyViewPawn.h"
#include "Camera/CameraComponent.h"

USkyViewComponent::USkyViewComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	ConstructorHelpers::FObjectFinder<UInputAction> SkyViewAsset(
		TEXT("'/Game/Splatoon/Input/IA_SkyView.IA_SkyView'")
	);
	if (SkyViewAsset.Succeeded())
	{
		SkyViewAction = SkyViewAsset.Object;
	}

	ConstructorHelpers::FObjectFinder<UInputMappingContext> IMCAsset(
		TEXT("'/Game/Input/IMC_Default.IMC_Default'")
	);
	if (IMCAsset.Succeeded())
	{
		IMC = IMCAsset.Object;
	}
}


void USkyViewComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerPawn = Cast<APawn>(GetOwner());

	Server_SpawnSkyViewPawn();

	if (OwnerPawn->IsLocallyControlled())
	{
		// Enhanced Input Subsystem 등록
		PlayerController = Cast<APlayerController>(OwnerPawn->GetController());
		if (PlayerController)
		{
			if (auto* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				PlayerController->GetLocalPlayer()))
			{
				InputSubsystem->AddMappingContext(IMC, 0);
			}

			// 입력 바인딩
			if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				if (SkyViewAction)
					EIC->BindAction(SkyViewAction, ETriggerEvent::Started, this, &USkyViewComponent::OnSkyView);
			}
		}
	}
}


void USkyViewComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USkyViewComponent::OnSkyView()
{
	Server_IsSkyView(PlayerController);
}

void USkyViewComponent::Server_SpawnSkyViewPawn_Implementation()
{
	FVector Loc = GetOwner()->GetComponentByClass<UCameraComponent>()->GetComponentLocation() +
		InitialLocationOffset;
	FRotator Rot = GetOwner()->GetActorRotation();
	Rot.Pitch = InitialPitchOffset;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	SkyViewPawn = GetWorld()->SpawnActor<ASkyViewPawn>(
		ASkyViewPawn::StaticClass(),
		Loc,
		Rot,
		SpawnParams
	);
}

void USkyViewComponent::Server_IsSkyView_Implementation(APlayerController* PC)
{
	if (bIsSkyView) // Sky View On
	{
		Server_ResetSkyViewLocation(bIsSkyView);
		Server_PossessSkyView(bIsSkyView, PC);
		bIsSkyView = false;
		return;
	}
	// Sky View Off
	Server_ResetSkyViewLocation(bIsSkyView);
	Server_PossessSkyView(bIsSkyView, PC);
	bIsSkyView = true;
}

void USkyViewComponent::Server_ResetSkyViewLocation_Implementation(bool isSkyView)
{
	if (isSkyView) // Change view to Sky View
	{
		FVector Loc = GetOwner()->GetComponentByClass<UCameraComponent>()->GetComponentLocation() +
			InitialLocationOffset;
		FRotator Rot = GetOwner()->GetActorRotation();
		Rot.Pitch = InitialPitchOffset;

		SkyViewPawn->SetActorTransform(FTransform(Rot, Loc));
	}
}

void USkyViewComponent::Server_PossessSkyView_Implementation(bool isSkyView, APlayerController* PC)
{
	if (isSkyView)
	{
		PC->Possess(SkyViewPawn);
		return;
	}
	if (isSkyView == false) // Change view to Character View
	{
		PC->Possess(OwnerPawn);
	}
}
