#pragma once
#include <JuceHeader.h>
#include "DryWet.h"
#include "Delay.h"
#include "Oscillator.h"
#include "ParameterModulation.h"
#include "PitchShifter.h"

class ShimmerAudioProcessor  
    : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    ShimmerAudioProcessor();
    ~ShimmerAudioProcessor() override;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return JucePlugin_Name; }

    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    bool isMidiEffect() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int index) override {}
    const juce::String getProgramName(int index) override { return {}; }
    void changeProgramName(int index, const juce::String& newName) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    //Atomic<float> envelope;
    Atomic<float> envelopeInput[2];
    Atomic<float> envelopeOutput[2];
    
private:

    void parameterChanged(const String& paramID, float newValue) override;

    AudioProcessorValueTreeState parameters;

    dsp::ProcessSpec dspProcessSpec;
    dsp::AudioBlock<float> block;
    //dsp::ProcessContextReplacing<float> contextToUse = dsp::ProcessContextReplacing<float>(block);

    DryWet dryWet;
    DryWet dryWetPitch;
    PitchShifter::PitchShifterAllPass pitchShifter1;
    PitchShifter::PitchShifterAllPass pitchShifter2;

    dsp::Reverb branchReverb;
    dsp::Reverb::Parameters branchReverbParameters; // using juce::Reverb::Parameters

    Delay::AnalogDelay delay;


    dsp::Reverb masterReverb;
    dsp::Reverb::Parameters masterReverbParameters;
    //DryWet dryWet;
    //Delay::DelayBlock delay;
    //Delay::AnalogDelay delay;

    /*
    Delay::ModDelay delay;
    Oscillator::NaiveOscillator LFO;
    ParameterModulation timeAdapter;

    AudioBuffer<float> modulationSignal;
    */

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ShimmerAudioProcessor)
};
