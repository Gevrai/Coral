#include "Camera.h"

#define ACCELERATION 100.0

#define MAX_VELOCITY 300.0
#define VELOCITY_DAMPING 0.5

#define TURN_RATE_ACCELERATION 0.15
#define MAX_TURN_RATE 1.0
#define TURN_RATE_DAMPING 0.1

enum PlayerAction {
	TURN_RIGHT,
	TURN_LEFT,
	FOWARD,
	BACKWARD,
	UP,
	DOWN
};

class Player {
	Camera camera;

	Vec3D velocity;
	Vec3D acceleration;

	double turnRate;

	int turning = 0;
	int accelerating = 0;
	int ascending = 0;

 public:
	Player();
	Player(Vec3D pos);
	~Player();

	Vec3D getPos() const;
	Camera* getCamera();

	void setPos(Vec3D);

	void startAction(PlayerAction action);
	void stopAction(PlayerAction action);

	void update(double dt);

};
