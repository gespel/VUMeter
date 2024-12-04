#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "math.h"

//==============================================================================
VUMeterAudioProcessorEditor::VUMeterAudioProcessorEditor (VUMeterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    startTimer(10.0);
    setSize (300, 200);
}

VUMeterAudioProcessorEditor::~VUMeterAudioProcessorEditor()
{
}

//==============================================================================
void VUMeterAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    float angle = audioProcessor.getRMS()*M_PI + 3.3;
    g.setColour(juce::Colours::grey);
    g.drawLine(80 * cos(M_PI) + 150, 80 * sin(M_PI) + 150, 90 * cos(M_PI) + 150, 90 * sin(M_PI) + 150, 2.0);
    g.drawLine(80 * cos(1.25 * M_PI) + 150, 80 * sin(1.25 * M_PI) + 150, 90 * cos(1.25 * M_PI) + 150, 90 * sin(1.25 * M_PI) + 150, 2.0);
    g.drawLine(80 * cos(1.5 * M_PI) + 150, 80 * sin(1.5 * M_PI) + 150, 90 * cos(1.5 * M_PI) + 150, 90 * sin(1.5 * M_PI) + 150, 2.0);
    g.drawLine(80 * cos(1.75 * M_PI) + 150, 80 * sin(1.75 * M_PI) + 150, 90 * cos(1.75 * M_PI) + 150, 90 * sin(1.75 * M_PI) + 150, 2.0);
    g.drawLine(80 * cos(2 * M_PI) + 150, 80 * sin(2 * M_PI) + 150, 90 * cos(2 * M_PI) + 150, 90 * sin(2 * M_PI) + 150, 2.0);
    g.setColour(juce::Colours::darkslateblue);
    g.drawLine(30 * cos(angle) + 150, 30 * sin(angle) + 150, 100 * cos(angle) + 150, 100 * sin(angle) + 150, 3.0);
    g.drawFittedText ("Made by Phi Labs", getLocalBounds(), juce::Justification::centredTop, 1);
}

void VUMeterAudioProcessorEditor::resized()
{


}
