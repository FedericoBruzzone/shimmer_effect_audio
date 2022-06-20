#pragma once
#include <JuceHeader.h>

#define FPS       25
#define DB_FLOOR -48.0f
#define RT         0.5f

namespace Meter
{
    // === Bulb ===
    class Bulb : public juce::Component
    {
    public:
        Bulb(const juce::Colour& c);

        ~Bulb();

        void paint(juce::Graphics& g) override;

        void setState(const bool state);

    private:

        bool isOn = false;
        juce::Colour colour{};
    };

    // === VerticalGradientMeterAtomic ===
    class VerticalGradientMeterAtomic
    : public Component, public Timer
    {
    public:
        VerticalGradientMeterAtomic();

        ~VerticalGradientMeterAtomic();

        void paint(Graphics& g) override;

        void resized() override;

        void connectTo(Atomic<float>& targetVariable);

    private:

        void timerCallback() override;

        float alpha = 0.0f;

        Atomic<float>* observedEnvelope = nullptr;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VerticalGradientMeterAtomic);
    };

    // === VerticalDiscreteMeterAtomic ===
    class VerticalDiscreteMeterAtomic
        : public juce::Component, public juce::Timer
    {
    public:
        VerticalDiscreteMeterAtomic();

        ~VerticalDiscreteMeterAtomic();

        void paint(juce::Graphics& g) override;

        void resized() override;

        void connectTo(Atomic<float>& targetVariable);

    private:
        void timerCallback() override;

        Atomic<float>* observedEnvelope = nullptr;
        std::vector<std::unique_ptr<Bulb>> bulbs;
        juce::ColourGradient gradient{};
        const int totalNumberOfBulbs = 15;
    };
    
    // === HorizontalMeter ===
    class HorizontalMeter : public juce::Component
    {
    public:
        HorizontalMeter();
        ~HorizontalMeter();

        void paint(juce::Graphics& g) override;

        void resized() override;

        void setLevel(const float value);
    private:
        float level = -60.f;
    };

    // === VerticalGradientMeter ===
    class VerticalGradientMeter : public juce::Component, public juce::Timer
    {
    public:
        VerticalGradientMeter(std::function<float()>&& valueFunction);

        ~VerticalGradientMeter();

        void paint(juce::Graphics& g) override;

        void resized() override;

    private:
        void timerCallback() override;

        std::function<float()> valueSupplier;
        juce::ColourGradient gradient{};
    };
   
    // === VerticalDiscreteMeter ===
    class VerticalDiscreteMeter : public juce::Component, public juce::Timer
    {
    public:
        VerticalDiscreteMeter(std::function<float()>&& valueFunction);

        ~VerticalDiscreteMeter();

        void paint(juce::Graphics& g) override;

        void resized() override;

        void timerCallback() override;

    private:
        std::function<float()> valueSupplier;
        std::vector<std::unique_ptr<Bulb>> bulbs;
        juce::ColourGradient gradient{};
        const int totalNumberOfBulbs = 10;
    };
   
}