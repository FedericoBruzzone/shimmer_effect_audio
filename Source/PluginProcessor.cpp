#include "PluginProcessor.h"
#include "GUI/PluginEditor.h"
#include "Parameters.h"

ShimmerAudioProcessor::ShimmerAudioProcessor()
    : parameters(*this, nullptr, "ShimmerParameters", Parameters::createParameterLayout())
{
    // === TODO === --> file Parameters.h
    // {
    //      Parameters::initializeParameters(parameters, *this); 
    // }
    parameters.addParameterListener(NAME_DRYWET, this);
    parameters.addParameterListener(NAME_PITCHSHIFTER1_SHIFT, this);
    parameters.addParameterListener(NAME_PITCHSHIFTER2_SHIFT, this);
    parameters.addParameterListener(NAME_PITCHSHIFTER2_ACTIVE, this);
    parameters.addParameterListener(NAME_SHIMMER_DELAY_FEEDBACK, this);
    parameters.addParameterListener(NAME_SHIMMER_BRANCH_ROOMSIZE, this);
    parameters.addParameterListener(NAME_SHIMMER_BRANCH_DAMPING, this);
    parameters.addParameterListener(NAME_SHIMMER_BRANCH_WIDTH, this);
    parameters.addParameterListener(NAME_SHIMMER_MASTER_ROOMSIZE, this);

    //parameters.addParameterListener("PSP", this);

    dryWet.setDryWetRatio(DEFAULT_DRYWET);
    dryWetPitch.setDryWetRatio(DEFAULT_DRYWETPITCH);
    pitchShifter1.setShift(DEFAULT_PITCHSHIFTER1_SHIFT);
    pitchShifter2.setShift(DEFAULT_PITCHSHIFTER2_SHIFT);

    branchReverbParameters.roomSize = DEFAULT_SHIMMER_BRANCH_ROOMSIZE;
    branchReverbParameters.damping = DEFAULT_SHIMMER_BRANCH_DAMPING;
    branchReverbParameters.damping = DEFAULT_SHIMMER_BRANCH_WIDTH;
    branchReverb.setParameters(branchReverbParameters);

    delay.setTime(DEFAULT_SHIMMER_DELAY_TIME);
    delay.setFeedback(DEFAULT_SHIMMER_DELAY_FEEDBACK);


    masterReverbParameters.roomSize = DEFAULT_SHIMMER_MASTER_ROOMSIZE;
    masterReverb.setParameters(masterReverbParameters);

}

ShimmerAudioProcessor::~ShimmerAudioProcessor() {}

void ShimmerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    dspProcessSpec.sampleRate = sampleRate;
    dspProcessSpec.maximumBlockSize = samplesPerBlock;

    dryWet.prepareToPlay(sampleRate, samplesPerBlock);
    dryWetPitch.prepareToPlay(sampleRate, samplesPerBlock);
    pitchShifter1.prepare(sampleRate, samplesPerBlock);
    pitchShifter2.prepare(sampleRate, samplesPerBlock);
     
    branchReverb.prepare(dspProcessSpec);

    delay.prepareToPlay(sampleRate, samplesPerBlock);

    masterReverb.prepare(dspProcessSpec);

    branchReverb.reset();
    masterReverb.reset();

}

void ShimmerAudioProcessor::releaseResources()
{
    dryWet.releaseResources();
    dryWetPitch.releaseResources();
    pitchShifter1.releaseResources();
    pitchShifter2.releaseResources();

    branchReverb.reset();

    delay.releaseResources();

    masterReverb.reset();

}

void ShimmerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals; 
    
    if (buffer.getNumChannels() != 1)
    {
        envelopeInput[0].set(juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples())));
        envelopeInput[1].set(juce::Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples())));
    }
    else
    {
        envelopeInput[0].set(juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples())));
        envelopeInput[1].set(juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples())));
    }
    
    block = dsp::AudioBlock<float>(buffer);
    dsp::ProcessContextReplacing<float> contextToUse = dsp::ProcessContextReplacing<float>(block);

    dryWet.setDry(buffer); 
    
    pitchShifter1.process(buffer);
    
    dryWetPitch.setDry(buffer);

    pitchShifter2.process(buffer); 

    dryWetPitch.merge(buffer);

    branchReverb.process(contextToUse);
    
    delay.processBlock(buffer);

    dryWet.merge(buffer);

    masterReverb.process(contextToUse);
    
    if (buffer.getNumChannels() != 1)
    {
        envelopeOutput[0].set(juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples())));
        envelopeOutput[1].set(juce::Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples())));
    }
    else
    {
        envelopeOutput[0].set(juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples())));
        envelopeOutput[1].set(juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples())));
    }
    
}

juce::AudioProcessorEditor* ShimmerAudioProcessor::createEditor()
{
    return new PluginEditor(*this, parameters);
}

void ShimmerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void ShimmerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.replaceState(ValueTree::fromXml(*xmlState));
}

void ShimmerAudioProcessor::parameterChanged(const String& paramID, float newValue)
{
    if (paramID == NAME_DRYWET)
        dryWet.setDryWetRatio(newValue);

    if (paramID == NAME_PITCHSHIFTER1_SHIFT)
        pitchShifter1.setShift(newValue);

    if (paramID == NAME_PITCHSHIFTER2_SHIFT)
        pitchShifter2.setShift(newValue);

    if (paramID == NAME_PITCHSHIFTER2_ACTIVE)
        pitchShifter2.setActive(newValue);

    if (paramID == NAME_SHIMMER_DELAY_FEEDBACK)
        delay.setFeedback(newValue);

    if (paramID == NAME_SHIMMER_BRANCH_ROOMSIZE)
    {
        branchReverbParameters.roomSize = newValue;
        branchReverb.setParameters(branchReverbParameters);
    }

    if (paramID == NAME_SHIMMER_BRANCH_DAMPING)
    {
        branchReverbParameters.damping = newValue;
        branchReverb.setParameters(branchReverbParameters);
    }

    if (paramID == NAME_SHIMMER_BRANCH_WIDTH)
    {
        branchReverbParameters.width = newValue;
        branchReverb.setParameters(branchReverbParameters);
    }

    if (paramID == NAME_SHIMMER_MASTER_ROOMSIZE)
    {
        masterReverbParameters.roomSize = newValue;
        masterReverb.setParameters(masterReverbParameters);
    }

}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ShimmerAudioProcessor();
}