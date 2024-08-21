#include <Core/Game.hpp>

#include <Core/Properties.hpp>

namespace core
{
bool Game::performSharedEarlyStartup() {
    if (!Properties.load()) { return false; }

    // TODO - SETUP_TASK - setup resource loaders for custom resource types

    return true;
}

bool Game::performSharedStartupCompletion(bl::engine::Engine& engine) {
    // TODO - SETUP_TASK - register shared engine systems here

    return true;
}

void Game::startShutdown() {
    // noop. Engine still exists here
}

void Game::completeShutdown() {
    // noop. Called right before main() exits
}

} // namespace core
