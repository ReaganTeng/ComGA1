#ifndef A1_H
#define A1_H

#include "Scene.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class Scene_Assignment : public Scene
{

	MS modelStack, viewStack, projectionStack;

	enum GEOMETRY_TYPE
	{
		GEO_AXES,


		GEO_QUAD,
		GEO_LIGHTBALL,

		GEO_HEAD,
		GEO_LIMBS,
		GEO_FEET,
		GEO_PALM,
		GEO_EYES,
		GEO_MOUTH,


		GEO_BLADE,
		GEO_HANDLE,
		

		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_TOTAL
	};
public:
	Scene_Assignment();
	~Scene_Assignment();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	void RenderMesh(Mesh* mesh, bool enableLight);

private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	//VARIABLES FOR RIGHT LEG
	float rotate_right_leg_X;
	float rotate_right_leg_Y;
	float rotate_right_front_leg_X;
	float rotate_right_front_leg_Y;
	
	//VARIABLES FOR LEFT
	float rotate_left_leg_X;
	float rotate_left_leg_Y;
	float rotate_left_front_leg_X;
	float rotate_left_front_leg_Y;


	//VARIABLES FOR KNIFE
	float timer_knife;
	float rotate_knife_X;
	float rotate_knife_Y;
	float rotate_knife_Z;
	float move_knife_z;
	float move_knife_x;

	//VARIABLES FOR HEAD
	float rotateHead_X;
	float rotateHead_Z;

	//VARIABLES FOR RIGHT ARM
	float timer_right_arm;
	float rotate_right_arm_X;
	float rotate_right_arm_Z;
	float rotate_right_arm_Y;

	//VARIABLES FOR LEFT ARM
	float timer_left_arm;
	float rotate_left_arm_X;
	float rotate_left_arm_Y;
	float rotate_left_arm_Z;

	//VARIABLES FOR LEG
	float timer_leg;
	float timer_stand;

	//MOVE FRONT
	float walk_front;

	//VARIABLES FOR JUMP
	float jump;
	float time_jump;

	Camera2 camera;
	Light light[1];
};

#endif