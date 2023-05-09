#pragma once

struct Inputs
{
	static const float CONTROLLER_DEAD_ZONE;

	Inputs();
	void reset();
	static float eliminateVibration(float analogInput);
	bool fireBullet;
	float moveFactor;
};