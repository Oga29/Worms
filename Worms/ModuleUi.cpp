#include "ModuleUi.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "ModuleFonts.h"
#include "SString.h"
#include "p2Point.h"
#include "p2List.h"
#include <stdio.h>
#include <cstdio>

ModuleUi::ModuleUi(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	



}

ModuleUi::~ModuleUi()
{
	
}

bool ModuleUi::Start() {

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	char lookUpTable2[] = { "abcdefghijklmnopqrstuvwxyz0123456789!.?   " };
	testFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable, 2);
	font = App->fonts->Load("Assets/Fonts/font.png", lookUpTable2, 7);
	rFont = App->fonts->Load("Assets/Fonts/rtype_font2.png", lookupTable, 2);
	bFont = App->fonts->Load("Assets/Fonts/rtype_font.png", lookupTable, 2);

	return true;
}

update_status ModuleUi::Update()
{
	if (App->physics->debug)
		Draw();
	SString weaponBlue("blue %s %i", App->scene_intro->weaponBlue.GetString(), App->scene_intro->ammoBlue);
	SString weaponRed("red %s %i", App->scene_intro->weaponRed.GetString(), App->scene_intro->ammoRed);

	SString time("time left %i", App->scene_intro->turnTimer / 60);
	App->fonts->BlitText(900, 0, testFont, time.GetString());
	App->fonts->BlitText(10, 725, rFont, weaponRed.GetString());
	App->fonts->BlitText(850, 725, bFont, weaponBlue.GetString());
	if (App->scene_intro->blueTurn) App->fonts->BlitText(500, 0, bFont, "blue turn");
	if (App->scene_intro->redTurn) App->fonts->BlitText(500, 0, rFont, "red turn");
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleUi::PostUpdate()
{
	return UPDATE_CONTINUE;
}






bool ModuleUi::CleanUp()
{
	App->fonts->UnLoad(testFont);
	App->fonts->UnLoad(bFont);
	App->fonts->UnLoad(rFont);
	App->fonts->UnLoad(font);

	return true;
}

void ModuleUi::Draw()
{
	SString fps;
	fps.Create("current fps %.2f deltatime %.2f ms expected fps %i deltatime %i ms", 1000 / App->dt, App->dt, 1000 / App->targetDT, App->targetDT);
	SString integrator;
	switch (App->physics->world.integrator)
	{
	case Integrator::VERLET:
		integrator.Create("current integrator verlet");
	break;
	case Integrator::IEULER:
		integrator.Create("current integrator implicit euler");
	break;
	case Integrator::SEULER:
		integrator.Create("current integrator symplectic euler");
	break;
	}

	SString wind;
	wind.Create("atmosphere density %.2f wind x %.2f wind y %.2f", App->physics->world.atmosphere.density, App->physics->world.atmosphere.wind.x, App->physics->world.atmosphere.wind.y);

	SString timeControll;
	switch (App->controll)
	{
	case FrameTimeControll::FIXEDDTTM :
		timeControll.Create("time controll fixed delta time");
		break;
	case FrameTimeControll::VARIABLEDT:
		timeControll.Create("time controll variable delta time");
		break;
	
	}

	App->fonts->BlitText(0, 10, testFont, fps.GetString());
	App->fonts->BlitText(0, 30, testFont, integrator.GetString());
	App->fonts->BlitText(0, 50, testFont, wind.GetString());
	App->fonts->BlitText(0, 70, testFont, timeControll.GetString());

}



