#include "Worm.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "Application.h"
#include "ModuleInput.h"
#include "Animation.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Grenade.h"
#include "ModuleAudio.h"
Worm::Worm(Vector2d position_, Team team_, Application* app_, Module* listener_) : Entity(EntityType::WORM, position_, team_, app_, listener_)
{
	name.Create("worm");
	pbody = new PhysObject();
	pbody->mass = 1000.0f;
	pbody->x = position.x;
	pbody->y = position.y;
	pbody->type = Type::DYNAMIC;
	pbody->shape = Shape::RECTANGLE;
	pbody->h = 30;
	pbody->w = 20;
	health = 100;
	pbody->entity = this;
	pbody->restitution = 0.1f;
	pbody->friction = 0.1f;
	pbody->SetLimit(Vector2d(300.0f, 300.0f));
	isSelected = false;

	shotGun* gun = new shotGun(app_, listener, this);
	guns.add(gun);
	AirStrike* air = new AirStrike(app_, listener, this);
	guns.add(air);
	Grenade* grenade = new Grenade(app_, listener, this);
	guns.add(grenade);
	
	currentAnim = &idleAnim;
	currentWeapon = guns.getFirst();
	int offset = 10;

	
	jumpAnim.PushBack({ 6, 15,  18, 30 });
	jumpAnim.loop = true;
	jumpAnim.mustFlip = false;
	jumpAnim.speed = 0.1f;


	
	idleAnim.PushBack({ 6, 15,  18, 30 });
	idleAnim.loop = true;
	idleAnim.mustFlip = false;
	idleAnim.speed = 0.1f;

	
	deadAnim.PushBack({ 369, 12,  18, 30 });
	deadAnim.PushBack({ 372, 70,  18, 30 });
	deadAnim.PushBack({ 367, 130,  18, 30 });
	deadAnim.PushBack({ 244, 136,  18, 30 });
	//deadAnim.PushBack({ 304, 14,  18, 30 });
	//deadAnim.PushBack({ 304, 14,  18, 30 });
	deadAnim.loop = false;
	deadAnim.mustFlip = true;
	deadAnim.speed = 0.07f;

	
	atackAnim.PushBack({ 197, 13,  20, 30 });
	atackAnim.loop = true;
	atackAnim.mustFlip = false;
	atackAnim.speed = 0.1f;
	atackAnim.pingpong = true;


	
	grenadeAnim.PushBack({ 202, 72,  18, 30 });
	grenadeAnim.loop = true;
	grenadeAnim.mustFlip = false;
	grenadeAnim.speed = 0.1f;
	grenadeAnim.pingpong = true;

	laser = false;

	
}

Worm::~Worm()
{
}



void Worm::Update(float dt)
{
	position.x = pbody->x;
	position.y = pbody->y;

	if (app_->scene_intro->turnStarted) canMove = true;
	else canMove = false;
	if (isSelected)
	{
		if (canMove)
		{
			if (isGrounded)
			{
				if (app_->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
				{
					pbody->AddForce(Vector2d(-10.0f, 0.0f));
					currentAnim->mustFlip = false;
					
				}
				if (app_->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
				{
					pbody->AddForce(Vector2d(+10.0f, 0.0f));
					currentAnim->mustFlip = true;
					
				}
				if (app_->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)
				{
					pbody->AddForce(Vector2d(0.0f, -100.0f));

					if (currentAnim == &idleAnim)
					{
						jumpAnim.mustFlip = currentAnim->mustFlip;
						currentAnim = &jumpAnim;
					}

					isGrounded = false;
				}
				if (app_->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
				{
					currentWeapon->data->Use(position);
					endTurn = true;
				}
			}
		
		}
		printf("\n pos: %f, %f, m: %i, %i", position.x, position.y, app_->input->GetMouseX(), app_->input->GetMouseY());
		if (currentWeapon->data->id == 0) //Shotgun
		{
			atackAnim.mustFlip = currentAnim->mustFlip;
			currentAnim = &atackAnim;
			laser = true;
		}
		else laser = false;

		if (currentWeapon->data->id == 1) //Airstrike
		{
			talkAnim.mustFlip = currentAnim->mustFlip;
			currentAnim = &talkAnim;
		}


		if (currentWeapon->data->id == 2) //Grenade
		{
			grenadeAnim.mustFlip = currentAnim->mustFlip;
			currentAnim = &grenadeAnim;
		}
		
		if (currentAnim == &jumpAnim && isGrounded == true) {
			idleAnim.mustFlip = currentAnim->mustFlip;
			currentAnim = &idleAnim;
		}

		if(app_->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
		{
			currentWeapon = currentWeapon->next;
			if (currentWeapon == nullptr)
				currentWeapon = guns.getFirst();
			
		}
		if (currentAnim == &talkAnim && app_->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
			currentAnim->Update();
		printf("\n %f", position.y);
	}
	else
	{
		currentAnim = &idleAnim;
		laser = false;
	}


	if (health <= 0)
	{
		
		if (currentAnim != &deadAnim)
		{
			deadAnim.mustFlip = !currentAnim->mustFlip;
			currentAnim = &deadAnim;
		}
		if (deadAnim.HasFinished())
		{
			setPendingToDelete = true;
		}
	}

	if (pbody->setPendingToDelete)
	{
		setPendingToDelete = true;
	}

	if (currentAnim!=&talkAnim)	currentAnim->Update();
}

void Worm::Draw(SDL_Texture* tex)
{
	app_->renderer->Blit(tex, position.x - pbody->w / 2, position.y - pbody->h / 2, &currentAnim->GetCurrentFrame(), 1.0f, 0, 0, 0, currentAnim->mustFlip);
}

void Worm::Select()
{
	isSelected = true;
}

void Worm::UnSelect()
{
	isSelected = false;
}
