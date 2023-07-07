#pragma once

#include <SFML/Graphics.hpp>

float GetLength(sf::Vector2f vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f GetNormalizedVector(sf::Vector2f vec)
{
	return vec / GetLength(vec);
}
