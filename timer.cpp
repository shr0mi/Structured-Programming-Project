#include "timer.h"
#include <sstream>
#include <iostream>

GameTimer::GameTimer() : totalTime(0.0f), timerText(font, "", 30)
{
    if (!font.openFromFile("assets/arial.ttf")) // Make sure the font exists
    {
        std::cerr << "Failed to load font!" << std::endl;
    }

    // Initialize timerText properties
    timerText.setFillColor(sf::Color::White);
    timerText.setOutlineColor(sf::Color::Black);
    timerText.setOutlineThickness(2);
    timerText.setPosition({10, 10});
}

void GameTimer::update(float dt, bool isPaused, bool isOver)
{
    if (!isPaused && !isOver) // Only update time if not paused or game over
    {
        totalTime += dt; // Increment total time by delta time
        updateText();    // Update the text with the new time
    }
}

void GameTimer::updateText()
{
    // Convert totalTime to minutes and seconds
    int totalSeconds = static_cast<int>(totalTime);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    // Format the time as MM:SS
    // Using stringstream for formatting
    // This ensures leading zeros for single-digit minutes and seconds
    std::stringstream ss;
    ss << "Time: ";
    ss << (minutes < 10 ? "0" : "") << minutes << ":";
    ss << (seconds < 10 ? "0" : "") << seconds;

    ss << "   |   Keys: " << keyCount; // <-- ADD KEYS
    timerText.setString(ss.str());
}

void GameTimer::draw(sf::RenderWindow &window)
{
    sf::View currentView = window.getView();
    window.setView(window.getDefaultView()); // Draw timer in screen space
    window.draw(timerText);
    window.setView(currentView); // Restore previous view
}

// Return Minutes
int GameTimer::get_minutes()
{
    int totalSeconds = static_cast<int>(totalTime);
    int minutes = totalSeconds / 60;
    return minutes;
}

// Return seconds
int GameTimer::get_seconds()
{
    int totalSeconds = static_cast<int>(totalTime);
    int seconds = totalSeconds % 60;
    return seconds;
}
void GameTimer::setKeyCount(int count) // <-- NEW
{
    keyCount = count;
    updateText(); // Update text immediately
}
