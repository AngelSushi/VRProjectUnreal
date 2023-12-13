#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Flashable.generated.h"

UINTERFACE(MinimalAPI)
class UFlashable : public UInterface
{
	GENERATED_BODY()
};


class VRPROJECT_API IFlashable
{
	GENERATED_BODY()

	
public:
	virtual void Flash() = 0;
};
