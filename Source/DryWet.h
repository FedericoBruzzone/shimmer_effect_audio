#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

class DryWet
{
public:
	DryWet();
	~DryWet();

	void prepareToPlay(double sr, int maxNumSamples);

	void releaseResources();

	void setDry(const AudioBuffer<float>& buffer);

	void merge(AudioBuffer<float>& buffer);

	void setDryWetRatio(const float newValue);

private:

	float dryWetRatio = 0.5;
	//float dryLevel = 0;
	//float wetLevel = 0;
	SmoothedValue<float, ValueSmoothingTypes::Linear> dryLevel;
	SmoothedValue<float, ValueSmoothingTypes::Linear> wetLevel;

	AudioBuffer<float> drySignal;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DryWet)
};
	
	