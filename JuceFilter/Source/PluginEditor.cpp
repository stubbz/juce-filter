/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JuceFilterAudioProcessorEditor::JuceFilterAudioProcessorEditor (JuceFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{

	addAndMakeVisible(&cutoffSlider);
	cutoffSlider.addListener(this);
	cutoffSlider.setRange(50, 20'000);
	cutoffSlider.setTextValueSuffix(" Hz");
	cutoffSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	cutoffSlider.setSkewFactorFromMidPoint(1000);
	cutoffSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 200, 20);
	addAndMakeVisible(&cutoffLabel);
	cutoffLabel.setText("Cutoff", dontSendNotification);
	cutoffLabel.attachToComponent(&cutoffSlider, false);

	addAndMakeVisible(&qSlider);
	qSlider.addListener(this);
	qSlider.setRange(0.001, 1);
	qSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	qSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 200, 20);
	addAndMakeVisible(&qLabel);
	qLabel.setText("Q", dontSendNotification);
	qLabel.attachToComponent(&qSlider, false);

	setSize(400, 220);
}

JuceFilterAudioProcessorEditor::~JuceFilterAudioProcessorEditor()
{
}

//==============================================================================
void JuceFilterAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);


}

void JuceFilterAudioProcessorEditor::resized()
{
	cutoffSlider.setBounds(0, 20, 200, 200);
	qSlider.setBounds(200, 20, 200, 200);
}

void JuceFilterAudioProcessorEditor::sliderValueChanged(Slider* slider) {
	if (slider == &cutoffSlider) {
		*processor.filterCutoff = slider->getValue();
	}
	else if (slider == &qSlider) {
		*processor.filterQ = slider->getValue();
	}
}