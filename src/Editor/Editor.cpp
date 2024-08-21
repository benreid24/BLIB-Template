#include <Editor/Editor.hpp>

#include <Core/DemoEngineState.hpp>
#include <Core/Properties.hpp>
#include <Editor/ConstantsEditor.hpp>
#include <iostream>

namespace editor
{
namespace
{
// one instance should exist globally
Editor editor;
} // namespace

bool Editor::performEarlyStartup(int argc, char** argv) {
    if (!performSharedEarlyStartup()) { return false; }

#ifdef BLIB_DEBUG
    bl::logging::Config::rollLogs("logs", "verbose", 3);
    bl::logging::Config::configureOutput(std::cout, bl::logging::Config::Info);
    bl::logging::Config::addFileOutput("logs/verbose.log", bl::logging::Config::Trace);
#else
    bl::logging::Config::rollLogs("logs", "error", 3);
    bl::logging::Config::configureOutput(std::cout, bl::logging::Config::Warn);
    bl::logging::Config::addFileOutput("logs/error.log", bl::logging::Config::Warn);
#endif

    // if no previous value then use default editor specific value
    if (core::Properties.WindowWidth.get() == core::Constants::UnsetUintProperty) {
        core::Properties.WindowWidth.set(ConstantsEditor::WindowWidth);
        core::Properties.WindowHeight.set(ConstantsEditor::WindowHeight);
    }

    // TODO - SETUP_TASK - any other editor specific early setup steps

    return true;
}

bl::engine::Settings Editor::createStartupParameters() {
    return bl::engine::Settings()
        .withWindowParameters(
            bl::engine::Settings::WindowParameters()
                .withVideoMode(sf::VideoMode(
                    core::Properties.WindowWidth.get(), core::Properties.WindowHeight.get(), 32))
                .withStyle(sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize)
                .withTitle("BLIB Editor") // TODO - SETUP_TASK - set window title
                .withLetterBoxOnResize(true)
                .fromConfig())
        .fromConfig();
}

bool Editor::completeStartup(bl::engine::Engine& engine) {
    if (!performSharedStartupCompletion(engine)) { return false; }

    // TODO - SETUP_TASK - setup engine input system
    // TODO - SETUP_TASK - register editor specific systems

    return true;
}

bl::engine::State::Ptr Editor::createInitialEngineState() {
    // TODO - SETUP_TASK - create actual initial state
    return core::DemoEngineState::create();
}

} // namespace editor
