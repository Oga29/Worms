#include "Worm.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "Application.h"
#include "ModuleInput.h"
#include "Animation.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Granade.h"
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

	HandGun* gun = new HandGun(app_, listener, this);
	guns.add(gun);
	AirStrike* air = new AirStrike(app_, listener, this);
	guns.add(air);
	PortalGun* pgun = new PortalGun(app_, listener, this);
	guns.add(pgun);
	Granade* granade = new Granade(app_, listener, this);
	guns.add(granade);
	// SETING ANIMATIONS
	currentAnim = &idleAnim;
	currentWeapon = guns.getFirst();
	int offset = 10;

	for (int i = 0; i < 36; i++)
		jumpAnim.PushBack({ 108 + offset - i / 5,i * 60 + offset,54 - (3*offset),64 - offset });
	jumpAnim.loop = true;
	jumpAnim.mustFlip = false;
	jumpAnim.speed = 0.1f;


	for (int i = 0; i < 36; i++)
		idleAnim.PushBack({ 3 * 54 + offset,i * 60 + offset,54 - (offset*3),64 - offset });
	idleAnim.loop = true;
	idleAnim.mustFlip = false;
	idleAnim.speed = 0.1f;

	for (int i = 0; i < 11; i++)
		deadAnim.PushBack({ 15 * 54, i * 60 + offset + 5,54 - (2*offset),64 - offset });
	deadAnim.loop = false;
	deadAnim.mustFlip = true;
	deadAnim.speed = 0.07f;

	for (int i = 20 ; i < 23; i++)
		atackAnim.PushBack({ 9 * 54 + (offset * 3),i * 60 + offset,54 - (3*offset+2),64 - offset });
	atackAnim.loop = true;
	atackAnim.mustFlip = false;
	atackAnim.speed = 0.1f;
	atackAnim.pingpong = true;

	for (int i = 0; i < 5; i++)
		talkAnim.PushBack({ 5 * 54 + offset,(5 + i) * 60+offset,54 - offset*2,64 - offset });
	talkAnim.loop = false;
	talkAnim.mustFlip = false;
	talkAnim.speed = 0.07f;
	talkAnim.pingpong = true;

	for (int i = 20; i < 23; i++)
		portalAnim.PushBack({ 14 * 54 + (offset * 3),i * 60 + offset,54 - (3 * offset + 2),64 - offset });
	portalAnim.loop = true;
	portalAnim.mustFlip = false;
	portalAnim.speed = 0.1f;
	portalAnim.pingpong = true;

	for (int i = 20; i < 23; i++)
		grenadeAnim.PushBack({ 16 * 54 + (offset * 3),i * 60 + offset,54 - (3 * offset + 2),64 - offset });
	grenadeAnim.loop = true;
	grenadeAnim.mustFlip = false;
	grenadeAnim.speed = 0.1f;
	grenadeAnim.pingpong = true;

	laser = false;

	walkSFX = app_->audio->LoadFx("Assets/SFX/Walk-Expand.wav");
	deadSFX = app_->audio->LoadFx("Assets/SFX/COUGH5.WAV");
	jumpSFX = app_->audio->LoadFx("Assets/SFX/WORMSPRING.WAV");
	changeSFX = app_->audio->LoadFx("Assets/SFX/SHOTGUNRELOAD.WAV");
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
					if (app_->frame % 10 == 0 && isGrounded == true) app_->audio->PlayFx(walkSFX);
				}
				if (app_->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
				{
					pbody->AddForce(Vector2d(+10.0f, 0.0f));
					currentAnim->mustFlip = true;
					if (app_->frame % 10 == 0 && isGrounded == true) app_->audio->PlayFx(walkSFX);
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
		if (currentWeapon->data->id == 0) //Id 0 means handgun
		{
			atackAnim.mustFlip = currentAnim->mustFlip;
			currentAnim = &atackAnim;
			laser = true;
		}
		else laser = false;

		if (currentWeapon->data->id == 1) //Id 1 means airstrike
		{
			talkAnim.mustFlip = currentAnim->mustFlip;
			currentAnim = &talkAnim;
		}

		if (currentWeapon->data->id == 2) //Id 2 means portal
		{
			portalAnim.mustFlip = currentAnim->mustFlip;
			currentAnim = &portalAnim;
		}

		if (currentWeapon->data->id == 3) //Id 2 means grenade
		{
			grenadeAnim.mustFlip = currentAnim->mustFlip;
			currentAnim = &grenadeAnim;
		}
		
		if (currentAnim == &jumpAnim && isGrounded == true) {
			idleAnim.mustFlip = currentAnim->mustFlip;
			currentAnim = &idleAnim;
		}

		if(app_->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
		{
			currentWeapon = currentWeapon->next;
			if (currentWeapon == nullptr)
				currentWeapon = guns.getFirst();
			app_->audio->PlayFx(changeSFX);
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
		app_->audio->PlayFx(deadSFX);
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
