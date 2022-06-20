#pragma once
#include <JuceHeader.h>
#include "Parameters.h"

namespace Filter
{
	class ReleaseFilter
	{
	public:
		ReleaseFilter();
		~ReleaseFilter();

		void prepareToPlay(double sr);

		void processBlock(AudioBuffer<float>& buffer, const int numSamples);

		void setRelease(float newValue);

	private:

		void updateAlpha();

		float release = DEFAULT_FILTER_RELEASE;
		double sampleRate = 1.0;
		double alpha = 0.0;
		float envelope = 0.0f;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ReleaseFilter)
	};

	class StereoFilter
	{
	public:
		StereoFilter();

		~StereoFilter();

		void prepareToPlay(double sr);

		void processBlock(AudioBuffer<float>& buffer, const int numSamples);

		void setFrequency(float newValue);

		void setQuality(float newValue);

		void setType(float newValue);

		void reset();

		float getFrequency();
		
	private:

		void updateCoefficients();

		float frequency = DEFAULT_FILTER_FREQUENCY;
		float quality = DEFAULT_FILTER_QUALITY;
		double sampleRate = 44100.0;
		int type = 0;

		OwnedArray<IIRFilter> iirFilters;
	};

}