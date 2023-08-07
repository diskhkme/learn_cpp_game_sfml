#include "Bullet.h"


Bullet::Bullet(const sf::Vector2f& pos, const sf::Vector2f& direction,
	float size, const sf::Color& color, float speed)
	: position{ pos }, direction{ direction },
	size{ size }, color{ color }, speed{ speed }
{
	shape = sf::CircleShape{ size };
	shape.setFillColor(color);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(0.3f);
}

Bullet::Bullet()
	: Bullet{ sf::Vector2f{0,0}, sf::Vector2f{1.0f,0}, 0.3f, sf::Color{255,255,0,255}, 5.0f }
{}

void Bullet::Update(float dt)
{
	UpdatePosition(dt);
	shape.setPosition(position);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}


void Bullet::UpdatePosition(float dt)
{
	position += direction * speed * dt;
	shape.setPosition(position);
}