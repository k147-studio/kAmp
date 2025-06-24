#include <JuceHeader.h>

#include "BasePedalComponent.h"

class OktaverEffectComponent : public BasePedalComponent {
public:
	OktaverEffectComponent(AbstractEffect* effect);
	~OktaverEffectComponent() override;
private:
	Grid grid;
	Slider mixSlider;
	Label mixLabel;
	Slider octaveShiftSlider;
	Label octaveShiftLabel;
	void setupSlidersAndLabels();
};