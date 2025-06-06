#pragma once

class IScene {
public:
	virtual ~IScene() = default;
	virtual void Init() const = 0;
	virtual void Enter() const = 0;
	virtual void Tick() const = 0;
	virtual void Exit() const = 0;
};