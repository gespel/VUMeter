/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "math.h"

//==============================================================================
VUMeterAudioProcessorEditor::VUMeterAudioProcessorEditor (VUMeterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    startTimer(10.0);
    setSize (400, 300);
}

VUMeterAudioProcessorEditor::~VUMeterAudioProcessorEditor()
{
}

//==============================================================================
void VUMeterAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto& random = juce::Random::getSystemRandom();
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    //float angle = (float) random.nextFloat()*2.5 + 3.3;
    float angle = audioProcessor.getRMS()*2.5 + 3.3;
    g.drawLine(30 * cos(angle) + 150, 30 * sin(angle) + 150, 100 * cos(angle) + 150, 100 * sin(angle) + 150, 3.0);
    //std::cout << angle << std::endl;
}

void VUMeterAudioProcessorEditor::resized()
{

    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
