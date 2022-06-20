#pragma once
#include <JuceHeader.h>
#include "../Parameters.h"

class ParameterModulation
{
public:
	ParameterModulation();
	~ParameterModulation();

	void prepareToPlay(double sr);

	void setParameter(float newValue);

	void setModAmount(float newValue);

	void processBlock(AudioBuffer<float>& buffer, const int numSamples);

private:
	SmoothedValue<float, ValueSmoothingTypes::Linear> modAmount;
	SmoothedValue<float, ValueSmoothingTypes::Linear> parameter;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterModulation)
};