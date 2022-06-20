#include "ParameterModulation.h"

ParameterModulation::ParameterModulation() {}
ParameterModulation::~ParameterModulation() {}

void ParameterModulation::prepareToPlay(double sr)
{
	parameter.reset(sr, DEFAULT_MODULATION_SMOOTHING_TIME);
	modAmount.reset(sr, DEFAULT_MODULATION_SMOOTHING_TIME);
}

void ParameterModulation::setParameter(float newValue)
{
	parameter.setTargetValue(newValue);
}

void ParameterModulation::setModAmount(float newValue)
{
	modAmount.setTargetValue(newValue);
}

void ParameterModulation::processBlock(AudioBuffer<float>& buffer, const int numSamples)
{
	auto bufferData = buffer.getArrayOfWritePointers();
	auto numCh = buffer.getNumChannels();

	for (int ch = 0; ch < numCh; ++ch)
	{
		FloatVectorOperations::add(bufferData[ch], 1.0, numSamples);
		FloatVectorOperations::multiply(bufferData[ch], 0.5f, numSamples);
	}

	modAmount.applyGain(buffer, numSamples);

	if (parameter.isSmoothing())
		for (int smp = 0; smp < numSamples; ++smp)
		{
			const auto param = parameter.getNextValue();

			for (int ch = 0; ch < numCh; ++ch)
				bufferData[ch][smp] += param;
		}
	else
		for (int ch = 0; ch < numCh; ++ch)
			FloatVectorOperations::add(bufferData[ch], parameter.getCurrentValue(), numSamples);

	for (int ch = 0; ch < numCh; ++ch)
		FloatVectorOperations::min(bufferData[ch], bufferData[ch], DEFAULT_MODULATION_MAX_TIME, numSamples);
}