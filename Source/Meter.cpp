#include "Meter.h"

// === Bulb === 
Meter::Bulb::Bulb(const juce::Colour& c) : colour(c) 
{
}

Meter::Bulb::~Bulb()
{

}

void Meter::Bulb::paint(juce::Graphics& g)
{
    const auto delta = 4.f;
    const auto bounds = getLocalBounds().toFloat().reduced(delta);
    const auto side = juce::jmin(bounds.getWidth(), bounds.getHeight());
    const auto bulbFillBounds = juce::Rectangle<float>{ bounds.getX(), bounds.getY(), side, side };
    if (isOn)
        g.setColour(colour);
    else
        g.setColour(juce::Colours::black);

    g.fillEllipse(bulbFillBounds);
    g.setColour(juce::Colours::black);
    g.drawEllipse(bulbFillBounds, 1.f);

    if (isOn)
    {
        g.setGradientFill(
            juce::ColourGradient{
                colour.withAlpha(0.3f),
                bulbFillBounds.getCentre(),
                colour.withLightness(1.5f).withAlpha(0.f),
                { },
                true
            });
        g.fillEllipse(bulbFillBounds.expanded(delta));
    }
}

void Meter::Bulb::setState(const bool state) 
{ 
    isOn = state; 
}

// === Vertical Gradient Meter Atomic ===
Meter::VerticalGradientMeterAtomic::VerticalGradientMeterAtomic()
{
    alpha = exp(-1.0f / (FPS * RT));
    startTimerHz(FPS);
}

Meter::VerticalGradientMeterAtomic::~VerticalGradientMeterAtomic()
{
    stopTimer();
}

void Meter::VerticalGradientMeterAtomic::paint(Graphics& g)
{
    auto W = getWidth();
    auto H = getHeight();

    g.fillAll(Colours::black);
    g.setColour(Colours::grey);
    g.drawRect(0, 0, W, H, 1);

    if (observedEnvelope != nullptr)
    {
        auto envelopeSnapshot = observedEnvelope->get();
        observedEnvelope->set(envelopeSnapshot * alpha);

        auto peak = Decibels::gainToDecibels(envelopeSnapshot);

        //auto barHeight = (H - 2) * (peak - DB_FLOOR) / abs(DB_FLOOR);
        auto barHeight = jmap(peak, DB_FLOOR, 0.0f, 0.0f, H - 2.0f);
        barHeight = jlimit(0.0f, H - 2.0f, barHeight);

        auto topColour = peak >= 0.0f ? Colours::red : Colours::yellow;
        ColourGradient filler = ColourGradient(Colours::blue, 0, H, topColour, 0, 0, false);
        filler.addColour(0.8f, Colours::green);

        //g.setColour(peak >= 0.0f ? Colours::red : Colours::blueviolet);
        g.setGradientFill(filler);

        g.fillRect(1.0f, H - 1.0f - barHeight, W - 2.0f, barHeight);
    }

}

void Meter::VerticalGradientMeterAtomic::resized()
{
}

void Meter::VerticalGradientMeterAtomic::connectTo(Atomic<float>& targetVariable)
{
    observedEnvelope = &targetVariable;
}

void Meter::VerticalGradientMeterAtomic::timerCallback()
{
    repaint();
}

// === Vertical Discrete Meter Atomic ===
Meter::VerticalDiscreteMeterAtomic::VerticalDiscreteMeterAtomic()
{
    startTimer(24);
}

Meter::VerticalDiscreteMeterAtomic::~VerticalDiscreteMeterAtomic()
{
    stopTimer();
}

void Meter::VerticalDiscreteMeterAtomic::paint(juce::Graphics& g)
{
    const auto level = jmap(static_cast<float>(observedEnvelope->value), -60.f, 6.f, 0.f, 1.f);

    for (auto i = 0; i < totalNumberOfBulbs; i++)
    {
        if (level >= static_cast<float>(i + 1) / totalNumberOfBulbs)
            bulbs[i]->setState(true);
        else
            bulbs[i]->setState(false);
    }
}

void Meter::VerticalDiscreteMeterAtomic::resized()
{
    const auto bounds = getLocalBounds().toFloat();
    gradient = juce::ColourGradient{
        juce::Colours::green,
        bounds.getBottomLeft(),
        juce::Colours::red,
        bounds.getTopLeft(),
        false
    };

    gradient.addColour(0.5, juce::Colours::yellow);

    auto bulbBounds = getLocalBounds();
    const auto bulbHeight = bulbBounds.getHeight() / totalNumberOfBulbs;
    bulbs.clear();
    for (auto i = 0; i < totalNumberOfBulbs; i++)
    {
        auto bulb = std::make_unique<Bulb>(gradient.getColourAtPosition(static_cast<double>(i) / totalNumberOfBulbs));
        addAndMakeVisible(bulb.get());
        bulb->setBounds(bulbBounds.removeFromBottom(bulbHeight));
        bulbs.push_back(std::move(bulb));
    }
}

void Meter::VerticalDiscreteMeterAtomic::connectTo(Atomic<float>& targetVariable)
{
    observedEnvelope = &targetVariable;
}

void Meter::VerticalDiscreteMeterAtomic::timerCallback()
{
    repaint();
}

// === Horizontal Meter ===
Meter::HorizontalMeter::HorizontalMeter()
{
}

Meter::HorizontalMeter::~HorizontalMeter()
{

}

void Meter::HorizontalMeter::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    g.setColour(juce::Colours::white.withBrightness(0.4f));
    g.fillRoundedRectangle(bounds, 5.f);
    g.setColour(juce::Colours::white);
    //map level from -60.f / +6.f to 0 / widh
    const auto scaledX = juce::jmap(level, -60.f, +6.f, 0.f, static_cast<float>(getWidth()));
    g.fillRoundedRectangle(bounds.removeFromLeft(scaledX), 5.f);

}

void Meter::HorizontalMeter::resized()
{
}

void Meter::HorizontalMeter::setLevel(const float value) 
{ 
    level = value; 
}

// === Vertical Gradient Meter ===
Meter::VerticalGradientMeter::VerticalGradientMeter(std::function<float()>&& valueFunction)
    : valueSupplier(std::move(valueFunction))
{
    startTimerHz(24);
}

Meter::VerticalGradientMeter::~VerticalGradientMeter()
{

}

void Meter::VerticalGradientMeter::paint(juce::Graphics& g)
{
    const auto level = valueSupplier();

    auto bounds = getLocalBounds().toFloat();

    g.setColour(juce::Colours::black);
    g.fillRect(bounds);

    g.setGradientFill(gradient);
    const auto scaledY = juce::jmap(level, -60.f, 6.f, 0.f, static_cast<float>(getHeight()));
    g.fillRect(bounds.removeFromBottom(scaledY));
}

void Meter::VerticalGradientMeter::resized()
{
    const auto bounds = getLocalBounds().toFloat();
    gradient = juce::ColourGradient{
        juce::Colours::green,
        bounds.getBottomLeft(),
        juce::Colours::red,
        bounds.getTopLeft(),
        false
    };

    gradient.addColour(0.5, juce::Colours::yellow);
}

void Meter::VerticalGradientMeter::timerCallback()
{
    repaint();
}

// === Vertical Discrete Meter ===
Meter::VerticalDiscreteMeter::VerticalDiscreteMeter(std::function<float()>&& valueFunction) : valueSupplier(std::move(valueFunction))
{
    startTimerHz(24);
}

Meter::VerticalDiscreteMeter::~VerticalDiscreteMeter()
{
}

void Meter::VerticalDiscreteMeter::paint(juce::Graphics& g)
{
    const auto level = juce::jmap(valueSupplier(), -60.f, 6.f, 0.f, 1.f);

    for (auto i = 0; i < totalNumberOfBulbs; i++)
    {
        if (level >= static_cast<float>(i + 1) / totalNumberOfBulbs)
            bulbs[i]->setState(true);
        else
            bulbs[i]->setState(false);
    }
}

void Meter::VerticalDiscreteMeter::resized() 
{
    const auto bounds = getLocalBounds().toFloat();
    gradient = juce::ColourGradient{
        juce::Colours::green,
        bounds.getBottomLeft(),
        juce::Colours::red,
        bounds.getTopLeft(),
        false
    };

    gradient.addColour(0.5, juce::Colours::yellow);

    auto bulbBounds = getLocalBounds();
    const auto bulbHeight = bulbBounds.getHeight() / totalNumberOfBulbs;
    bulbs.clear();
    for (auto i = 0; i < totalNumberOfBulbs; i++)
    {
        auto bulb = std::make_unique<Bulb>(gradient.getColourAtPosition(static_cast<double>(i) / totalNumberOfBulbs));
        addAndMakeVisible(bulb.get());
        bulb->setBounds(bulbBounds.removeFromBottom(bulbHeight));
        bulbs.push_back(std::move(bulb));
    }
}

void Meter::VerticalDiscreteMeter::timerCallback()
{
    repaint();
}
