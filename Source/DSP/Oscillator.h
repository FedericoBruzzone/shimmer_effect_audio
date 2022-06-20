#pragma once
#include <JuceHeader.h>
#include "../Parameters.h"

namespace Oscillator
{
	class NaiveOscillator
	{
	public:
		NaiveOscillator();
		~NaiveOscillator();

		void prepareToPlay(double sr);

		void setFrequency(float newValue);

		void setWaveform(float newValue);

		void getNextAudioBlock(AudioBuffer<float>& buffer, const int numSamples);

		float getNextAudioSample();

	private:

		int waveform = 0; 

		double samplePeriod = 1.0;
		float currentPhase = 0.0f;
		float phaseIncrement = 0.0f;
		SmoothedValue<float, ValueSmoothingTypes::Multiplicative> frequency;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NaiveOscillator)
	};
}