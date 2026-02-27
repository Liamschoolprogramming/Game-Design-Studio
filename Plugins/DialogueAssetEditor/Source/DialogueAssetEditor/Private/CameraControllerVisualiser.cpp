#include "CameraControllerVisualiser.h"

void FCameraControllerVisualiser::DrawVisualization(const UActorComponent* Component, const FSceneView* View,
                                                    FPrimitiveDrawInterface* PDI)
{
	const UCameraControlComponent* CamComp =
		Cast<UCameraControlComponent>(Component);

	if (!CamComp)
		return;

	const FVector Location = CamComp->GetComponentLocation();
	const FVector Forward = CamComp->GetComponentRotation().Vector();

	const float FocusDist = CamComp->FocusDistance;
	
	PDI->DrawLine( Location, Location + Forward * FocusDist, FColor(255,0,0), SDPG_World );
	
}

bool FCameraControllerVisualiser::HandleInputDelta(FEditorViewportClient* ViewportClient, FViewport* Viewport,
	FVector& DeltaTranslate, FRotator& DeltaRotate, FVector& DeltaScale)
{
	return FComponentVisualizer::HandleInputDelta(ViewportClient, Viewport, DeltaTranslate, DeltaRotate, DeltaScale);
}
