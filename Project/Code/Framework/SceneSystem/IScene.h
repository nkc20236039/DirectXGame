#pragma once

class IScene {
public:
	virtual ~IScene() = default;
	virtual void init() const = 0;
	virtual void enter() const = 0;
	virtual void update() const = 0;
	virtual void exit() const = 0;
};