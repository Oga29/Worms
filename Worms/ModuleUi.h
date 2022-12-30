#ifndef __UI_H__
#define __UI_H__

#include "Module.h"
#include "Globals.h"

class ModuleUi : public Module
{
public:
	ModuleUi(Application* app, bool start_enabled = true);
	virtual ~ModuleUi();

	bool Start();

	update_status Update();
	update_status PostUpdate();
	bool CleanUp();


	void Draw();


	

private:
	int testFont;
	int font;
	int bFont;
	int rFont;
};

#endif // !__UI_H__
