/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class JuceFilterAudioProcessorEditor  : public AudioProcessorEditor, 
	private Slider::Listener
{
public:
    JuceFilterAudioProcessorEditor (JuceFilterAudioProcessor&);
    ~JuceFilterAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void sliderValueChanged(Slider * slider) override;

private:
    Label cutoffLabel;
    Slider cutoffSlider;
    Label qLabel;
    Slider qSlider;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceFilterAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceFilterAudioProcessorEditor)
};
