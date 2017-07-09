/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
JuceFilterAudioProcessor::JuceFilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
	
#endif
{
	addParameter(filterCutoff = new AudioParameterFloat("FilterCutoff", "Filter Cutoff", 50, 22'000, 22'000));
	addParameter(filterQ = new AudioParameterFloat("FilterQ", "Filter Q", 0.001, 1, 0.5));
}

JuceFilterAudioProcessor::~JuceFilterAudioProcessor()
{
}

//==============================================================================
const String JuceFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JuceFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double JuceFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JuceFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceFilterAudioProcessor::setCurrentProgram (int index)
{
}

const String JuceFilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void JuceFilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JuceFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	
}

void JuceFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JuceFilterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	IIRCoefficients coeffs = IIRCoefficients::makeLowPass(getSampleRate(), *filterCutoff, *filterQ);
	filterL.setCoefficients(coeffs);
	filterR.setCoefficients(coeffs);

	const int numSamples = buffer.getNumSamples();

	float* outL = buffer.getWritePointer(0);
	float* outR = buffer.getWritePointer(1);
	filterL.processSamples(outL, numSamples);
	filterR.processSamples(outR, numSamples);
}

//==============================================================================
bool JuceFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JuceFilterAudioProcessor::createEditor()
{
    return new JuceFilterAudioProcessorEditor (*this);
}

//==============================================================================
void JuceFilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceFilterAudioProcessor();
}
