#include "Oscillator.h"

// === Naive Oscillator ===
Oscillator::NaiveOscillator::NaiveOscillator() {};
Oscillator::NaiveOscillator::~NaiveOscillator() {};

void Oscillator::NaiveOscillator::prepareToPlay(double sr)
{
	samplePeriod = 1.0 / sr;
	frequency.reset(sr, DEFAULT_OSCILLATOR_GLIDE_TIME);
}

void Oscillator::NaiveOscillator::setFrequency(float newValue)
{
	frequency.setTargetValue(newValue);
}

void Oscillator::NaiveOscillator::setWaveform(float newValue)
{
	waveform = roundToInt(newValue);
}

void Oscillator::NaiveOscillator::getNextAudioBlock(AudioBuffer<float>& buffer, const int numSamples)
{
	const int numCh = buffer.getNumChannels();
	auto bufferData = buffer.getArrayOfWritePointers();

	for (int smp = 0; smp < numSamples; ++smp)
	{
		const auto sampleValue = getNextAudioSample();

		for (int ch = 0; ch < numCh; ++ch)
			bufferData[ch][smp] = sampleValue;
	}
}

float Oscillator::NaiveOscillator::getNextAudioSample()
{
	auto sampleValue = 0.0f;

	switch (waveform)
	{
	case 0: // Sine
		sampleValue = sin(MathConstants<float>::twoPi * currentPhase);
		break;
	case 1: // Triangular
		sampleValue = 4.0f * abs(currentPhase - 0.5f) - 1.0f;
		break;
	case 2: // Saw up
		sampleValue = 2.0f * currentPhase - 1.0f;
		break;
	case 3: // Saw down
		sampleValue = -2.0f * currentPhase - 1.0f;
		break;
	default:
		break;
	}

	phaseIncrement = frequency.getNextValue() * samplePeriod;
	currentPhase += phaseIncrement;
	currentPhase -= static_cast<int>(currentPhase);

	return sampleValue;
}