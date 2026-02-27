#pragma once
#include "CameraControlComponent.h"
#include "ComponentVisualizer.h"
#include "CameraControllerVisualiser.h"
class FCameraControllerVisualiser : public FComponentVisualizer
{
public:
public:

	virtual void DrawVisualization(
		const UActorComponent* Component,
		const FSceneView* View,
		FPrimitiveDrawInterface* PDI) override;

	virtual bool HandleInputDelta(
		FEditorViewportClient* ViewportClient,
		FViewport* Viewport,
		FVector& DeltaTranslate,
		FRotator& DeltaRotate,
		FVector& DeltaScale) override;

private:
	UCameraControlComponent* EditedComponent = nullptr;
};
