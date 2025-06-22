#include "ToggleButtonComponent.h"

namespace {
constexpr int buttonWidth = 100;
constexpr int buttonHeight = 50;
constexpr float toggleWidth = 50.0f;
constexpr float toggleHeight = 25.0f;
constexpr float toggleRadius = 10.0f;
constexpr float ellipseDiameter = 19.0f;
constexpr float ellipseYOffset = 3.0f;
constexpr float ellipseXOffsetOn = 0.0f;
constexpr float ellipseXOffsetOff = -22.0f;
}

ToggleButtonComponent::ToggleButtonComponent() {
	setMouseCursor(MouseCursor::PointingHandCursor);
	setSize(buttonWidth, buttonHeight);
}

ToggleButtonComponent::~ToggleButtonComponent() = default;

void ToggleButtonComponent::paint(Graphics& g) {
	const auto centerX = static_cast<float>(getWidth()) / 2.0f;
	const auto centerY = static_cast<float>(getHeight()) / 2.0f;

	g.setColour(Colours::darkgrey);
	g.fillRoundedRectangle(centerX - toggleWidth / 2.0f,
	                       centerY - toggleHeight / 2.0f,
	                       toggleWidth, toggleHeight, toggleRadius);

	if (getToggleState()) {
		g.setColour(Colours::green);
		g.fillEllipse(centerX + ellipseXOffsetOn,
		              centerY - toggleHeight / 2.0f + ellipseYOffset,
		              ellipseDiameter, ellipseDiameter);
	} else {
		g.setColour(Colours::red);
		g.fillEllipse(centerX + ellipseXOffsetOff,
		              centerY - toggleHeight / 2.0f + ellipseYOffset,
		              ellipseDiameter, ellipseDiameter);
	}
}