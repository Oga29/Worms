
#include "Entity.h"
#include "Animation.h"
#include "HandGun.h"
#include "p2List.h"
#include "AirStrike.h"
#include "PortalGun.h"

class Worm : public Entity
{
public:
	Worm(Vector2d, Team team_, Application* app_, Module* listener_);
	~Worm();

	void Update(float dt);
	void Draw(SDL_Texture* tex);


	void Select();
	void UnSelect();

private:

	bool canMove;

	Animation* currentAnim;
	bool laser;
	Animation idleAnim;
	Animation jumpAnim;
	Animation atackAnim;
	Animation deadAnim;
	Animation talkAnim;
	Animation portalAnim;
	Animation grenadeAnim;
	int walkSFX;
	int jumpSFX;
	int deadSFX;
	int changeSFX;
};

