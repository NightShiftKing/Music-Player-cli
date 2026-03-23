// ============================================================
// File: UIElement.h
// Author: Michael Monreal
// Description: Abstract base class for all UI panels in the
//              TUI music player. Defines a common interface
//              with pure virtual methods that derived classes
//              must implement. Demonstrates: Abstract Classes.
// ============================================================
#pragma once
#include <string>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/event.hpp>

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
