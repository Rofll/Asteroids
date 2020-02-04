#pragma once

#include "BaseComponent.h"
#include "Framework.h"

enum class InpustState
{
	None = 0,
	Stay
};

class InputComponent : public BaseComponent
{
public:
	InputComponent();
	~InputComponent();

	void OnButtonDown(FRKey key);
	void OnButtonRelease(FRKey key);
	void OnMouseDown(FRMouseButton key);
	void OnMouseRelease(FRMouseButton key);

	void Tick() override;

private:

	InpustState inputState = InpustState::None;
};

