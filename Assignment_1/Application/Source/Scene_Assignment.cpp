#include "Scene_Assignment.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Utility.h"
#include "Application.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"

Scene_Assignment::Scene_Assignment()
{
}

Scene_Assignment::~Scene_Assignment()
{
}

void Scene_Assignment::Init()
{


	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);

	// Set background color to dark blue
	glClearColor(0.4f, 0.0f, 0.0f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders
	//m_programID = LoadShaders( "Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader" );
	m_programID = LoadShaders("Shader//Shading.vertexshader",
		"Shader//Shading.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID,
		"MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID,
		"MV");

	


	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] =
		glGetUniformLocation(m_programID, "MV_inverse_transpose");




	m_parameters[U_MATERIAL_AMBIENT] =
		glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] =
		glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] =
		glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] =
		glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHT0_POSITION] =
		glGetUniformLocation(m_programID,
			"lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] =
		glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] =
		glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID,
		"lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID,
		"lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID,
		"lights[0].kQ");
	m_parameters[U_LIGHTENABLED] =
		glGetUniformLocation(m_programID, "lightEnabled");
	glUseProgram(m_programID);
	// 
	// 
	// 
	// 
	// 
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	// Use our shader
	glUseProgram(m_programID);

	light[0].position.Set(0, 170, 0);
	light[0].color.Set(0, 1, 1);
	light[0].power = 2;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;

	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1,
		&light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	
	//VARIABLES FOR RIGHT LEG
	rotate_right_leg_X = 0;
	rotate_right_leg_Y = 0;
	rotate_right_front_leg_X = 0;
	rotate_right_front_leg_Y = 0;

	//VARIABLES FOR LEFT
	rotate_left_leg_X = 0;
	rotate_left_leg_Y = 0;
	rotate_left_front_leg_X = 0;
	rotate_left_front_leg_Y = 0;


	//VARIABLES FOR KNIFE
	timer_knife = 0;
	rotate_knife_X = 0;
	rotate_knife_Y = 0;
	rotate_knife_Z = 0;
	move_knife_z = 0;
	move_knife_x = -16;

	//VARIABLES FOR HEAD
	rotateHead_X = 0;
	rotateHead_Z = 0;

	//VARIABLES FOR RIGHT ARM
	timer_right_arm = 0;
	rotate_right_arm_X = 0;
	rotate_right_arm_Z = 0;
	rotate_right_arm_Y = 0;

	//VARIABLES FOR LEFT ARM
	timer_left_arm = 0;
	rotate_left_arm_X = 0;
	rotate_left_arm_Y = 0;
	rotate_left_arm_Z = 0;

	//VARIABLES FOR LEG
	timer_leg = 0;
	timer_stand = 0;

	//MOVE FRONT
	walk_front = 0;

	//VARIABLES FOR JUMP
	jump = 0;
	time_jump = 0;

	

	//Initialize camera settings
	camera.Init(Vector3(200, 200, 200), Vector3(0, 0, 0), Vector3(0, 1, 0));

	// Init VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = nullptr;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	//
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("STAR", Color(1, 1, 1), 50, 50, 1.f);


	

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("STAR", Color(0.3, 0.3, 0.3), 0.5);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;


	//GenerateSphere(const std::string& meshName, Color color, unsigned numStacks, unsigned numSlices = 10, float radius = 1.f);
	meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("STAR", Color(1, 1, 1), 30, 30, 2);
	meshList[GEO_HEAD]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HEAD]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HEAD]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HEAD]->material.kShininess = 1.f;
	
	
	//static Mesh*GenerateCylinder(const std::string & meshName, Color color, unsigned numSlices = 10, unsigned height = 2, float radius = 1.f);
	meshList[GEO_LIMBS] = MeshBuilder::GenerateCylinder("STAR", Color(0, 0, 0), 30, 10, 5);
	meshList[GEO_LIMBS]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_LIMBS]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LIMBS]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_LIMBS]->material.kShininess = 1.f;
	
	//GenerateSphere(const std::string & meshName, Color color, unsigned numStacks, unsigned numSlices = 10, float radius = 1.f);
	meshList[GEO_PALM] = MeshBuilder::GenerateSphere("STAR", Color(1, 1, 1), 30, 10, 0);
	meshList[GEO_PALM]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_PALM]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_PALM]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_PALM]->material.kShininess = 1.f;


	// MeshBuilder::GenerateCube(const std::string &meshName, Color color, float length)
	meshList[GEO_FEET] = MeshBuilder::GenerateCube("STAR", Color(0.545098039215686, 0.270588235294117, 0.074509803921568), 1);
	meshList[GEO_FEET]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_FEET]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_FEET]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_FEET]->material.kShininess = 1.f;



	// MeshBuilder::GenerateCube(const std::string &meshName, Color color, float length)
	meshList[GEO_BLADE] = MeshBuilder::GenerateCube("STAR", Color(1, 1, 1), 1);
	meshList[GEO_BLADE]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BLADE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BLADE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_BLADE]->material.kShininess = 1.f;

	//static Mesh*GenerateCylinder(const std::string & meshName, Color color, unsigned numSlices = 10, unsigned height = 2, float radius = 1.f);
	meshList[GEO_HANDLE] = MeshBuilder::GenerateCylinder("STAR", Color(0.545098039215686, 0.270588235294117, 0.074509803921568), 20, 10, 2);
	meshList[GEO_HANDLE]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HANDLE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HANDLE]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_HANDLE]->material.kShininess = 1.f;


	//GenerateTorus(const std::string& meshName, Color color, unsigned numStacks, unsigned numSlices, float outerradius, float innerradius)
	meshList[GEO_EYES] = MeshBuilder::GenerateTorus("STAR", Color(0, 0, 0), 20, 20, 3, 2);
	meshList[GEO_EYES]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_EYES]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYES]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_EYES]->material.kShininess = 1.f;



	meshList[GEO_MOUTH] = MeshBuilder::GenerateHalfTorus("STAR", Color(0, 0, 0), 20, 20, 3, 2);
	meshList[GEO_MOUTH]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_MOUTH]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MOUTH]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_MOUTH]->material.kShininess = 1.f;
}

void  Scene_Assignment::Update(double dt)
{
	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	float LSPEED = 30.0f;
	//MOVE LIGHT TO NEGATIVE SIDE OF Z AXIS
	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	//MOVE LIGHT TO POSITIVE SIDE OF Z AXIS
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	//MOVE LIGHT TO NEGATIVE SIDE OF x AXIS
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	//MOVE LIGHT TO POSITIVE SIDE OF X AXIS
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	//GO DOWN
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	//GO UP
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);

	//RESET EVERYTHING
	if (Application::IsKeyPressed('R'))
	{

		//RESET THE LIGHT
		light[0].position.x = 0;
		light[0].position.y = 170;
		light[0].position.z = 0;

		//VARIABLES FOR RIGHT LEG
		rotate_right_leg_X = 0;
		rotate_right_leg_Y = 0;
		rotate_right_front_leg_X = 0;
		rotate_right_front_leg_Y = 0;

		//VARIABLES FOR LEFT
		rotate_left_leg_X = 0;
		rotate_left_leg_Y = 0;
		rotate_left_front_leg_X = 0;
		rotate_left_front_leg_Y = 0;


		//VARIABLES FOR KNIFE
		timer_knife = 0;
		rotate_knife_X = 0;
		rotate_knife_Y = 0;
		rotate_knife_Z = 0;
		move_knife_z = 0;
		move_knife_x = -16;

		//VARIABLES FOR HEAD
		rotateHead_X = 0;
		rotateHead_Z = 0;

		//VARIABLES FOR RIGHT ARM
		timer_right_arm = 0;
		rotate_right_arm_X = 0;
		rotate_right_arm_Z = 0;
		rotate_right_arm_Y = 0;

		//VARIABLES FOR LEFT ARM
		timer_left_arm = 0;
		rotate_left_arm_X = 0;
		rotate_left_arm_Y = 0;
		rotate_left_arm_Z = 0;

		//VARIABLES FOR LEG
		timer_leg = 0;
		timer_stand = 0;

		//MOVE FRONT
		walk_front = 0;

		//VARIABLES FOR JUMP
		jump = 0;
		time_jump = 0;
	}

	//MY SAMPLE ANIMATION
	if (Application::IsKeyPressed('F'))
	{
		timer_stand += (float)(10 * dt);

			if (timer_stand <= 100)
			{
				//TRANSFER KNIFE
				timer_left_arm += (float)(10 * dt);
				timer_right_arm += (float)(10 * dt);
				timer_knife += (float)(10 * dt);

				if (timer_right_arm >= 20)
				{
					timer_right_arm = 0;
				}
				if (timer_left_arm >= 20)
				{
					timer_left_arm = 0;
				}
				if (timer_knife >= 40)
				{
					timer_knife = 0;
				}

				rotate_right_arm_Z += (float)(30 * dt);
				rotate_left_arm_Z += (float)(30 * dt);

				if (timer_left_arm <= 10)
				{
					rotate_left_arm_X -= (float)(30 * dt);
				}
				else
				{
					rotate_left_arm_X += (float)(30 * dt);
				}

				if (timer_right_arm <= 10)
				{
					rotate_right_arm_X += (float)(30 * dt);
				}
				else
				{
					rotate_right_arm_X -= (float)(30 * dt);
				}

				
				if (timer_knife <= 20)
				{
					move_knife_x += (float)(20 * dt);

					rotateHead_X += (float)(10 * dt);
					rotateHead_Z += (float)(10 * dt);
				}
				else
				{
					move_knife_x -= (float)(20 * dt);

					rotateHead_X -= (float)(10 * dt);
					rotateHead_Z -= (float)(10 * dt);
				}


				//WALK
				walk_front += (float)(10 * dt);
				timer_leg += (float)(5 * dt);

				if (timer_leg >= 10)
				{
					timer_leg = 0;
				}

				if (timer_leg <= 5)
				{
					rotate_left_leg_X += (float)(40 * dt);
					rotate_right_leg_X -= (float)(40 * dt);


					rotate_left_leg_Y -= (float)(40 * dt);
					rotate_right_leg_Y -= (float)(40 * dt);
				}
				else
				{
					rotate_left_leg_X -= (float)(40 * dt);
					rotate_right_leg_X += (float)(40 * dt);

					rotate_left_leg_Y += (float)(40 * dt);
					rotate_right_leg_Y += (float)(40 * dt);
				}
			}
			else
			{


				if (rotateHead_X >= 20)
				{
					rotateHead_X -= (float)(rotateHead_X * dt);
				}
				if (rotateHead_Z >= 20)
				{
					rotateHead_Z -= (float)(rotateHead_Z * dt);
				}
				
				//stop rotate z for arms
				rotate_left_arm_Z = 0;
				rotate_right_arm_Z = 0;

				timer_left_arm += (float)(5 * dt);

				if(timer_left_arm <= 50)
				{
					rotate_left_arm_X += (float)(50 * dt);
					rotate_left_arm_Y += (float)(50 * dt);

					rotate_knife_X += (float)(50 * dt);
					rotate_knife_Y += (float)(50 * dt);
				}
				else
				{
					move_knife_z += (20 * dt);


					if (timer_left_arm >= 55 && timer_left_arm < 57)
					{
						rotate_left_arm_X -= (float)(50 * dt);
						rotate_left_arm_Y -= (float)(50 * dt);


						rotate_right_arm_X -= (float)(70 * dt);
						rotate_right_arm_Y += (float)(70 * dt);
					}
					
						time_jump += (float)(10 * dt);

						if (time_jump >= 5)
						{
							//mini
							jump -= (float)(30 * dt);

							rotate_left_leg_X += (float)(30 * dt);
							rotate_right_leg_X += (float)(30 * dt);

							rotate_left_leg_Y += (float)(30 * dt);
							rotate_right_leg_Y += (float)(30 * dt);

							rotate_left_front_leg_X -= (float)(90 * dt);
							rotate_right_front_leg_X -= (float)(90 * dt);


							rotate_left_front_leg_Y -= (float)(90 * dt);
							rotate_right_front_leg_Y -= (float)(90 * dt);

						}
						else
						{
							jump += (float)(30 * dt);

							rotate_left_leg_X -= (float)(30 * dt);
							rotate_right_leg_X -= (float)(30 * dt);


							rotate_left_leg_Y -= (float)(30 * dt);
							rotate_right_leg_Y -= (float)(30 * dt);



							rotate_left_front_leg_X += (float)(90 * dt);
							rotate_right_front_leg_X += (float)(90 * dt);


							rotate_left_front_leg_Y += (float)(90 * dt);
							rotate_right_front_leg_Y += (float)(90 * dt);
						}

						if (time_jump >= 10)
						{
							time_jump = 0;
						}
					



				}
			}
	}


	//ROTATE KNIFE WITH LEFT HAND
	if (Application::IsKeyPressed('X'))
	{
		//ROTATE HEAD TO CHARACTER'S LEFT
		if (rotateHead_X <= 20)
		{
			rotateHead_X += (float)(10 * dt);
		}
		if (rotateHead_Z <= 20)
		{
			rotateHead_Z += (float)(10 * dt);
		}

		timer_left_arm += (float)(10 * dt);
			timer_right_arm += (float)(10 * dt);

			//IF LEFT ARM TIMER IS NOT AT 20 YET, INDICTAING THE KNIFE IS NOT TRANSFERRED
			if (timer_left_arm >= 20)
			{
				//ROTRATE THE KNIFE
				rotate_right_arm_Z = 0;
				rotate_left_arm_Z = 0;

				rotate_left_arm_X += (float)(50 * dt);
				rotate_left_arm_Y += (float)(50 * dt);

				rotate_knife_X += (float)(50 * dt);
				rotate_knife_Y += (float)(50 * dt);

				if (timer_left_arm > 90)
				{
					//THROWS THE KNIFE
					move_knife_z += (20 * dt);
				}
			}
			else
			{
				//TRANSFER ONE KNIFE FROM THE OTHER
				move_knife_x += (float)(20 * dt);
				rotate_right_arm_Z += (float)(30 * dt);
				rotate_left_arm_Z += (float)(30 * dt);

				if (timer_left_arm <= 10)
				{
					rotate_left_arm_X -= (float)(30 * dt);
				}
				else
				{
					rotate_left_arm_X += (float)(30 * dt);
				}

				if (timer_right_arm <= 10)
				{
					rotate_right_arm_X += (float)(30 * dt);
				}
				else
				{
					rotate_right_arm_X -= (float)(30 * dt);
				}
			}

			

	}

	
	//MAKE A WALK CYCLE
	if (Application::IsKeyPressed('C'))
	{
		walk_front += (float)(10 * dt);
		timer_leg += (float)(5 * dt);

		if (timer_leg >= 10)
		{
			timer_leg = 0;
		}

		if (timer_leg <= 5)
		{
			rotate_left_leg_X += (float)(40 * dt);
			rotate_right_leg_X -= (float)(40 * dt);


			rotate_left_leg_Y -= (float)(40 * dt);
			rotate_right_leg_Y -= (float)(40 * dt);
		}
		else
		{
			rotate_left_leg_X -= (float)(40 * dt);
			rotate_right_leg_X += (float)(40 * dt);

			rotate_left_leg_Y += (float)(40 * dt);
			rotate_right_leg_Y += (float)(40 * dt);
		}
	}



	//JUMP CYCLE
	if (Application::IsKeyPressed('G'))
	{

		time_jump += (float)(10 * dt);

		timer_left_arm += (float)(5 * dt);

		//RAISE HANDS, IT WILL ONLY WORK WHEN TIMER_LEFT_ARM IS 0;
		if (timer_left_arm < 7)
		{
			rotate_left_arm_X -= (float)(50 * dt);
			rotate_left_arm_Y += (float)(50 * dt);

			rotate_knife_X -= (float)(50 * dt);
			rotate_knife_Y += (float)(50 * dt);


			rotate_right_arm_X -= (float)(70 * dt);
			rotate_right_arm_Y += (float)(70 * dt);
		}

		//DROP DOWN
		if (time_jump >= 5)
		{
			
			jump -= (float)(30 * dt);

			//ROTATE THE LEGS TO STAND
			rotate_left_leg_X += (float)(30 * dt);
			rotate_right_leg_X += (float)(30 * dt);

			rotate_left_leg_Y += (float)(30 * dt);
			rotate_right_leg_Y += (float)(30 * dt);

			rotate_left_front_leg_X -= (float)(90 * dt);
			rotate_right_front_leg_X -= (float)(90 * dt);


			rotate_left_front_leg_Y -= (float)(90 * dt);
			rotate_right_front_leg_Y -= (float)(90 * dt);

		}
		//JUMP AND MOVE UPWARDS
		else
		{
			//ROTATE THE LEGS TO JUMP
			jump += (float)(30 * dt);

			rotate_left_leg_X -= (float)(30 * dt);
			rotate_right_leg_X -= (float)(30 * dt);


			rotate_left_leg_Y -= (float)(30 * dt);
			rotate_right_leg_Y -= (float)(30 * dt);

			rotate_left_front_leg_X += (float)(90 * dt);
			rotate_right_front_leg_X += (float)(90 * dt);


			rotate_left_front_leg_Y += (float)(90 * dt);
			rotate_right_front_leg_Y += (float)(90 * dt);
		}

		//DROP AFTER JUMPING
		if (time_jump >= 10)
		{
			time_jump = 0;
		}
	}


	camera.Update(dt);
}


void  Scene_Assignment::RenderMesh(Mesh* mesh, bool enableLight)
{
	//light_on = enableLight;
	
		Mtx44 MVP, modelView, modelView_inverse_transpose;
		MVP = projectionStack.Top() * viewStack.Top() *
			modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE,
			&MVP.a[0]);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE,
			&modelView.a[0]);
		if (enableLight)
		{
			glUniform1i(m_parameters[U_LIGHTENABLED], 1);
			modelView_inverse_transpose =
				modelView.GetInverse().GetTranspose();
			glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1,
				GL_FALSE, &modelView_inverse_transpose.a[0]);
			//load material
			glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1,
				&mesh->material.kAmbient.r);
			glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1,
				&mesh->material.kDiffuse.r);
			glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1,
				&mesh->material.kSpecular.r);
			glUniform1f(m_parameters[U_MATERIAL_SHININESS],
				mesh->material.kShininess);
		}
		else
		{
			glUniform1i(m_parameters[U_LIGHTENABLED], 0);
		}
		mesh->Render();
	
}



void  Scene_Assignment::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Set view matrix using camera settings
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	modelStack.LoadIdentity();


	Position lightPosition_cameraspace = viewStack.Top() *
		light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1,
		&lightPosition_cameraspace.x);

	RenderMesh(meshList[GEO_AXES], false);


	//Render the lightball
	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y,
		light[0].position.z);
	modelStack.Scale(10, 10,
		10);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Rotate(-90, 1, 0, 0);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();


	//HEAD
	modelStack.PushMatrix();
	modelStack.Translate(0, 120 + jump, walk_front);

		//torso
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, -40, 0);
			modelStack.Scale(1, 5, 1);
			modelStack.Rotate(0, 0, 0, 1);
			RenderMesh(meshList[GEO_LIMBS], true);
			modelStack.PopMatrix();
		}

		//LEFT ARM
		{
			modelStack.PushMatrix();
			modelStack.Translate(15, -20, 15);
			modelStack.Rotate(rotate_left_arm_X, rotate_left_arm_Y , rotate_left_arm_Z, 1);
			

			//left for arm
			modelStack.PushMatrix();
			modelStack.Translate(5, 0, 25);
			modelStack.Rotate(90, 90, 0, 1);
			modelStack.Scale(1, 3, 1);
			RenderMesh(meshList[GEO_LIMBS], true);
			modelStack.PopMatrix();

			//left back arm
			modelStack.PushMatrix();
			modelStack.Rotate(90, -1.5, 0, 1);
			modelStack.Scale(1, 2, 1);
			RenderMesh(meshList[GEO_LIMBS], true);
			modelStack.PopMatrix();


			RenderMesh(meshList[GEO_PALM], true);
			modelStack.PopMatrix();
		}

		//RIGHT ARM
		{
			modelStack.PushMatrix();
			modelStack.Translate(-15, -20, 15);
			modelStack.Rotate(rotate_right_arm_X, rotate_right_arm_Y, rotate_right_arm_Z, 1);

			//right for arm
			modelStack.PushMatrix();
			modelStack.Translate(-5, 0, 25);
			modelStack.Rotate(90, 90, 0, 1);
			modelStack.Scale(1, 3, 1);
			RenderMesh(meshList[GEO_LIMBS], true);
			modelStack.PopMatrix();

			//right back arm
			modelStack.PushMatrix();
			modelStack.Rotate(90, 1.5, 0, 1);
			modelStack.Scale(1, 2, 1);
			RenderMesh(meshList[GEO_LIMBS], true);
			modelStack.PopMatrix();


			RenderMesh(meshList[GEO_PALM], true);
			modelStack.PopMatrix();
		}


		//ENTIRE RIGHT LEG
		{


			//right thigh joint
			modelStack.PushMatrix();
			modelStack.Translate(-4, -60, 0);
			modelStack.Rotate(-rotate_right_leg_X, rotate_right_leg_Y, 0, 1);
			

			//right thigh
			modelStack.PushMatrix();
			modelStack.Translate(0, -15, 0);
			modelStack.Scale(1, 2, 1);
			RenderMesh(meshList[GEO_LIMBS], true);
			modelStack.PopMatrix();


			//right lower leg joint
			modelStack.PushMatrix();
			modelStack.Translate(0, -5, 0);
			modelStack.Rotate(30 + rotate_right_front_leg_X, 30 + rotate_right_front_leg_Y, 0, 1);

				//right lower leg
				modelStack.PushMatrix();
				modelStack.Translate(0, -30, 10);
				modelStack.Scale(1, 3, 1);
				RenderMesh(meshList[GEO_LIMBS], true);
				modelStack.PopMatrix();

				//right feet
				modelStack.PushMatrix();
				modelStack.Translate(0, -45, 15);
				modelStack.Scale(10, 5, 20);
				RenderMesh(meshList[GEO_FEET], true);
				modelStack.PopMatrix();


			RenderMesh(meshList[GEO_PALM], true);
			modelStack.PopMatrix();




			RenderMesh(meshList[GEO_PALM], true);
			modelStack.PopMatrix();
		}


		//ENTIRE LEFT LEG
		{
			//left thigh joint
			modelStack.PushMatrix();
			modelStack.Translate(4, -60, 0);
			modelStack.Rotate(-rotate_left_leg_X, rotate_left_leg_Y, 0, 1);

				//left thigh
				modelStack.PushMatrix();
				modelStack.Translate(0, -15, 0);
				modelStack.Scale(1, 2, 1);
				RenderMesh(meshList[GEO_LIMBS], true);
				modelStack.PopMatrix();


				//left lower leg joint
				modelStack.PushMatrix();
				modelStack.Translate(0, -5, 0);
				modelStack.Rotate(30 + rotate_left_front_leg_X, 30 + rotate_left_front_leg_Y, 0, 1);

					//left lower leg
					modelStack.PushMatrix();
					modelStack.Translate(0, -30, 10);
					modelStack.Scale(1, 3, 1);
					//modelStack.Rotate(rotate_left_leg, 30, 0, 1);
					RenderMesh(meshList[GEO_LIMBS], true);
					modelStack.PopMatrix();
			
					//left feet
					modelStack.PushMatrix();
					modelStack.Translate(0, -45, 15);
					modelStack.Scale(10, 5, 20);
					RenderMesh(meshList[GEO_FEET], true);
					modelStack.PopMatrix();

				
				RenderMesh(meshList[GEO_PALM], true);
				modelStack.PopMatrix();

			

			
			RenderMesh(meshList[GEO_PALM], true);
			modelStack.PopMatrix();
		}

		//ENTIRE KNIFE
		{
			modelStack.PushMatrix();
			modelStack.Translate(move_knife_x, -20, 15 + (move_knife_z * 30));
			modelStack.Rotate(rotate_knife_X, rotate_knife_Y, 0, 1);

			//handle
			modelStack.PushMatrix();
			modelStack.Translate(0, 0, 35);

			//blade
			modelStack.PushMatrix();
			modelStack.Translate(0, 30, 15);
			modelStack.Scale(0.5, 40, 40);
			modelStack.Rotate(90, 0, 0, 1);
			RenderMesh(meshList[GEO_BLADE], true);
			modelStack.PopMatrix();

			modelStack.Scale(2, 2, 2);
			RenderMesh(meshList[GEO_HANDLE], true);
			modelStack.PopMatrix();


			RenderMesh(meshList[GEO_PALM], true);
			modelStack.PopMatrix();
		}

	modelStack.Rotate(-30 + rotateHead_X * 3, 0, 30 + rotateHead_Z * 3, 1);
		//modelStack.Rotate(rotateHead_X * 3, -rotateHead_X * 3, 0, 1);

		//ENTIRE EYES
		{
			modelStack.PushMatrix();
			modelStack.Translate(-5, 5, 15);
			modelStack.Scale(2, 2, 2);
			modelStack.Rotate(90, 0, 0, 1);
			RenderMesh(meshList[GEO_EYES], true);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(5, 5, 15);
			modelStack.Scale(2, 2, 2);
			modelStack.Rotate(90, 0, 0, 1);
			RenderMesh(meshList[GEO_EYES], true);
			modelStack.PopMatrix();
		}


		//ENTIRE MOUTH
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, -10, 13);
			modelStack.Rotate(-90, -180, 360, 1);
			modelStack.Scale(2, 2, 2);
			RenderMesh(meshList[GEO_MOUTH], true);
			modelStack.PopMatrix();
		}

	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_HEAD], true);
	modelStack.PopMatrix();
	
	
	
	
}

void  Scene_Assignment::Exit()
{
	// Cleanup VBO here
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
		{
			delete meshList[i];
		}
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}