#include "DryWet.h"

DryWet::DryWet() {}
DryWet::~DryWet() {}

void DryWet::prepareToPlay(double sr, int maxNumSamples)
{
	drySignal.setSize(2, maxNumSamples);

	dryLevel.reset(sr, DEFAULT_DRYWET_SMOOTHING_TIME);
	wetLevel.reset(sr, DEFAULT_DRYWET_SMOOTHING_TIME);

	setDryWetRatio(dryWetRatio);
}

void DryWet::releaseResources()
{
	drySignal.setSize(0, 0);
}

void DryWet::setDry(const AudioBuffer<float>& buffer)
{
	for (int ch = buffer.getNumChannels(); --ch >= 0; )
		drySignal.copyFrom(ch, 0, buffer, ch, 0, buffer.getNumSamples());
}

void DryWet::merge(AudioBuffer<float>& buffer)
{
	//buffer.applyGain(wetLevel);
	//drySignal.applyGain(dryLevel);
	auto numSamples = buffer.getNumSamples();
	wetLevel.applyGain(buffer, numSamples);
	dryLevel.applyGain(drySignal, numSamples);

	for (int ch = buffer.getNumChannels(); --ch >= 0; )
	{
		//buffer.addFrom(ch, 0, drySignal, ch, 0, buffer.getNumSamples(), dryLevel);
		buffer.addFrom(ch, 0, drySignal, ch, 0, numSamples);
	}
}

void DryWet::setDryWetRatio(float newValue)
{
	dryWetRatio = newValue;
	//dryLevel = sqrt(1 - dryWetRatio);
	//wetLevel = sqrt(dryWetRatio);
	dryLevel.setTargetValue(sqrt(1 - dryWetRatio));
	wetLevel.setTargetValue(sqrt(dryWetRatio));
}
