#include "PitchShifter.h"

// === Pitch Shifter ===
PitchShifter::PitchShifterBase::PitchShifterBase() {}
PitchShifter::PitchShifterBase::~PitchShifterBase() {}

void PitchShifter::PitchShifterBase::setShift(float newValue)
{
	shift = newValue;
}

void PitchShifter::PitchShifterBase::initialize()
{
	setShift(shift);
}

void PitchShifter::PitchShifterBase::setActive(float newValue)
{
	active = newValue;

	shift = active > 0.5f ? 
			2.0f : 
		    1.0f;
}

void PitchShifter::PitchShifterBase::moveTo(AudioBuffer<float>& buffer)
{
	const auto numSamples = buffer.getNumSamples();
	const auto numChannels = buffer.getNumChannels();
	const auto numSamplesDiv = numSamples / 2;

	auto** bufferOut = buffer.getArrayOfWritePointers();
	auto** pitchData = memory.getArrayOfWritePointers();

	overlap = numSamples * DEFAULT_PITCHSHIFTER_OVERLAP;

	for (auto smp = 0; smp < numSamples; ++smp)
	{
		readIndex_int[0] = static_cast<int>(readIndex);
		readIndex_int[1] = readIndex_int[0] >= numSamplesDiv ?
						   readIndex_int[0] - numSamplesDiv :
						   readIndex_int[0] + numSamplesDiv;
	
		for (auto ch = 0; ch < numChannels; ++ch)
		{
			readSample[0] = pitchData[ch][readIndex_int[0]];
			readSample[1] = pitchData[ch][readIndex_int[1]];
			
			if (overlap >= (smp - readIndex_int[0]) && (smp - readIndex_int[0]) >= 0 && shift != 1.0f)
			{
				delta = smp - readIndex_int[0];
				crossFade = (float)delta / overlap;
			}
			else if (smp - readIndex_int[0] == 0)
			{
				crossFade = 0.0f;
			}
				
			if (overlap >= (smp - readIndex_int[1]) && (smp - readIndex_int[1]) >= 0 && shift != 1.0f)
			{
				delta = smp - readIndex_int[1];
				crossFade = 1.0f - ((float)delta / overlap);
			}
			else if (smp - readIndex_int[1] == 0)
			{
				crossFade = 1.0f;
			}
			
			bufferOut[ch][smp] = ((readSample[0] * crossFade) + 
							      (readSample[1] * (1.0f - crossFade)));
		}

		readIndex = readIndex + shift;

		readIndex = readIndex >= memorySize ? 0.0f : readIndex;

		/*if (readIndex >= memorySize)
			readIndex = 0.0f;*/
	}
}

// === Pitch Shifter High Pass===
PitchShifter::PitchShifterHighPass::PitchShifterHighPass() {}
PitchShifter::PitchShifterHighPass::~PitchShifterHighPass() {}

void PitchShifter::PitchShifterHighPass::setShift(float newValue)
{
	shift = newValue;
}

void PitchShifter::PitchShifterHighPass::initialize()
{
	setShift(shift);
	highPassFilter.setType(2);
	highPassFilter.setFrequency(250);
	highPassFilter.prepareToPlay(sr);
}

void PitchShifter::PitchShifterHighPass::setActive(float newValue)
{
	active = newValue;

	shift = active > 0.5f ?
			2.0f :
			1.0f;
}

void PitchShifter::PitchShifterHighPass::moveTo(AudioBuffer<float>& buffer)
{
	const auto numSamples = buffer.getNumSamples();
	const auto numChannels = buffer.getNumChannels();
	const auto numSamplesDiv = numSamples / 2;

	auto** bufferOut = buffer.getArrayOfWritePointers();
	auto** pitchData = memory.getArrayOfWritePointers();

	overlap = numSamples * DEFAULT_PITCHSHIFTER_OVERLAP;

	highPassFilter.processBlock(buffer, numSamples);

	for (auto smp = 0; smp < numSamples; ++smp)
	{
		readIndex_int[0] = static_cast<int>(readIndex);
		readIndex_int[1] = readIndex_int[0] >= numSamplesDiv ?
			readIndex_int[0] - numSamplesDiv :
			readIndex_int[0] + numSamplesDiv;

		for (auto ch = 0; ch < numChannels; ++ch)
		{
			readSample[0] = pitchData[ch][readIndex_int[0]];
			readSample[1] = pitchData[ch][readIndex_int[1]];

			if (overlap >= (smp - readIndex_int[0]) && (smp - readIndex_int[0]) >= 0 && shift != 1.0f)
			{
				delta = smp - readIndex_int[0];
				crossFade = (float)delta / overlap;
			}
			else if (smp - readIndex_int[0] == 0)
			{
				crossFade = 0.0f;
			}

			if (overlap >= (smp - readIndex_int[1]) && (smp - readIndex_int[1]) >= 0 && shift != 1.0f)
			{
				delta = smp - readIndex_int[1];
				crossFade = 1.0f - ((float)delta / overlap);
			}
			else if (smp - readIndex_int[1] == 0)
			{
				crossFade = 1.0f;
			}

			bufferOut[ch][smp] = ((readSample[0] * crossFade) +
				(readSample[1] * (1.0f - crossFade)));
		}

		readIndex = readIndex + shift;

		readIndex = readIndex >= memorySize ? 0.0f : readIndex;

		/*if (readIndex >= memorySize)
			readIndex = 0.0f;*/
	}
}

// === Pitch Shifter All Pass===
PitchShifter::PitchShifterAllPass::PitchShifterAllPass()
{
	for (int f = 0; f <= 50; ++f)
		allPassFilters.add(new Filter::StereoFilter());
}

PitchShifter::PitchShifterAllPass::~PitchShifterAllPass() {}

void PitchShifter::PitchShifterAllPass::initialize()
{
	setShift(shift);

	//allPassFilter.prepareToPlay(sr);
	for (int f = allPassFilters.size(); --f >= 0;)
	{
		allPassFilters.getUnchecked(f)->setFrequency
		(
			allPassFilters.getUnchecked(f)->getFrequency() +
			(f * 250)
		);

		allPassFilters.getUnchecked(f)->prepareToPlay(sr);
	}
}

void PitchShifter::PitchShifterAllPass::processBlock(AudioBuffer<float>& buffer)
{
	//store
	CircularBuffer::store(buffer);

	//all pass
	//allPassFilters.processBlock(buffer, buffer.getNumSamples());
	for (int f = allPassFilters.size(); --f >= 0;)
		allPassFilters.getUnchecked(f)->processBlock(buffer, buffer.getNumSamples());

	//output
	PitchShifterHighPass::moveTo(buffer);


	//update write head
	CircularBuffer::updateWriteHead(buffer.getNumSamples());

}