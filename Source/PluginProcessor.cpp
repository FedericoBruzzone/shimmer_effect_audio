#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"

ShimmerAudioProcessor::ShimmerAudioProcessor()
    : parameters(*this, nullptr, "ShimmerParameters", Parameters::createParameterLayout())
{
    //Parameters::initializeParameters(parameters, *this);
    parameters.addParameterListener(NAME_DRYWET, this);
    parameters.addParameterListener(NAME_PITCHSHIFTER1_SHIFT, this);
    parameters.addParameterListener(NAME_PITCHSHIFTER2_SHIFT, this);
    parameters.addParameterListener(NAME_PITCHSHIFTER2_ACTIVE, this);
    parameters.addParameterListener(NAME_SHIMMER_DELAY_FEEDBACK, this);
    parameters.addParameterListener(NAME_SHIMMER_BRANCH_ROOMSIZE, this);
    parameters.addParameterListener(NAME_SHIMMER_BRANCH_DAMPING, this);
    parameters.addParameterListener(NAME_SHIMMER_BRANCH_WIDTH, this);
    parameters.addParameterListener(NAME_SHIMMER_MASTER_ROOMSIZE, this);
    //parameters.addParameterListener(NAME_DRYWETPITCH, this);

    dryWet.setDryWetRatio(DEFAULT_DRYWET);
    dryWetPitch.setDryWetRatio(DEFAULT_DRYWETPITCH);
    pitchShifter1.setShift(DEFAULT_PITCHSHIFTER1_SHIFT);
    pitchShifter2.setShift(DEFAULT_PITCHSHIFTER2_SHIFT);

    branchReverbParameters.roomSize = DEFAULT_SHIMMER_BRANCH_ROOMSIZE; // Big Room 1.0f
    branchReverbParameters.damping = DEFAULT_SHIMMER_BRANCH_DAMPING;
    branchReverbParameters.damping = DEFAULT_SHIMMER_BRANCH_WIDTH;
    branchReverb.setParameters(branchReverbParameters);

    delay.setTime(DEFAULT_SHIMMER_DELAY_TIME);
    delay.setFeedback(DEFAULT_SHIMMER_DELAY_FEEDBACK);


    masterReverbParameters.roomSize = DEFAULT_SHIMMER_MASTER_ROOMSIZE; // small Room
    masterReverb.setParameters(masterReverbParameters);

    /*
    parameters.addParameterListener(NAME_DRYWET, this);
    parameters.addParameterListener(NAME_DELAY_TIME, this);
    parameters.addParameterListener(NAME_DELAY_FEEDBACK, this);
    parameters.addParameterListener(NAME_LFO_FREQENCY, this);
    parameters.addParameterListener(NAME_MODULATION_DELAY, this);
    parameters.addParameterListener(NAME_LFO_WAVEFORM, this);

    dryWet.setDryWetRatio(DEFAULT_DRYWET);
    //delay.setTime(DEFAULT_DELAY_TIME);
    delay.setFeedback(DEFAULT_FEEDBACK);
    LFO.setFrequency(DEFAULT_LFO_FREQENCY);
    timeAdapter.setModAmount(DEFAULT_MODULATION_DELAY);
    LFO.setWaveform(DEFAULT_LFO_WAVEFORM);

    timeAdapter.setParameter(DEFAULT_DELAY_TIME);
    */
}

ShimmerAudioProcessor::~ShimmerAudioProcessor()
{
}

void ShimmerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    dspProcessSpec.sampleRate = sampleRate;
    dspProcessSpec.maximumBlockSize = samplesPerBlock;

    dryWet.prepareToPlay(sampleRate, samplesPerBlock);
    dryWetPitch.prepareToPlay(sampleRate, samplesPerBlock);
    pitchShifter1.prepareToPlay(sampleRate, samplesPerBlock);
    pitchShifter2.prepareToPlay(sampleRate, samplesPerBlock);
     
    branchReverb.prepare(dspProcessSpec);

    delay.prepareToPlay(sampleRate, samplesPerBlock);

    masterReverb.prepare(dspProcessSpec);

    branchReverb.reset();
    masterReverb.reset();
    

    /*
    dryWet.prepareToPlay(sampleRate, samplesPerBlock);
    delay.prepareToPlay(sampleRate, samplesPerBlock);
    LFO.prepareToPlay(sampleRate);
    modulationSignal.setSize(2, samplesPerBlock);
    timeAdapter.prepareToPlay(sampleRate);
    */

}

void ShimmerAudioProcessor::releaseResources()
{
    dryWet.releaseResources();
    dryWetPitch.releaseResources();
    pitchShifter1.releaseResurces();
    pitchShifter2.releaseResurces();

    branchReverb.reset();

    delay.releaseResurces();

    masterReverb.reset();
    /*
    dryWet.releaseResources();
    delay.releaseResurces();
    modulationSignal.setSize(0, 0);
    */
}

void ShimmerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    //int chN = buffer.getNumChannels();
    //auto x = chN > 1 ?  
    
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

    //setDry clean buffer
    dryWet.setDry(buffer); 

    //pitchShifter1
    pitchShifter1.processBlock(buffer);
    
    //setDry pitchShifter1
    dryWetPitch.setDry(buffer);

    //pitchShifter2
    pitchShifter2.processBlock(buffer); 

    //merge pitchShifter1 and pitchShifter2 (50%)
    dryWetPitch.merge(buffer);

    //branch reverb
    branchReverb.process(contextToUse);
    
    //delay
    delay.processBlock(buffer);

    //merge process and clean buffer
    dryWet.merge(buffer);

    //master reverb
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
    
    /*
    const auto numSamples = buffer.getNumSamples(); 
    
    // Genero una modulante
    LFO.getNextAudioBlock(modulationSignal, numSamples);

    // Scalare modulante
    timeAdapter.processBlock(modulationSignal, numSamples);

    // Salvo il segnale in input pulito
    dryWet.setDry(buffer);

    // Applicare delay
    //delay.processBlock(buffer);
    delay.processBlock(buffer, modulationSignal);
    
    // Miscelo il segnale pulito salvato in drywetter con quello processato da delay
    dryWet.merge(buffer);

    // ~~~ Listen to the wavez ~~~
    //LFO.getNextAudioBlock(buffer, buffer.getNumSamples());
    */
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


    /*if (paramID == NAME_DRYWETPITCH)
        dryWet.setDryWetRatio(newValue);*/


    /*
    if (paramID == NAME_DRYWET)
       dryWet.setDryWetRatio(newValue)
       ;
    if (paramID == NAME_DELAY_TIME)
        timeAdapter.setParameter(newValue);
        //delay.setTime(newValue);

    if (paramID == NAME_DELAY_FEEDBACK)
        delay.setFeedback(newValue);

    if (paramID == NAME_LFO_FREQENCY)
        LFO.setFrequency(newValue);

    if (paramID == NAME_MODULATION_DELAY)
        timeAdapter.setModAmount(newValue);

    if (paramID == NAME_LFO_WAVEFORM)
        LFO.setWaveform(newValue);
    */

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ShimmerAudioProcessor();
}
