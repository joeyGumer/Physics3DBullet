#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
	
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	

	// TODO 2: Place the camera one unit up in Y and one unit to the right
	// experiment with different camera placements, then use LookAt()
	// to make it look at the center
	App->camera->Move({ 1, 1, 0 });
	App->camera->LookAt({ 0, 0, 0 });


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	vec3 i = { 1, 0, 0 };
	vec3 j = { 0, 1, 0 };
	vec3 k = { 0, 0, 1 };
	// TODO 1: Create a Plane primitive. This uses the plane formula
	// so you have to express the normal of the plane to create 
	// a plane centered around 0,0. Make that it draw the axis for reference
	Plane pi(0, 0, 1, 0);
	pi.axis = true;
	pi.Render();

	// TODO 6: Draw a sphere of 0.5f radius around the center
	// Draw somewhere else a cube and a cylinder in wireframe
	Sphere s(0.5f);

	Cube box(2, 1, 1);
	box.SetPos(5, 0, 0);
	box.color.Set(255, 0, 0);
	box.wire = true;

	Cylinder c(0.5f, 2.0f);
	c.SetPos(-5, 0, 0);
	c.color.Set(0, 0, 255);
	c.SetRotation(90, k);
	c.wire = true;

	s.Render();
	box.Render();
	c.Render();

	return UPDATE_CONTINUE;
}

