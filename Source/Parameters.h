#pragma once
#include <JuceHeader.h>

// Shimmer
#define DEFAULT_SHIMMER_DELAY_TIME 0.275f
#define NAME_SHIMMER_DELAY_FEEDBACK "shimmerDelayFeedback"
#define DEFAULT_SHIMMER_DELAY_FEEDBACK 0.1f

#define NAME_DRYWET "drywet"
#define NAME_DRYWETPITCH "drywetpitch"
#define DEFAULT_DRYWET 0.1f
#define DEFAULT_DRYWETPITCH 0.5f

#define NAME_PITCHSHIFTER1_SHIFT "pitchShifter1"
#define NAME_PITCHSHIFTER2_SHIFT "pitchShifter2"
//#define DEFAULT_PITCHSHIFTER1_SHIFT 2.0f 
//#define DEFAULT_PITCHSHIFTER2_SHIFT 2.0f
#define DEFAULT_PITCHSHIFTER1_SHIFT 10.0f 
#define DEFAULT_PITCHSHIFTER2_SHIFT 10.0f

#define NAME_PITCHSHIFTER2_ACTIVE "pitchShifter2Active"
#define DEFAULT_PITCHSHIFTER2_ACTIVE 1

#define MUTE_DEFAULT   0

//#define DEFAULT_PITCHSHIFTER_SEMITONE 0.083333333f // (std::pow(2.0f, 1 / 12)) / 2
#define DEFAULT_PITCHSHIFTER_SEMITONE 0.83333333f // (std::pow(2.0f, 1 / 12)) / 2 * 10

#define DEFAULT_PITCHSHIFTER_OVERLAP 0.1f

#define NAME_SHIMMER_BRANCH_ROOMSIZE "branchRoomSize"
#define DEFAULT_SHIMMER_BRANCH_ROOMSIZE 1.0f

#define NAME_SHIMMER_BRANCH_DAMPING "branchDamping"
#define DEFAULT_SHIMMER_BRANCH_DAMPING 0.5f

#define NAME_SHIMMER_BRANCH_WIDTH "branchWidth"
#define DEFAULT_SHIMMER_BRANCH_WIDTH 1.0f

#define NAME_SHIMMER_MASTER_ROOMSIZE "masterRoomSize"
#define DEFAULT_SHIMMER_MASTER_ROOMSIZE 0.1f

// Filter
#define DEFAULT_FILTER_RELEASE 0.25
#define NAME_FILTER_RELEASE "filterRelease"

#define DEFAULT_FILTER_FREQUENCY 1000.0f
#define DEFAULT_FILTER_QUALITY 0.707f
#define NAME_FILTER_QUALITY "filterQuality"

// CircularBuffer
//#define DEFAULT_CIRCULARBUFFER_MAX_TIME 5.00f
#define DEFAULT_CIRCULARBUFFER_MAX_TIME 1.00f

// Delay
#define DEFAULT_DELAY_TIME_SMOOTHING 0.02f
#define DEFAULT_DELAY_FEEDBACK_SMOOTHING 0.02f

// DryWet
#define DEFAULT_DRYWET_SMOOTHING_TIME 0.02f

// Oscillator
#define DEFAULT_OSCILLATOR_GLIDE_TIME 0.01

// ParameterModulation
#define DEFAULT_MODULATION_SMOOTHING_TIME 0.04
#define DEFAULT_MODULATION_MAX_TIME 5.00f

// Actual parameters
#define NAME_DELAY_TIME "delayTime"
#define NAME_DELAY_FEEDBACK "delayFeedback"
#define NAME_LFO_FREQENCY "lfoFrequency"
#define NAME_MODULATION_DELAY "timeModulation-Delay"
#define NAME_LFO_WAVEFORM "lfoWaveform"

//#define DEFAULT_DRYWET 0.5f
#define DEFAULT_DELAY_TIME 0.5f
#define DEFAULT_FEEDBACK 0.0f
#define DEFAULT_LFO_FREQENCY 1.0f
#define DEFAULT_MODULATION_DELAY 0.0f
#define DEFAULT_LFO_WAVEFORM 0

namespace Parameters
{
	static AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
	{
		std::vector<std::unique_ptr<RangedAudioParameter>> params;

		params.push_back(std::make_unique<AudioParameterFloat>(NAME_DRYWET, "Dry/Wet", 0.0f, 1.0f, DEFAULT_DRYWET));
		params.push_back(std::make_unique<AudioParameterBool>(NAME_PITCHSHIFTER2_ACTIVE, "2nd PitchShifter Mute", DEFAULT_PITCHSHIFTER2_ACTIVE));
		//params.push_back(std::make_unique<AudioParameterFloat>(NAME_PITCHSHIFTER1_SHIFT, "PitchShifter1", NormalisableRange<float>(0.5f, 2.0f, DEFAULT_PITCHSHIFTER_SEMITONE), DEFAULT_PITCHSHIFTER1_SHIFT));
		//params.push_back(std::make_unique<AudioParameterFloat>(NAME_PITCHSHIFTER2_SHIFT, "PitchShifter2", NormalisableRange<float>(0.5f, 2.0f, DEFAULT_PITCHSHIFTER_SEMITONE), DEFAULT_PITCHSHIFTER2_SHIFT));
		params.push_back(std::make_unique<AudioParameterFloat>(NAME_SHIMMER_DELAY_FEEDBACK, "Delay Feedback", 0.0f, 1.0f, DEFAULT_SHIMMER_DELAY_FEEDBACK));
		params.push_back(std::make_unique<AudioParameterFloat>(NAME_SHIMMER_BRANCH_ROOMSIZE, "Branch Reverb Room Size (Tail)", 0.0f, 1.0f, DEFAULT_SHIMMER_BRANCH_ROOMSIZE));
		params.push_back(std::make_unique<AudioParameterFloat>(NAME_SHIMMER_BRANCH_DAMPING, "Branch Reverb Damping", 0.0f, 1.0f, DEFAULT_SHIMMER_BRANCH_DAMPING));
		params.push_back(std::make_unique<AudioParameterFloat>(NAME_SHIMMER_BRANCH_WIDTH, "Branch Reverb Width", 0.0f, 1.0f, DEFAULT_SHIMMER_BRANCH_WIDTH));
		//params.push_back(std::make_unique<AudioParameterFloat>(NAME_SHIMMER_MASTER_ROOMSIZE, "Master Reverb Room Size (Tail)", 0.0f, 1.0f, DEFAULT_SHIMMER_MASTER_ROOMSIZE));
		params.push_back(std::make_unique<AudioParameterFloat>(NAME_PITCHSHIFTER1_SHIFT, "PitchShifter1", NormalisableRange<float>(0.0f, 10.0f, DEFAULT_PITCHSHIFTER_SEMITONE), DEFAULT_PITCHSHIFTER1_SHIFT));
		params.push_back(std::make_unique<AudioParameterFloat>(NAME_PITCHSHIFTER2_SHIFT, "PitchShifter2", NormalisableRange<float>(0.0f, 10.0, DEFAULT_PITCHSHIFTER_SEMITONE), DEFAULT_PITCHSHIFTER2_SHIFT));
		params.push_back(std::make_unique<AudioParameterFloat>(NAME_DELAY_TIME, "Delay Time", NormalisableRange<float>(0.0f, 1.0f, 0.01f), DEFAULT_DELAY_TIME));

		return {params.begin(), params.end()};
	}

	// === TODO ===
	/*void initializeParameters(AudioProcessorValueTreeState& parameters, AudioProcessorValueTreeState::Listener& vts)
	{
		parameters.addParameterListener(NAME_DRYWET, &vts);
		parameters.addParameterListener(NAME_SHIMMER_DELAY_FEEDBACK, &vts);
		parameters.addParameterListener(NAME_SHIMMER_BRANCH_ROOMSIZE, &vts);
		parameters.addParameterListener(NAME_SHIMMER_BRANCH_DAMPING, &vts);
		parameters.addParameterListener(NAME_SHIMMER_BRANCH_WIDTH, &vts);
	}*/
}