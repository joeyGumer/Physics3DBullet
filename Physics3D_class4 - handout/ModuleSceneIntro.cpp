#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

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

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	// TODO 2: Chain few N spheres together to form a snake
	
	float d = 0.75f;
	vec3 pos;
	for (int i = 0; i < MAX_SNAKE; i++)
	{
		float r = (i + 1)*0.25;
		s_snake[i] = Sphere(r);
		//He de cambiar la posicio perque apareixen en el mateix punt i fa que es mogui al sortir
		
		float dis = s_snake[i].radius + s_snake[i - 1].radius + d;
		if (i > 0)
			pos = { 0, 10, pos.z + dis };
		else
			pos = { 0, 10, 0 };
		
		s_snake[i].SetPos(pos.x, pos.y, pos.z);
		s_snake[i].color = Red;

		pb_snake[i] = App->physics->AddBody(s_snake[i]);
		pb_snake[i]->SetPos(pos.x, pos.y, pos.z);
		
		//I DONT FUCKING KNOW HOW THE FUCK DOES THE LOACL COORDINATES WORK WITH BULLET, I PUT RADIUS, IT SHOULD
		//BE ON THE SURFACE OF EACH SFERE, BUT NO!, IT APPEARS MUCH FARTHER
		//SO, I'LL LET IT LIKE FUCKING THIS
		//IT ISN'T REKT BECAUSE THE CONSTRAINT DISTANCE IS ARBITRARI
		if (i > 0)
			App->physics->CreateP2PConstraint(
			pb_snake[i - 1], 
			pb_snake[i], 
			(0, 0, s_snake[i-1].radius/2 + d/2),
			(0, 0, -(s_snake[i].radius/2 + d/2)));
	}
	

	// TODO 4: Chain few N spheres together to form a a bike's sphere
	// Be sure to put the right axis

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	
	for(int i = 0; i < MAX_SNAKE; ++i)
	{
		pb_snake[i]->GetTransform(&(s_snake[i].transform));
		s_snake[i].Render();
	}
	/*
	for(int i = 0; i < MAX_SNAKE; ++i)
	{
		pb_snake2[i]->GetTransform(&(s_snake2[i].transform));
		s_snake2[i].Render();
	}
	*/
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

