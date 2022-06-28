#pragma once
#include <JuceHeader.h>

class CircularBuffer
{
public:
	CircularBuffer();
	~CircularBuffer();

	void prepareToPlay(double sampleRate, int maxNumSamples);

	void releaseResurces();

	void processBlock(AudioBuffer<float>& buffer);

	void setMaxTime(float newValue);

protected:
	virtual void initialize() = 0;

	void store(const AudioBuffer<float>& buffer);

	virtual void moveTo(AudioBuffer<float>& buffer) = 0;

	void updateWriteHead(int leap);

	float maxTime = DEFAULT_CIRCULARBUFFER_MAX_TIME;
	AudioBuffer<float> memory;
	int memorySize = 0;
	int writeIndex = 0;
	double sr = 1;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CircularBuffer)
};