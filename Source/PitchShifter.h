#pragma once
#include <JuceHeader.h>
#include "CircularBuffer.h"
#include "Parameters.h"
#include "Filter.h"

namespace PitchShifter
{
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

	class PitchShifterAllPass : public PitchShifterHighPass
	{
	public:
		PitchShifterAllPass();
		~PitchShifterAllPass();

		void processBlock(AudioBuffer<float>& buffer);

	protected:
		void initialize() override;

		//Filter::StereoFilter allPassFilter;
		OwnedArray<Filter::StereoFilter> allPassFilters;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PitchShifterAllPass)
	};
}






