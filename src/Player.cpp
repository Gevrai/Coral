#include "Player.h"

Player::Player()
	: camera(Camera(Vec3D(0,0,150), Vec3D(0,0,1), Vec3D(0,1,0)))
	, velocity(Vec3D(0,0,0))
	, acceleration(Vec3D(0,0,0))
{}

Player::Player(Vec3D pos)
	: camera(Camera(pos, Vec3D(0,0,1), Vec3D(0,1,0)))
	, velocity(Vec3D(0,0,0))
	, acceleration(Vec3D(0,0,0))
{}

Player::~Player()
{}

Vec3D Player::getPos() const { return camera.getPos(); }
void Player::setPos(Vec3D pos) {camera.setPos(pos); }
Camera* Player::getCamera() { return &camera; }

void Player::startAction(PlayerAction action)
{
	switch (action) {
	case TURN_RIGHT: turning      =  1; break;
	case TURN_LEFT:  turning      = -1; break;
	case FOWARD:     accelerating =  1; break;
	case BACKWARD:   accelerating = -1; break;
	case UP:         ascending    =  1; break;
	case DOWN:       ascending    = -1; break;
	}
}

void Player::stopAction(PlayerAction action)
{
	switch (action) {
	case TURN_RIGHT:
	case TURN_LEFT:
		turning = 0; break;
	case FOWARD:
	case BACKWARD:
		accelerating = 0; break;
	case UP:
	case DOWN:
		ascending = 0; break;
	}
}

void Player::update(double dt){

	// ====== TURNING =======
	if (turning == 0) {
		turnRate *= std::pow(TURN_RATE_DAMPING,dt);
	}
	else {
		turnRate += (double) turning * TURN_RATE_ACCELERATION * dt;
		if (turnRate > MAX_TURN_RATE)
			turnRate = MAX_TURN_RATE;
		else if (turnRate < -MAX_TURN_RATE)
			turnRate = -MAX_TURN_RATE;
	}
	camera.rotateSideways(turnRate);

	// ====== ACCELERATION =======
	acceleration = camera.getFoward() * ((double) accelerating * ACCELERATION);
	acceleration.addInPlace(camera.getUp() * ((double) ascending * ACCELERATION));

	// ====== VELOCITY ======
	velocity = velocity * std::pow(VELOCITY_DAMPING, dt);
	if (accelerating !=0 || ascending != 0) {
		velocity.addInPlace(acceleration * dt);
		if (velocity.norm() > MAX_VELOCITY){
			velocity.normalize();
			velocity.multInPlace(MAX_VELOCITY);
		}
	}

	// ====== MOVEMENT ======
	Vec3D newposition = camera.getPos();
	newposition.addInPlace(velocity * dt);
	camera.setPos(newposition);
}
