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

//[Headers] You can add your own extra header files here...
#include "Parameters.h"
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginEditor::PluginEditor (ShimmerAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState (vts)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    branchRoomSize.reset (new juce::Slider ("Reverb Branch Room Size "));
    addAndMakeVisible (branchRoomSize.get());
    branchRoomSize->setRange (0, 10, 0);
    branchRoomSize->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    branchRoomSize->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    branchRoomSize->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);

    branchRoomSize->setBounds (200, 136, 136, 160);

    branchDamping.reset (new juce::Slider ("Reverb Branch Damping"));
    addAndMakeVisible (branchDamping.get());
    branchDamping->setRange (0, 10, 0);
    branchDamping->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    branchDamping->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    branchDamping->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);

    branchDamping->setBounds (488, 136, 136, 160);

    branchWidth.reset (new juce::Slider ("Reverb Branch Width"));
    addAndMakeVisible (branchWidth.get());
    branchWidth->setRange (0, 10, 0);
    branchWidth->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    branchWidth->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    branchWidth->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);

    branchWidth->setBounds (800, 136, 136, 160);

    delayFeedback.reset (new juce::Slider ("Delay Feedback (s)"));
    addAndMakeVisible (delayFeedback.get());
    delayFeedback->setRange (0, 10, 0);
    delayFeedback->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    delayFeedback->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    delayFeedback->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);

    delayFeedback->setBounds (192, 536, 136, 160);

    pitchShifter1Shift.reset (new juce::Slider ("Pitch Shifter 1 (semitone)"));
    addAndMakeVisible (pitchShifter1Shift.get());
    pitchShifter1Shift->setRange (0, 10, 0);
    pitchShifter1Shift->setSliderStyle (juce::Slider::LinearVertical);
    pitchShifter1Shift->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    pitchShifter1Shift->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);

    pitchShifter1Shift->setBounds (496, 440, 88, 328);

    pitchShifter2Shift.reset (new juce::Slider ("Pitch Shifter 2 (semitone)"));
    addAndMakeVisible (pitchShifter2Shift.get());
    pitchShifter2Shift->setRange (0, 10, 0);
    pitchShifter2Shift->setSliderStyle (juce::Slider::LinearVertical);
    pitchShifter2Shift->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    pitchShifter2Shift->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);

    pitchShifter2Shift->setBounds (840, 440, 88, 328);

    dryWet.reset (new juce::Slider ("Dry / Wet"));
    addAndMakeVisible (dryWet.get());
    dryWet->setRange (0, 10, 0);
    dryWet->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    dryWet->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    dryWet->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);

    dryWet->setBounds (1080, 128, 136, 160);

    masterRoomSize.reset (new juce::Slider ("Reverb Master Room Size"));
    addAndMakeVisible (masterRoomSize.get());
    masterRoomSize->setRange (0, 10, 0);
    masterRoomSize->setSliderStyle (juce::Slider::RotaryVerticalDrag);
    masterRoomSize->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    masterRoomSize->setColour (juce::Slider::textBoxTextColourId, juce::Colours::black);

    masterRoomSize->setBounds (1080, 528, 136, 160);

    pitchShifter2Active.reset (new juce::ToggleButton ("Pitch Shifter 2 Active"));
    addAndMakeVisible (pitchShifter2Active.get());
    pitchShifter2Active->setButtonText (juce::String());
    pitchShifter2Active->setColour (juce::ToggleButton::textColourId, juce::Colours::black);

    pitchShifter2Active->setBounds (968, 736, 40, 32);

    outputVerticalDiscreteMeterAtomicLeft.reset (new Meter::VerticalDiscreteMeterAtomic());
    addAndMakeVisible (outputVerticalDiscreteMeterAtomicLeft.get());
    outputVerticalDiscreteMeterAtomicLeft->setName ("O Vertical Discrete Meter Atomic Left");

    outputVerticalDiscreteMeterAtomicLeft->setBounds (1296, 101, 24, 688);

    outputVerticalDiscreteMeterAtomicRight.reset (new Meter::VerticalDiscreteMeterAtomic());
    addAndMakeVisible (outputVerticalDiscreteMeterAtomicRight.get());
    outputVerticalDiscreteMeterAtomicRight->setName ("O Vertical Discrete Meter Atomic Right");

    outputVerticalDiscreteMeterAtomicRight->setBounds (1328, 101, 24, 688);

    inputVerticalDiscreteMeterAtomicLeft.reset (new Meter::VerticalDiscreteMeterAtomic());
    addAndMakeVisible (inputVerticalDiscreteMeterAtomicLeft.get());
    inputVerticalDiscreteMeterAtomicLeft->setName ("I Vertical Discrete Meter Atomic Left");

    inputVerticalDiscreteMeterAtomicLeft->setBounds (40, 101, 24, 688);

    inputVerticalDiscreteMeterAtomicRight.reset (new Meter::VerticalDiscreteMeterAtomic());
    addAndMakeVisible (inputVerticalDiscreteMeterAtomicRight.get());
    inputVerticalDiscreteMeterAtomicRight->setName ("I Vertical Discrete Meter Atomic Right");

    inputVerticalDiscreteMeterAtomicRight->setBounds (72, 101, 24, 688);


    //[UserPreSize]
    branchRoomSizeAttachment.reset(new SliderAttachment(valueTreeState, NAME_SHIMMER_BRANCH_ROOMSIZE, *branchRoomSize));
    branchDampingAttachment.reset(new SliderAttachment(valueTreeState, NAME_SHIMMER_BRANCH_DAMPING, *branchDamping));
    branchWidthAttachment.reset(new SliderAttachment(valueTreeState, NAME_SHIMMER_BRANCH_WIDTH, *branchWidth));
    delayFeedbackAttachment.reset(new SliderAttachment(valueTreeState, NAME_SHIMMER_DELAY_FEEDBACK, *delayFeedback));
    pitchShifter1ShiftAttachment.reset(new SliderAttachment(valueTreeState, NAME_PITCHSHIFTER1_SHIFT, *pitchShifter1Shift));
    pitchShifter2ShiftAttachment.reset(new SliderAttachment(valueTreeState, NAME_PITCHSHIFTER2_SHIFT, *pitchShifter2Shift));
    pitchShifter2ActiveAttachment.reset(new ButtonAttachment(valueTreeState, NAME_PITCHSHIFTER2_ACTIVE, *pitchShifter2Active));
    dryWetAttachment.reset(new SliderAttachment(valueTreeState, NAME_DRYWET, *dryWet));
    masterRoomSizeAttachment.reset(new SliderAttachment(valueTreeState, NAME_SHIMMER_MASTER_ROOMSIZE, *masterRoomSize));

    inputVerticalDiscreteMeterAtomicLeft->connectTo(p.envelopeInput[0]);
    inputVerticalDiscreteMeterAtomicRight->connectTo(p.envelopeInput[1]);

    outputVerticalDiscreteMeterAtomicLeft->connectTo(p.envelopeOutput[0]);
    outputVerticalDiscreteMeterAtomicRight->connectTo(p.envelopeOutput[1]);

    branchRoomSize->setLookAndFeel(&myTheme);
    branchDamping->setLookAndFeel(&myTheme);
    branchWidth->setLookAndFeel(&myTheme);
    delayFeedback->setLookAndFeel(&myTheme);
    //pitchShifter1Shift
    //pitchShifter2Shift
    pitchShifter2Active->getLookAndFeel().setColour(juce::ToggleButton::ColourIds::tickColourId, juce::Colours::black);
    pitchShifter2Active->getLookAndFeel().setColour(juce::ToggleButton::ColourIds::tickDisabledColourId, juce::Colours::black);

    dryWet->setLookAndFeel(&myTheme);
    masterRoomSize->setLookAndFeel(&myTheme);


    //[/UserPreSize]

    setSize (1390, 840);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PluginEditor::~PluginEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    branchRoomSizeAttachment.reset();
    branchDampingAttachment.reset();
    branchWidthAttachment.reset();
    delayFeedbackAttachment.reset();
    pitchShifter1ShiftAttachment.reset();
    pitchShifter2ShiftAttachment.reset();
    pitchShifter2ActiveAttachment.reset();
    dryWetAttachment.reset();
    masterRoomSizeAttachment.reset();

    branchRoomSize->setLookAndFeel(nullptr);
    branchDamping->setLookAndFeel(nullptr);
    branchWidth->setLookAndFeel(nullptr);
    delayFeedback->setLookAndFeel(nullptr);
    //pitchShifter1Shift
    //pitchShifter2Shift
    //pitchShifter2Active
    dryWet->setLookAndFeel(nullptr);
    masterRoomSize->setLookAndFeel(nullptr);
    //[/Destructor_pre]

    branchRoomSize = nullptr;
    branchDamping = nullptr;
    branchWidth = nullptr;
    delayFeedback = nullptr;
    pitchShifter1Shift = nullptr;
    pitchShifter2Shift = nullptr;
    dryWet = nullptr;
    masterRoomSize = nullptr;
    pitchShifter2Active = nullptr;
    outputVerticalDiscreteMeterAtomicLeft = nullptr;
    outputVerticalDiscreteMeterAtomicRight = nullptr;
    inputVerticalDiscreteMeterAtomicLeft = nullptr;
    inputVerticalDiscreteMeterAtomicRight = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginEditor::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::white);

    {
        int x = 0, y = 0, width = 1392, height = 840;
        juce::Colour fillColour1 = juce::Colour (0xfff1ff00), fillColour2 = juce::Colour (0xffff9700);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             88.0f - 0.0f + x,
                                             368.0f - 0.0f + y,
                                             fillColour2,
                                             1280.0f - 0.0f + x,
                                             400.0f - 0.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 1044, y = 0, width = 204, height = 840;
        juce::Colour fillColour1 = juce::Colours::white, fillColour2 = juce::Colour (0xfff1ff00);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             1136.0f - 1044.0f + x,
                                             640.0f - 0.0f + y,
                                             fillColour2,
                                             1400.0f - 1044.0f + x,
                                             848.0f - 0.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 142, y = 0, width = 896, height = 352;
        juce::Colour fillColour1 = juce::Colour (0xffff9700), fillColour2 = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             56.0f - 142.0f + x,
                                             static_cast<float> (-8) - 0.0f + y,
                                             fillColour2,
                                             920.0f - 142.0f + x,
                                             296.0f - 0.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 141, y = 356, width = 240, height = 484;
        juce::Colour fillColour1 = juce::Colour (0xffff9700), fillColour2 = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             120.0f - 141.0f + x,
                                             232.0f - 356.0f + y,
                                             fillColour2,
                                             696.0f - 141.0f + x,
                                             560.0f - 356.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 167, y = 108, width = 204, height = 28;
        juce::String text (TRANS("Room Size"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 440, y = 28, width = 276, height = 52;
        juce::String text (TRANS("Branch Reverb"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 35.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 159, y = 380, width = 209, height = 52;
        juce::String text (TRANS("Delay"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 35.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 159, y = 508, width = 204, height = 28;
        juce::String text (TRANS("Feedback"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 385, y = 356, width = 332, height = 484;
        juce::Colour fillColour1 = juce::Colour (0xffff9700), fillColour2 = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             192.0f - 385.0f + x,
                                             296.0f - 356.0f + y,
                                             fillColour2,
                                             568.0f - 385.0f + x,
                                             664.0f - 356.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 721, y = 356, width = 317, height = 484;
        juce::Colour fillColour1 = juce::Colour (0xffff9700), fillColour2 = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             112.0f - 721.0f + x,
                                             16.0f - 356.0f + y,
                                             fillColour2,
                                             832.0f - 721.0f + x,
                                             392.0f - 356.0f + y,
                                             false));
        g.fillRect (x, y, width, height);
    }

    {
        int x = 404, y = 372, width = 276, height = 52;
        juce::String text (TRANS("Pitch Shifter 1"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 35.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 740, y = 372, width = 276, height = 52;
        juce::String text (TRANS("Pitch Shifter 2"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 35.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 936, y = 768, width = 84, height = 28;
        juce::String text (TRANS("Active"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 848, y = 768, width = 76, height = 28;
        juce::String text (TRANS("Shift "));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 504, y = 768, width = 72, height = 28;
        juce::String text (TRANS("Shift "));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 456, y = 108, width = 204, height = 28;
        juce::String text (TRANS("Damping"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 760, y = 108, width = 204, height = 28;
        juce::String text (TRANS("Width"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 1044, y = 107, width = 204, height = 28;
        juce::String text (TRANS("Mix"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 1044, y = 507, width = 204, height = 28;
        juce::String text (TRANS("Reverb Room Size"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 1060, y = 35, width = 180, height = 52;
        juce::String text (TRANS("Master"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 35.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        float x = 1252.0f, y = 0.0f, width = 135.0f, height = 840.0f;
        juce::Colour fillColour1 = juce::Colours::white, fillColour2 = juce::Colour (0xfff1ff00);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             1152.0f - 1252.0f + x,
                                             600.0f - 0.0f + y,
                                             fillColour2,
                                             1440.0f - 1252.0f + x,
                                             840.0f - 0.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        int x = 1260, y = 35, width = 117, height = 52;
        juce::String text (TRANS("Output"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 35.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        float x = 2.0f, y = 0.0f, width = 135.0f, height = 840.0f;
        juce::Colour fillColour1 = juce::Colour (0xffff9700), fillColour2 = juce::Colours::white;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setGradientFill (juce::ColourGradient (fillColour1,
                                             32.0f - 2.0f + x,
                                             static_cast<float> (-48) - 0.0f + y,
                                             fillColour2,
                                             1440.0f - 2.0f + x,
                                             840.0f - 0.0f + y,
                                             false));
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
    }

    {
        int x = 7, y = 44, width = 117, height = 52;
        juce::String text (TRANS("Input"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 35.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 40, y = 794, width = 24, height = 28;
        juce::String text (TRANS("L"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 72, y = 794, width = 24, height = 28;
        juce::String text (TRANS("R"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 1296, y = 794, width = 24, height = 28;
        juce::String text (TRANS("L"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 1328, y = 794, width = 24, height = 28;
        juce::String text (TRANS("R"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 104, y = 112, width = 24, height = 28;
        juce::String text (TRANS("+6"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 96, y = 752, width = 34, height = 28;
        juce::String text (TRANS("-60"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 104, y = 288, width = 24, height = 28;
        juce::String text (TRANS("0"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 1360, y = 112, width = 24, height = 28;
        juce::String text (TRANS("+6"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 1352, y = 752, width = 34, height = 28;
        juce::String text (TRANS("-60"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    {
        int x = 1360, y = 288, width = 24, height = 28;
        juce::String text (TRANS("0"));
        juce::Colour fillColour = juce::Colours::black;
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.setFont (juce::Font ("Lemon", 20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
        g.drawText (text, x, y, width, height,
                    juce::Justification::centred, true);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PluginEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginEditor" componentName=""
                 parentClasses="public juce::AudioProcessorEditor" constructorParams="ShimmerAudioProcessor&amp; p, AudioProcessorValueTreeState&amp; vts"
                 variableInitialisers="AudioProcessorEditor (&amp;p), processor (p), valueTreeState (vts)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="1390" initialHeight="840">
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="0 0 1392 840" fill="linear: 88 368, 1280 400, 0=fff1ff00, 1=ffff9700"
          hasStroke="0"/>
    <RECT pos="1044 0 204 840" fill="linear: 1136 640, 1400 848, 0=ffffffff, 1=fff1ff00"
          hasStroke="0"/>
    <RECT pos="142 0 896 352" fill="linear: 56 -8, 920 296, 0=ffff9700, 1=ffffffff"
          hasStroke="0"/>
    <RECT pos="141 356 240 484" fill="linear: 120 232, 696 560, 0=ffff9700, 1=ffffffff"
          hasStroke="0"/>
    <TEXT pos="167 108 204 28" fill="solid: ff000000" hasStroke="0" text="Room Size"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="440 28 276 52" fill="solid: ff000000" hasStroke="0" text="Branch Reverb"
          fontname="Lemon" fontsize="35.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="159 380 209 52" fill="solid: ff000000" hasStroke="0" text="Delay"
          fontname="Lemon" fontsize="35.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="159 508 204 28" fill="solid: ff000000" hasStroke="0" text="Feedback"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <RECT pos="385 356 332 484" fill="linear: 192 296, 568 664, 0=ffff9700, 1=ffffffff"
          hasStroke="0"/>
    <RECT pos="721 356 317 484" fill="linear: 112 16, 832 392, 0=ffff9700, 1=ffffffff"
          hasStroke="0"/>
    <TEXT pos="404 372 276 52" fill="solid: ff000000" hasStroke="0" text="Pitch Shifter 1"
          fontname="Lemon" fontsize="35.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="740 372 276 52" fill="solid: ff000000" hasStroke="0" text="Pitch Shifter 2"
          fontname="Lemon" fontsize="35.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="936 768 84 28" fill="solid: ff000000" hasStroke="0" text="Active"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="848 768 76 28" fill="solid: ff000000" hasStroke="0" text="Shift "
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="504 768 72 28" fill="solid: ff000000" hasStroke="0" text="Shift "
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="456 108 204 28" fill="solid: ff000000" hasStroke="0" text="Damping"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="760 108 204 28" fill="solid: ff000000" hasStroke="0" text="Width"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="1044 107 204 28" fill="solid: ff000000" hasStroke="0" text="Mix"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="1044 507 204 28" fill="solid: ff000000" hasStroke="0" text="Reverb Room Size"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="1060 35 180 52" fill="solid: ff000000" hasStroke="0" text="Master"
          fontname="Lemon" fontsize="35.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <ROUNDRECT pos="1252 0 135 840" cornerSize="10.0" fill="linear: 1152 600, 1440 840, 0=ffffffff, 1=fff1ff00"
               hasStroke="0"/>
    <TEXT pos="1260 35 117 52" fill="solid: ff000000" hasStroke="0" text="Output"
          fontname="Lemon" fontsize="35.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <ROUNDRECT pos="2 0 135 840" cornerSize="10.0" fill="linear: 32 -48, 1440 840, 0=ffff9700, 1=ffffffff"
               hasStroke="0"/>
    <TEXT pos="7 44 117 52" fill="solid: ff000000" hasStroke="0" text="Input"
          fontname="Lemon" fontsize="35.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="40 794 24 28" fill="solid: ff000000" hasStroke="0" text="L"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="72 794 24 28" fill="solid: ff000000" hasStroke="0" text="R"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="1296 794 24 28" fill="solid: ff000000" hasStroke="0" text="L"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="1328 794 24 28" fill="solid: ff000000" hasStroke="0" text="R"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="104 112 24 28" fill="solid: ff000000" hasStroke="0" text="+6"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="96 752 34 28" fill="solid: ff000000" hasStroke="0" text="-60"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="104 288 24 28" fill="solid: ff000000" hasStroke="0" text="0"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="1360 112 24 28" fill="solid: ff000000" hasStroke="0" text="+6"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="1352 752 34 28" fill="solid: ff000000" hasStroke="0" text="-60"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
    <TEXT pos="1360 288 24 28" fill="solid: ff000000" hasStroke="0" text="0"
          fontname="Lemon" fontsize="20.0" kerning="0.0" bold="0" italic="0"
          justification="36"/>
  </BACKGROUND>
  <SLIDER name="Reverb Branch Room Size " id="1f8692b6f23252ce" memberName="branchRoomSize"
          virtualName="" explicitFocusOrder="0" pos="200 136 136 160" textboxtext="ff000000"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Reverb Branch Damping" id="3a19ef35b10180cb" memberName="branchDamping"
          virtualName="" explicitFocusOrder="0" pos="488 136 136 160" textboxtext="ff000000"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Reverb Branch Width" id="b340104988e98e43" memberName="branchWidth"
          virtualName="" explicitFocusOrder="0" pos="800 136 136 160" textboxtext="ff000000"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Delay Feedback (s)" id="68f2f9a01198c5c9" memberName="delayFeedback"
          virtualName="" explicitFocusOrder="0" pos="192 536 136 160" textboxtext="ff000000"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Pitch Shifter 1 (semitone)" id="d1d2107481aa8b99" memberName="pitchShifter1Shift"
          virtualName="" explicitFocusOrder="0" pos="496 440 88 328" textboxtext="ff000000"
          min="0.0" max="10.0" int="0.0" style="LinearVertical" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Pitch Shifter 2 (semitone)" id="779f81b39c9a3161" memberName="pitchShifter2Shift"
          virtualName="" explicitFocusOrder="0" pos="840 440 88 328" textboxtext="ff000000"
          min="0.0" max="10.0" int="0.0" style="LinearVertical" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Dry / Wet" id="6f67b48430b430a4" memberName="dryWet" virtualName=""
          explicitFocusOrder="0" pos="1080 128 136 160" textboxtext="ff000000"
          min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <SLIDER name="Reverb Master Room Size" id="de50c78aed1205df" memberName="masterRoomSize"
          virtualName="" explicitFocusOrder="0" pos="1080 528 136 160"
          textboxtext="ff000000" min="0.0" max="10.0" int="0.0" style="RotaryVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="0"/>
  <TOGGLEBUTTON name="Pitch Shifter 2 Active" id="d8e68c0eeff17294" memberName="pitchShifter2Active"
                virtualName="" explicitFocusOrder="0" pos="968 736 40 32" txtcol="ff000000"
                buttonText="" connectedEdges="0" needsCallback="0" radioGroupId="0"
                state="0"/>
  <GENERICCOMPONENT name="O Vertical Discrete Meter Atomic Left" id="709bcf1c92a5c8f5"
                    memberName="outputVerticalDiscreteMeterAtomicLeft" virtualName="Meter::VerticalDiscreteMeterAtomic"
                    explicitFocusOrder="0" pos="1296 101 24 688" class="juce::Component"
                    params=""/>
  <GENERICCOMPONENT name="O Vertical Discrete Meter Atomic Right" id="2f677063f8984cf3"
                    memberName="outputVerticalDiscreteMeterAtomicRight" virtualName="Meter::VerticalDiscreteMeterAtomic"
                    explicitFocusOrder="0" pos="1328 101 24 688" class="juce::Component"
                    params=""/>
  <GENERICCOMPONENT name="I Vertical Discrete Meter Atomic Left" id="fe6087d8b76d5fdf"
                    memberName="inputVerticalDiscreteMeterAtomicLeft" virtualName="Meter::VerticalDiscreteMeterAtomic"
                    explicitFocusOrder="0" pos="40 101 24 688" class="juce::Component"
                    params=""/>
  <GENERICCOMPONENT name="I Vertical Discrete Meter Atomic Right" id="15318eb06a7452a1"
                    memberName="inputVerticalDiscreteMeterAtomicRight" virtualName="Meter::VerticalDiscreteMeterAtomic"
                    explicitFocusOrder="0" pos="72 101 24 688" class="juce::Component"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

