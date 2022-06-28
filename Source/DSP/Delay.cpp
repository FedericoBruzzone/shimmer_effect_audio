#include "Delay.h"

// === Delay Block ===
Delay::DelayBlock::DelayBlock() {}
Delay::DelayBlock::~DelayBlock() {}

void Delay::DelayBlock::setTime(float newValue)
{
	delayTime = newValue;
}

void Delay::DelayBlock::initialize()
{
	setTime(delayTime);
	CircularBuffer::setMaxTime(5.00f);
}

void Delay::DelayBlock::moveTo(AudioBuffer<float>& buffer)
{
	const auto numOutputSamples = buffer.getNumSamples();
	const auto numChannels = buffer.getNumChannels();

	const auto readIndex = (writeIndex - roundToInt(delayTime * sr) + memorySize) % memorySize;

	for (int ch = 0; ch < numChannels; ++ch)
	{
		if (readIndex + numOutputSamples <= memorySize)
			buffer.copyFrom(ch, 0, memory, ch, readIndex, numOutputSamples);
		else
		{
			const int fittingSamples = memorySize - readIndex;
			const int remainingSamples = numOutputSamples - fittingSamples;

			buffer.copyFrom(ch, 0, memory, ch, readIndex, fittingSamples);
			buffer.copyFrom(ch, fittingSamples, memory, ch, 0, remainingSamples);
		}
	}
}

// === Analog delay ===
Delay::AnalogDelay::AnalogDelay() {}
Delay::AnalogDelay::~AnalogDelay() {}

void Delay::AnalogDelay::setTime(float newValue)
{
	delayTime.setTargetValue(newValue);
}

void Delay::AnalogDelay::setFeedback(float newValue)
{
	feedback.setTargetValue(newValue);
}

void Delay::AnalogDelay::initialize()
{
	CircularBuffer::setMaxTime(5.00f);
	delayTime.reset(sr, DEFAULT_DELAY_TIME_SMOOTHING);
	feedback.reset(sr, DEFAULT_DELAY_FEEDBACK_SMOOTHING);
}

void Delay::AnalogDelay::moveTo(AudioBuffer<float>& buffer)
{
	const auto numOutputSamples = buffer.getNumSamples();
	const auto numChannels = buffer.getNumChannels();

	auto** outputData = buffer.getArrayOfWritePointers();
	auto** delayData = memory.getArrayOfWritePointers();

	for (int smp = 0; smp < numOutputSamples; ++smp)
	{
		auto dt = delayTime.getNextValue();
		auto fb = feedback.getNextValue();

		auto actualWriteIndex = (writeIndex + smp) % memorySize;
		auto actualReadIndex = memorySize + actualWriteIndex - (dt * sr);

		auto integerPart = (int)actualReadIndex;
		auto fractionalPart = actualReadIndex - integerPart;

		auto A = (integerPart + memorySize) % memorySize;
		auto B = (A + 1) % memorySize;

		const auto alpha = fractionalPart / (2.0f - fractionalPart);

		for (int ch = 0; ch < numChannels; ++ch)
		{
			// NO INTERPOLATION
			//auto sampleValue = delayData[ch][integerPart]; 

			// LINEAR INTERPOLATION
			//auto sampleValue = delayData[ch][A] * (1.0 - fractionalPart) +
			//				     delayData[ch][B] * fractionalPart;

			// ALLPASS FILTER
			auto sampleValue = alpha * (delayData[ch][B] - oldSample[ch]) + delayData[ch][A];
			oldSample[ch] = sampleValue;

			outputData[ch][smp] = sampleValue;

			delayData[ch][actualWriteIndex] += sampleValue * fb;
		}
	}
}

// === Mod delay ===
Delay::ModDelay::ModDelay() {}
Delay::ModDelay::~ModDelay() {}

void Delay::ModDelay::setFeedback(float newValue)
{
	feedback.setTargetValue(newValue);
}

void Delay::ModDelay::processBlock(AudioBuffer<float>& buffer, AudioBuffer<float>& delayTimeBuffer)
{
	store(buffer);
	moveTo(buffer, delayTimeBuffer);
	updateWriteHead(buffer.getNumSamples());
}

void Delay::ModDelay::initialize()
{
	CircularBuffer::setMaxTime(5.00f);
	feedback.reset(sr, DEFAULT_DELAY_FEEDBACK_SMOOTHING);
}

void Delay::ModDelay::moveTo(AudioBuffer<float>& buffer) 
{
	jassertfalse;
}

void Delay::ModDelay::moveTo(AudioBuffer<float>& buffer, AudioBuffer<float>& delayTimeBuffer)
{
	const auto numOutputSamples = buffer.getNumSamples();
	const auto numChannels = buffer.getNumChannels();
	const auto numModChannels = delayTimeBuffer.getNumChannels();

	auto** outputData = buffer.getArrayOfWritePointers();
	auto** delayData = memory.getArrayOfWritePointers();
	auto** delayTimeArray = delayTimeBuffer.getArrayOfReadPointers();

	for (int smp = 0; smp < numOutputSamples; ++smp)
	{
		auto fb = feedback.getNextValue();

		for (int ch = 0; ch < numChannels; ++ch)
		{
			auto dt = delayTimeArray[jmin(ch, numModChannels - 1)][smp];

			auto actualWriteIndex = (writeIndex + smp) % memorySize;
			auto actualReadIndex = memorySize + actualWriteIndex - (dt * sr);

			auto integerPart = (int)actualReadIndex;
			auto fractionalPart = actualReadIndex - integerPart;

			auto A = (integerPart + memorySize) % memorySize;
			auto B = (A + 1) % memorySize;

			const auto alpha = fractionalPart / (2.0f - fractionalPart);

			// NO INTERPOLATION
			//auto sampleValue = delayData[ch][integerPart]; 

			// LINEAR INTERPOLATION
			//auto sampleValue = delayData[ch][A] * (1.0 - fractionalPart) +
			//				     delayData[ch][B] * fractionalPart;

			// ALLPASS FILTER
			auto sampleValue = alpha * (delayData[ch][B] - oldSample[ch]) + delayData[ch][A];
			oldSample[ch] = sampleValue;

			outputData[ch][smp] = sampleValue;

			delayData[ch][actualWriteIndex] += sampleValue * fb;
		}
	}
}