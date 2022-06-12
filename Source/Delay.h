#pragma once
#include <JuceHeader.h>
#include "CircularBuffer.h"
#include "Parameters.h"

namespace Delay 
{
	class DelayBlock : public CircularBuffer
	{
	public:
		DelayBlock();
		~DelayBlock();

		void setTime(float newValue);

	private:
		void initialize() override;

		void moveTo(AudioBuffer<float>& buffer) override;

		float delayTime = 0.5;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DelayBlock)
	};

	class AnalogDelay : public CircularBuffer
	{
	public:
		AnalogDelay();
		~AnalogDelay();

		void setTime(float newValue);

		void setFeedback(float newValue);

	private:

		void moveTo(AudioBuffer<float>& buffer) override;

		void initialize() override;

		float oldSample[2] = { 0.0f, 0.0f };

		SmoothedValue<float, ValueSmoothingTypes::Linear> delayTime;
		SmoothedValue<float, ValueSmoothingTypes::Linear> feedback;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnalogDelay)
	};

	class ModDelay : public CircularBuffer
	{
	public:
		ModDelay();
		~ModDelay();

		void setFeedback(float newValue);

		void processBlock(AudioBuffer<float>& buffer, AudioBuffer<float>& delayTimeBuffer);

	private:

		void moveTo(AudioBuffer<float>& buffer) override;

		void moveTo(AudioBuffer<float>& buffer, AudioBuffer<float>& delayTimeBuffer);

		void initialize() override;

		float oldSample[2] = { 0.0f, 0.0f };

		SmoothedValue<float, ValueSmoothingTypes::Linear> feedback;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ModDelay)
	};
}