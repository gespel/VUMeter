/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class VUMeterAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    VUMeterAudioProcessorEditor (VUMeterAudioProcessor&);
    ~VUMeterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VUMeterAudioProcessor& audioProcessor;
    int i = 0;
    juce::Line<float> vu_line;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VUMeterAudioProcessorEditor)
    void timerCallback() final {
        repaint();
    }
    float angle = 0;
};
