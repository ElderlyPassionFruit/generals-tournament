#include "Game.h"

// Game

Game::Game(const std::string& configpath)
    : config_(configpath), map_(config_.GetMappath()), players_() {
}

std::string Game::Process() {
    return "";
}
