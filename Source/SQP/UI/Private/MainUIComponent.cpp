#include "MainUIComponent.h"

#include "UIManager.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


UMainUIComponent::UMainUIComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	LikeUIComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("LikeWidget"));

	ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(
		TEXT("Class'/Game/Splatoon/UI/WBP_LikeUI.WBP_LikeUI_C'"));
	if (WidgetClassFinder.Succeeded())
	{
		LikeUIComp->SetWidgetClass(WidgetClassFinder.Class);
	}
	LikeUIComp->SetupAttachment(this);
	LikeUIComp->SetWidgetSpace(EWidgetSpace::World);
	LikeUIComp->SetDrawSize(FVector2D(150.f, 50.f));
}


void UMainUIComponent::BeginPlay()
{
	Super::BeginPlay();
	
	LikeUIComp->SetupAttachment(GetOwner()->GetRootComponent());
	LikeUIComp->SetRelativeLocation(FVector(0, 0, 130));


	UIManager = GetWorld()->GetGameInstance()->GetSubsystem<UUIManager>();

	UIManager->CreateMainUI();
}


void UMainUIComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	BillboardLikeUI();
}

void UMainUIComponent::BillboardLikeUI()
{
	// 내가 컨트롤하고 있는 카메라를 가져오자.
	auto* Cam = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	// 카메라의 앞 방향 (반대), 윗 방향을 이용해서 Rotator 를 구하자.
	FRotator Rot = UKismetMathLibrary::MakeRotFromXZ(-Cam->GetActorForwardVector(), Cam->GetActorUpVector());
	// 구한 Rotator 를 comHP 에 설정
	LikeUIComp->SetWorldRotation(Rot);
}
