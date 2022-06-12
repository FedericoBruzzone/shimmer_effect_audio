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

	// Scalo la modulante tra 0 e 1
	for (int ch = 0; ch < numCh; ++ch)
	{
		FloatVectorOperations::add(bufferData[ch], 1.0, numSamples);
		FloatVectorOperations::multiply(bufferData[ch], 0.5f, numSamples);
	}

	// Scalo la modulante tra 0 e la modulaziuone massima desiderata
	modAmount.applyGain(buffer, numSamples);

	// Sommo alla modulante il tempo di delay proveniente dal parametro
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

	// Controllo di essere dentro al tempo di delay massimo
	for (int ch = 0; ch < numCh; ++ch)
		FloatVectorOperations::min(bufferData[ch], bufferData[ch], DEFAULT_MODULATION_MAX_TIME, numSamples);
}
