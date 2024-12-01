#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class VUMeterAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    VUMeterAudioProcessorEditor (VUMeterAudioProcessor&);
    ~VUMeterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    VUMeterAudioProcessor& audioProcessor;
    int i = 0;
    juce::Line<float> vu_line;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VUMeterAudioProcessorEditor)
    void timerCallback() final {
        repaint();
    }
    float angle = 0;
};
