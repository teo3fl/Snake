#pragma once
#include "Scene.h"
class InfoScene : public Scene
{
public:
	InfoScene(sf::RenderWindow* window);

	void update(const float& dt) override;
	void render() override;

protected:
	void updateInput(const float& dt) override;

private:
	void initializeText();
};

