#pragma once
#include <JuceHeader.h>
#include "CircularBuffer.h"
#include "Filter.h"
#include "../Parameters.h"

// For PitchShifterModBase
#include "Delay.h"
#include "Oscillator.h"
#include "ParameterModulation.h"

namespace PitchShifter
{
	// === PitchShifterBase ===
	class PitchShifterBase : public CircularBuffer
	{
	public:
		PitchShifterBase();
		~PitchShifterBase();

		void setShift(float newValue);

		void setActive(float newValue);

	protected:
		void initialize() override;

		void moveTo(AudioBuffer<float>& buffer) override;

		bool active = 1;

		float shift = 1.0f;

		float readIndex = 0.0f;
		int   readIndex_int[2] = { 0, 0 };
		float readSample[2] = { 0.0f, 0.0f };

		float crossFade = 1.0f;
		float overlap = 0.0f;
		int   delta = 0;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PitchShifterBase)
	};

	// === PitchShifterHighPass ===
	class PitchShifterHighPass : public CircularBuffer
	{
	public:
		PitchShifterHighPass();
		~PitchShifterHighPass();

		void setShift(float newValue);

		void setActive(float newValue);

	protected:
		void initialize() override;

		void moveTo(AudioBuffer<float>& buffer) override;

		Filter::StereoFilter highPassFilter;

		bool active = 1;

		float shift = 1.0f;

		float readIndex = 0.0f;
		int   readIndex_int[2] = { 0, 0 };
		float readSample[2] = { 0.0f, 0.0f };

		float crossFade = 1.0f;
		float overlap = 0.0f;
		int   delta = 0;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PitchShifterHighPass)
	};

	// === PitchShifterAllPass ===
	class PitchShifterAllPass : public PitchShifterHighPass
	{
	public:
		PitchShifterAllPass();
		~PitchShifterAllPass();

		void processBlock(AudioBuffer<float>& buffer);

	protected:
		void initialize() override;

		OwnedArray<Filter::StereoFilter> allPassFilters;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PitchShifterAllPass)
	};

	// === PitchShifterModBase ===
	class PitchShifterModBase
	{
	public:
		PitchShifterModBase();
		~PitchShifterModBase();

		void PitchShifterModBase::prepare(double sampleRate, int samplesPerBlock);

		void PitchShifterModBase::releaseResources();

		void PitchShifterModBase::process(juce::AudioBuffer<float>& buffer);

		void setShift(float newValue);

		void setActive(float newValue);

	protected:

		void setParameter();

		float shift = 10.f;
		bool active = 1 - MUTE_DEFAULT;

		Delay::ModDelay delay;
		Oscillator::NaiveOscillator LFO;
		ParameterModulation timeAdapter;

		AudioBuffer<float> modulationSignal;
	};
}