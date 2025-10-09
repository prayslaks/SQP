# Yeomin C++ 코딩 컨벤션 (Unreal Engine 5.6)

## 1. 파일 헤더 (File Header)
모든 `.h` 및 `.cpp` 파일은 다음 저작권 문구로 시작합니다.
```cpp
// Copyright (c) 2025 Yeomin-Yoon. All rights reserved. Unauthorized copying, modification, or distribution of this file, via any medium is strictly prohibited. Proprietary and confidential.
```

## 2. 네이밍 컨벤션 (Naming Conventions)

### 2.1. 클래스, 구조체, 열거형 (Classes, Structs, Enums)
*   **클래스:** 언리얼 엔진 표준 접두사(`A` for Actor, `U` for UObject, `I` for Interface)를 사용하고 `PascalCase`를 따릅니다.
    *   예: `AActor`, `UObject`, `APlayerActor`, `UStatSystem`, `IControllable`
*   **구조체:** `F` 접두사를 사용하고 `PascalCase`를 따릅니다.
    *   예: `FVector`, `FRotator`, `FHitStopData`, `FParabolaBallisticTrack`
*   **열거형:** `E` 접두사를 사용하고 `PascalCase`를 따릅니다.
    *   예: `EEaseType`, `EAttackPowerType`
*   **템플릿 클래스:** `T` 접두사를 사용하고 `PascalCase`를 따릅니다.
    *   예: `TArray`, `TMap`, `TSharedPtr`

### 2.2. 함수 (Functions)
*   `PascalCase`를 사용합니다.
    *   예: `StartupModule`, `OnPossess`, `InitSystem`, `GetPoolItem`

### 2.3. 변수 (Variables)
*   `camelCase`를 사용합니다.
    *   예: `selectedMapPackage`, `anchorLerpSpeed`, `elapsedTime`
*   **불리언 변수:** `b` 접두사를 사용하고 `PascalCase`를 따릅니다.
    *   예: `bStatFPSEnabled`, `bIsPlayer`, `bActive`
*   **입력 파라미터:** `In` 접두사를 사용합니다.
    *   예: `InOwner`, `InLongPackageName`, `InTargetActor`
*   **출력 파라미터:** `Out` 접두사를 사용합니다.
    *   예: `OutWorlds`, `OutRoot`

### 2.4. 매크로 (Macros)
*   `LOCTEXT_NAMESPACE`, `DEFINE_SUBSYSTEM_GETTER_INLINE`, `DECLARE_DYNAMIC_MULTICAST_DELEGATE`, `BIND_DYNAMIC_DELEGATE` 등 언리얼 엔진 표준 매크로를 사용합니다.

## 3. 포맷팅 (Formatting)

### 3.1. 중괄호 (Braces)
*   K&R 스타일을 따릅니다. 즉, 여는 중괄호(`{`)는 문장과 같은 줄에 위치합니다.
    ```cpp
    void MyFunction()
    {
        // ...
    }
    ```

### 3.2. 들여쓰기 (Indentation)
*   4칸 공백(spaces)을 사용합니다.

### 3.3. 공백 (Spacing)
*   연산자(`=`, `+`, `-`, `*`, `/`, `==`, `!=`, `<`, `>`), 콤마(`,`), 키워드(`if`, `for`, `while`) 뒤에 일관된 공백을 사용합니다.

### 3.4. 줄 바꿈 (Line Breaks)
*   논리적인 코드 블록 사이, 특히 `UPROPERTY()` / `UFUNCTION()` 매크로 블록 뒤와 함수 정의 사이에 빈 줄을 사용하여 가독성을 높입니다.

## 4. 주석 스타일 (Commenting Style)

### 4.1. 문서화 주석 (Documentation Comments)
*   클래스, 구조체, 열거형, 함수, 프로퍼티 등 Blueprint에 노출되거나 문서화가 필요한 요소에는 Doxygen 스타일 주석(`/** ... */`)을 사용합니다.
    ```cpp
    /**
     * @brief 주어진 시간 안에 목표 지점에 도달하기 위한 초기 속도를 계산합니다.
     * ...
     */
    static FVector SolveV0ForProjectile(...);
    ```

### 4.2. 인라인 주석 (Inline Comments)
*   단일 라인 주석은 `//`를 사용합니다.
*   코드 블록 주석은 `/* ... */`를 사용합니다.
*   `#pragma region` 및 `#pragma endregion`을 사용하여 관련 코드 블록을 그룹화하고 정리합니다.

## 5. 헤더 파일 관리 (Header File Management)

### 5.1. `#pragma once`
*   모든 헤더 파일에 `#pragma once`를 사용하여 다중 포함을 방지합니다.

### 5.2. `#include` 순서
*   프로젝트/모듈 내의 자체 헤더를 가장 먼저 포함합니다.
    *   예: `#include "FCoffeeToolbar.h"`
*   그 다음 언리얼 엔진 프레임워크 헤더를 포함합니다.
    *   예: `#include "ToolMenus.h"`
*   가능한 경우 전방 선언(Forward Declaration)을 적극적으로 활용하여 헤더 의존성을 최소화합니다.
    *   예: `class UMaterialInstanceDynamic;`

## 6. 언리얼 엔진 특정 컨벤션 (Unreal Engine Specific Conventions)

### 6.1. `GENERATED_BODY()`
*   `UCLASS()`, `USTRUCT()`, `UENUM()` 매크로 바로 아래에 `GENERATED_BODY()`를 배치합니다.

### 6.2. `UCLASS()`, `USTRUCT()`, `UENUM()`
*   적절한 클래스 그룹(`ClassGroup`), 메타 데이터(`meta`), 접근 지정자(`Config`, `DefaultConfig`)를 사용합니다.
    *   예: `UCLASS(Config=Game, DefaultConfig, meta=(DisplayName="CoffeeToolbar"))`
    *   예: `UENUM(BlueprintType)`

### 6.3. `UPROPERTY()`
*   다음과 같은 일반적인 지정자를 사용합니다.
    *   `EditAnywhere`, `BlueprintReadWrite`, `VisibleAnywhere`, `BlueprintReadOnly`
    *   `Category`: 명확하고 계층적인 카테고리 이름을 사용합니다.
    *   `meta`: `ClampMin`, `ClampMax`, `DisplayName`, `ToolTip`, `EditCondition`, `AllowPrivateAccess`, `WorldContext`, `DefaultToSelf`, `CompactNodeTitle`, `ArrayParm`, `ArrayTypeDependentParams` 등 필요한 메타데이터를 추가합니다.

### 6.4. `UFUNCTION()`
*   다음과 같은 일반적인 지정자를 사용합니다.
    *   `BlueprintCallable`, `BlueprintPure`, `BlueprintNativeEvent`
    *   `Category`: 명확하고 계층적인 카테고리 이름을 사용합니다.
    *   `meta`: `DisplayName`, `Keywords`, `WorldContext`, `DefaultToSelf` 등 필요한 메타데이터를 추가합니다.
    *   `CallInEditor`, `Exec` 등 에디터 전용 함수 지정자도 활용합니다.

### 6.5. 성능 최적화
*   작고 자주 호출되는 함수에는 `FORCEINLINE`을 사용하여 인라인화를 유도합니다.
*   `PrimaryComponentTick.bCanEverTick = true;`와 같이 Tick을 사용하는 컴포넌트는 Tick 로직을 최소화하고 필요한 경우에만 활성화합니다.

### 6.6. 문자열 처리
*   리터럴 문자열에는 `TEXT()` 매크로를 사용합니다.
    *   예: `TEXT("StatSystem")`
*   로그 출력에는 `UE_LOG`를 사용하며, `LogTemp` 또는 `DBSZ`와 같은 사용자 정의 로그 카테고리를 활용합니다.
    *   `DBSZ` 로그 카테고리는 `DECLARE_LOG_CATEGORY_EXTERN(DBSZ, Log, All);` 및 `DEFINE_LOG_CATEGORY(DBSZ);`로 정의됩니다.
*   `FString`, `FName`, `FText`를 용도에 맞게 사용합니다.

### 6.7. 컨테이너 (Containers)
*   `TArray`, `TMap` 등 언리얼 엔진 컨테이너를 사용합니다.

### 6.8. 수학 라이브러리 (Math Library)
*   `FVector`, `FRotator`, `FLinearColor` 등 언리얼 엔진의 수학 타입을 사용합니다.
*   `FMath` 유틸리티 함수를 적극적으로 활용합니다.

### 6.9. 이벤트 및 서브시스템 (Events and Subsystems)
*   `DECLARE_DYNAMIC_MULTICAST_DELEGATE`를 사용하여 Blueprint에서 바인딩 가능한 이벤트를 정의합니다.
*   `UGameInstanceSubsystem`을 활용하여 전역적인 매니저 및 이벤트 시스템을 구현합니다.
*   `DEFINE_SUBSYSTEM_GETTER_INLINE` 매크로를 사용하여 서브시스템 접근자를 간결하게 정의합니다.

---
