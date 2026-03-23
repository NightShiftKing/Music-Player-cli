#pragma once
#include <string>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>

// ============================================================
// UIElement — Abstract base class for all UI panels.
// Demonstrates: Abstract Classes, Polymorphism
//
// Any class inheriting UIElement MUST implement:
//   - render()      : returns an ftxui::Element for display
//   - handleEvent() : processes keyboard/mouse input
//   - getName()     : returns the panel's display name
// ============================================================
class UIElement {
public:
    virtual ~UIElement() = default;

    // Pure virtual: defines how the panel draws itself
    virtual ftxui::Element render() = 0;

    // Pure virtual: defines how the panel responds to input
    virtual bool handleEvent(ftxui::Event event) = 0;

    // Pure virtual: returns a human-readable panel name
    virtual std::string getName() const = 0;
};
