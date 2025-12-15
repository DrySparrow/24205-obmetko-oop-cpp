#include "../include/universe.h"


Universe::Universe() : name("Universe"), grid(height, std::vector<bool>(width, false)), generation(0) {}

Universe::Universe(size_t w, size_t h, const std::string& n) 
    : name(n), width(w), height(h), grid(h, std::vector<bool>(w, false)), generation(0) {}

Universe::Universe(const Universe& other)
    : name(other.name), width(other.width), height(other.height), 
      grid(other.grid), rule(other.rule), generation(other.generation) {}
