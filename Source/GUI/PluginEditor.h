/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.6

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "MyTheme.h"
#include "Meter.h"

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginEditor  : public juce::AudioProcessorEditor
{
public:
    //==============================================================================
    PluginEditor (ShimmerAudioProcessor& p, AudioProcessorValueTreeState& vts);
    ~PluginEditor() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    ShimmerAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    std::unique_ptr<SliderAttachment> branchRoomSizeAttachment;
    std::unique_ptr<SliderAttachment> branchDampingAttachment;
    std::unique_ptr<SliderAttachment> branchWidthAttachment;
    std::unique_ptr<SliderAttachment> delayFeedbackAttachment;
    std::unique_ptr<SliderAttachment> pitchShifter1ShiftAttachment;
    std::unique_ptr<SliderAttachment> pitchShifter2ShiftAttachment;
    std::unique_ptr<ButtonAttachment> pitchShifter2ActiveAttachment;
    std::unique_ptr<SliderAttachment> dryWetAttachment;
    std::unique_ptr<SliderAttachment> delayTimeAttachment;

    MyLookAndFeel myTheme;

    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Slider> branchRoomSize;
    std::unique_ptr<juce::Slider> branchDamping;
    std::unique_ptr<juce::Slider> branchWidth;
    std::unique_ptr<juce::Slider> delayFeedback;
    std::unique_ptr<juce::Slider> pitchShifter1Shift;
    std::unique_ptr<juce::Slider> pitchShifter2Shift;
    std::unique_ptr<juce::Slider> dryWet;
    std::unique_ptr<juce::Slider> delayTime;
    std::unique_ptr<juce::ToggleButton> pitchShifter2Active;
    std::unique_ptr<Meter::VerticalDiscreteMeterAtomic> outputVerticalDiscreteMeterAtomicLeft;
    std::unique_ptr<Meter::VerticalDiscreteMeterAtomic> outputVerticalDiscreteMeterAtomicRight;
    std::unique_ptr<Meter::VerticalDiscreteMeterAtomic> inputVerticalDiscreteMeterAtomicLeft;
    std::unique_ptr<Meter::VerticalDiscreteMeterAtomic> inputVerticalDiscreteMeterAtomicRight;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginEditor)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

