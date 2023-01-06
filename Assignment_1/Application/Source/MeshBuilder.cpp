#include "MeshBuilder.h"
#include "MyMath.h"
#include <GL\glew.h>
#include <vector>
#include "Light.h"
#include "Material.h"
#include "Vertex.h"

Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	//x-axis
	v.pos.Set(-lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(lengthX, 0, 0);	v.color.Set(1, 0, 0);	vertex_buffer_data.push_back(v);
	//y-axis
	v.pos.Set(0, -lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, lengthY, 0);	v.color.Set(0, 1, 0);	vertex_buffer_data.push_back(v);
	//z-axis
	v.pos.Set(0, 0, -lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, lengthZ);	v.color.Set(0, 0, 1);	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}



Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(0.5f * length, 0.5f * length, 0.f);	v.color = color; v.normal.Set(0.f, 0.f, 1.f); vertex_buffer_data.push_back(v); //v0
	v.pos.Set(-0.5f * length, 0.5f * length, 0.f);	v.color = color; v.normal.Set(0.f, 0.f, 1.f); vertex_buffer_data.push_back(v); //v1
	v.pos.Set(-0.5f * length, -0.5f * length, 0.f);	v.color = color; v.normal.Set(0.f, 0.f, 1.f); vertex_buffer_data.push_back(v); //v2
	v.pos.Set(0.5f * length, -0.5f * length, 0.f);	v.color = color; v.normal.Set(0.f, 0.f, 1.f);	vertex_buffer_data.push_back(v); //v3
	

	//tri1
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	//tri2
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);

	Mesh* mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}


Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.color = color;	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color;	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color;	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color;	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color;	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.color = color;	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color;	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, -0.5f * length, 0.5f * length);	v.color = color;	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color;	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color;	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, -0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color;	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color;	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color;	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color;	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, -0.5f * length);	v.color = color;	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color;	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, 0.5f * length, 0.5f * length);		v.color = color;	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f * length, 0.5f * length, 0.5f * length);	v.color = color;	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f * length, -0.5f * length, 0.5f * length);	v.color = color;	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	for (unsigned i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}



Mesh* MeshBuilder::GenerateSphere(const std::string& meshName, Color color, unsigned numStacks = 10, unsigned numSlices, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerStack = 180.f / numStacks;
	float degreePerSlice = 360.f / numSlices;

	for (unsigned stack = 0; stack <= numStacks; ++stack)
	{
		float phi = -90.f + degreePerStack * stack;
		for (unsigned slice = 0; slice <= numSlices; ++slice)
		{
			float theta = degreePerSlice * slice;
			float x = radius * cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
			float y = radius * sin(Math::DegreeToRadian(phi));
			float z = radius * cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
			v.pos.Set(x, y, z);
			v.normal.Set(x, y, z);
			v.color = color;
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack <= numStacks; ++stack)
	{
		for (unsigned slice = 0; slice <= numSlices; ++slice)
		{
			index_buffer_data.push_back(stack * (numSlices + 1) + slice);
			index_buffer_data.push_back((stack + 1) * (numSlices + 1) + slice);
		}
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}



Mesh* MeshBuilder::GenerateCylinder(const std::string& meshName, Color color, unsigned numSlices , float height , float radius )
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float radianPerSlice = Math::TWO_PI / numSlices;

	unsigned offset = 0;

	//cylinder bottom
	offset = index_buffer_data.size();
	for (unsigned slice = 0; slice <= numSlices; ++slice)
	{

		//centre of circle
		v.pos.Set(0, -height * 0.5f, 0);
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

		//edge of slice
		v.pos.Set(radius * cosf(slice * radianPerSlice), -height * 0.5f, radius * sinf(slice * radianPerSlice));
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);


	}
	for (unsigned slice = 0; slice <= numSlices; ++slice)
	{
		index_buffer_data.push_back(offset + slice * 2 + 0);
		index_buffer_data.push_back(offset + slice * 2 + 1);
	}

	//cylinder side
	offset = index_buffer_data.size();
	for (unsigned slice = 0; slice <= numSlices; ++slice)
	{
		//edge of slice
		v.pos.Set(radius * cosf(slice * radianPerSlice), -height * 0.5f, radius * sinf(slice * radianPerSlice));
		v.color = color;
		v.normal.Set(cosf(slice * radianPerSlice), 0, sinf(slice * radianPerSlice));
		vertex_buffer_data.push_back(v);

		//centre of circle
		v.pos.Set(radius * cosf(slice * radianPerSlice), height * 0.5f, radius * sinf(slice * radianPerSlice));
		v.normal.Set(cosf(slice * radianPerSlice), 0, sinf(slice * radianPerSlice));
		v.color = color;
		vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice <= numSlices; ++slice)
	{
		index_buffer_data.push_back(offset + slice * 2 + 0);
		index_buffer_data.push_back(offset + slice * 2 + 1);
	}
	

	//cylinder top
	offset = index_buffer_data.size();
	for (unsigned slice = 0; slice <= numSlices; ++slice)
	{
		//edge of slice
		v.pos.Set(radius * cosf(slice * radianPerSlice), height * 0.5f, radius * sinf(slice * radianPerSlice));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);

		//centre of circle
		v.pos.Set(0, height * 0.5f, 0);
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}
	for (unsigned slice = 0; slice <= numSlices; ++slice)
	{
		index_buffer_data.push_back(offset + slice * 2 + 0);
		index_buffer_data.push_back(offset + slice * 2 + 1);
	}
	
	
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;

	
}

Mesh* MeshBuilder::GenerateTorus(const std::string& meshName, Color color, unsigned numStacks, unsigned numSlices, float outerradius, float innerradius)
{

	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreeperstack = 360.f / numStacks;
	float degreeperslice = 360.f / numSlices;

	float x1, z1;

	float x2, y2, z2;



	for (unsigned stack = 0; stack <= numStacks; stack++)
	{
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			z1 = outerradius * cosf(Math::DegreeToRadian(stack * degreeperstack));
			x1 = outerradius * sinf(Math::DegreeToRadian(stack * degreeperstack));

			z2 = (outerradius + innerradius * cosf(Math::DegreeToRadian(slice * degreeperslice))) * cosf(Math::DegreeToRadian(stack * degreeperstack));
			y2 = innerradius * sin(Math::DegreeToRadian(slice * degreeperslice));
			x2 = (outerradius + innerradius * cosf(Math::DegreeToRadian(slice * degreeperslice))) * sinf(Math::DegreeToRadian(stack * degreeperstack));

			v.pos.Set(x2, y2, z2);
			v.color = color;
			v.normal.Set(x2 - x1, y2, z2 - z1);
			v.normal.Normalize();
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStacks; stack++)
	{
		for (unsigned slice = 0; slice <= numSlices + 1; slice++)
		{
			index_buffer_data.push_back((numSlices + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlices + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}




Mesh* MeshBuilder::GenerateHalfTorus(const std::string& meshName, Color color, unsigned numStacks, unsigned numSlices, float outerradius, float innerradius)
{

	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreeperstack = 180.f / numStacks;
	float degreeperslice = 360.f / numSlices;

	float x1, z1;

	float x2, y2, z2;



	for (unsigned stack = 0; stack <= numStacks; stack++)
	{
		for (unsigned slice = 0; slice <= numSlices; slice++)
		{
			z1 = outerradius * cosf(Math::DegreeToRadian(stack * degreeperstack));
			x1 = outerradius * sinf(Math::DegreeToRadian(stack * degreeperstack));

			z2 = (outerradius + innerradius * cosf(Math::DegreeToRadian(slice * degreeperslice))) * cosf(Math::DegreeToRadian(stack * degreeperstack));
			y2 = innerradius * sin(Math::DegreeToRadian(slice * degreeperslice));
			x2 = (outerradius + innerradius * cosf(Math::DegreeToRadian(slice * degreeperslice))) * sinf(Math::DegreeToRadian(stack * degreeperstack));

			v.pos.Set(x2, y2, z2);
			v.color = color;
			v.normal.Set(x2 - x1, y2, z2 - z1);
			v.normal.Normalize();
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStacks; stack++)
	{
		for (unsigned slice = 0; slice <= numSlices + 1; slice++)
		{
			index_buffer_data.push_back((numSlices + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlices + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}
