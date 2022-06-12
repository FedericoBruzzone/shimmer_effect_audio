#include "Filter.h"

// === Release Filter ===
Filter::ReleaseFilter::ReleaseFilter() {}
Filter::ReleaseFilter::~ReleaseFilter() {}


void Filter::ReleaseFilter::prepareToPlay(double sr)
{
	sampleRate = sr;
	updateAlpha();
}

void Filter::ReleaseFilter::processBlock(AudioBuffer<float>& buffer, const int numSamples)
{
	float* bufferData = buffer.getWritePointer(0);

	for (int smp = 0; smp < numSamples; ++smp)
	{
		envelope = jmax(bufferData[smp], envelope * (float)alpha);
		bufferData[smp] = envelope;
	}
}

void Filter::ReleaseFilter::setRelease(float newValue)
{
	release = newValue;
	updateAlpha();
}

void Filter::ReleaseFilter::updateAlpha()
{
	const auto n = jmax(1.0, release * sampleRate);
	alpha = exp(-1.0 / n);
}

// === Stereo Filter ===
Filter::StereoFilter::StereoFilter()
{
	for (int f = 0; f < 2; ++f)
		iirFilters.add(new IIRFilter());
}
Filter::StereoFilter::~StereoFilter() {}

void Filter::StereoFilter::prepareToPlay(double sr)
{
	sampleRate = sr;

	reset();

	updateCoefficients();
}

void Filter::StereoFilter::processBlock(AudioBuffer<float>& buffer, const int numSamples)
{
	for (int ch = buffer.getNumChannels(); --ch >= 0;)
		iirFilters.getUnchecked(ch)->processSamples(buffer.getWritePointer(ch), numSamples);
}

void Filter::StereoFilter::setFrequency(float newValue)
{
	frequency = jmin(newValue, (float)(sampleRate * 0.499));
	updateCoefficients();
}

void Filter::StereoFilter::setQuality(float newValue)
{
	quality = newValue;
	updateCoefficients();
}

void Filter::StereoFilter::setType(float newValue)
{
	type = roundToInt(newValue);
}

void Filter::StereoFilter::reset()
{
	for (int f = iirFilters.size(); --f >= 0;)
		iirFilters.getUnchecked(f)->reset();
}

void Filter::StereoFilter::updateCoefficients()
{
	IIRCoefficients iirCoeffs;

	switch (type)
	{
	case 0:
		iirCoeffs = IIRCoefficients::makeAllPass(sampleRate, frequency, quality);
		break;
	case 1:
		iirCoeffs = IIRCoefficients::makeLowPass(sampleRate, frequency, quality);
		break;
	case 2:
		iirCoeffs = IIRCoefficients::makeHighPass(sampleRate, frequency, quality);
		break;
	case 3:
		iirCoeffs = IIRCoefficients::makeBandPass(sampleRate, frequency, quality);
		break;
		/*case 4:
			iirCoeffs = IIRCoefficients::makeLowShelf(sampleRate, frequency, quality);
			break;
		case 5:
			iirCoeffs = IIRCoefficients::makeHighShelf(sampleRate, frequency, quality);
			break;
		case 6:
			iirCoeffs = IIRCoefficients::makePeakFilter(sampleRate, frequency, quality);
				break;
		case 7:
			iirCoeffs = IIRCoefficients::makeNotchFilter(sampleRate, frequency, quality);
				break;*/
	default:
		break;
	}


	for (int f = iirFilters.size(); --f >= 0;)
		iirFilters.getUnchecked(f)->setCoefficients(iirCoeffs);
}