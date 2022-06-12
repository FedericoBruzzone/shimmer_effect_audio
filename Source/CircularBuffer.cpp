#include "CircularBuffer.h"
#include "Parameters.h"


CircularBuffer::CircularBuffer() {}
CircularBuffer::~CircularBuffer() {}

void CircularBuffer::prepareToPlay(double sampleRate, int maxNumSamples)
{
	sr = sampleRate;
	memorySize = roundToInt(DEFAULT_CIRCULARBUFFER_MAX_TIME * sampleRate) + maxNumSamples;
	memory.setSize(2, memorySize);
	initialize();
}

void CircularBuffer::releaseResurces()
{
	memory.setSize(0, 0);
	memorySize = 0;
}

void CircularBuffer::processBlock(AudioBuffer<float>& buffer)
{
	store(buffer);
	moveTo(buffer);
	updateWriteHead(buffer.getNumSamples());
}
	
void CircularBuffer::store(const AudioBuffer<float>& buffer)
{
	const auto numInputSamples = buffer.getNumSamples();
	const auto numChannels = buffer.getNumChannels();

	for (int ch = 0; ch < numChannels; ++ch)
	{
		if (writeIndex + numInputSamples <= memorySize)
			memory.copyFrom(ch, writeIndex, buffer, ch, 0, numInputSamples);
		else
		{
			const int fittingSamples = memorySize - writeIndex;
			const int remainingSamples = numInputSamples - fittingSamples;

			memory.copyFrom(ch, writeIndex, buffer, ch, 0, fittingSamples);
			memory.copyFrom(ch, 0, buffer, ch, fittingSamples, remainingSamples);
		}
	}
}

void CircularBuffer::updateWriteHead(int leap)
{
	writeIndex += leap;
	writeIndex %= memorySize;
}



