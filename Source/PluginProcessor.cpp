
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VUMeterAudioProcessor::VUMeterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

VUMeterAudioProcessor::~VUMeterAudioProcessor()
{
}

//==============================================================================
const juce::String VUMeterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool VUMeterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool VUMeterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool VUMeterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double VUMeterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int VUMeterAudioProcessor::getNumPrograms()
{
    return 1;
}

int VUMeterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void VUMeterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String VUMeterAudioProcessor::getProgramName (int index)
{
    return {};
}

void VUMeterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

void VUMeterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

}

void VUMeterAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VUMeterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void VUMeterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    auto* channelDataL = buffer.getWritePointer (0);
    auto* channelDataR = buffer.getWritePointer (1);
    float tmp = 0;
    for(int sample = 0; sample < buffer.getNumSamples(); sample++) {
        tmp += (channelDataL[sample] + channelDataR[sample])/2 * (channelDataL[sample] + channelDataR[sample])/2;
    }
    rms = (sqrt(tmp/buffer.getNumSamples()) + prevRMS) / 2;
    prevRMS = sqrt(tmp/buffer.getNumSamples());
}

bool VUMeterAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* VUMeterAudioProcessor::createEditor()
{
    return new VUMeterAudioProcessorEditor (*this);
}

//==============================================================================
void VUMeterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{

}

void VUMeterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

}

float VUMeterAudioProcessor::getRMS() {
    return rms;				
}


juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new VUMeterAudioProcessor();
}
