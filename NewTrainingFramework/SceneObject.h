#pragma once
#include "Model.h"
#include "Texture.h"
#include "Shader.h"

class SceneObject
{
protected:
	GLuint	id;
	
public:
	Matrix		mvp, m;
	bool		depthTest;
	bool		wiredFormat = true;
	Vector3		position;
	Vector3		rotation;
	Vector3		scale;
	Model*		model;
	Shader*		shader;
	std::vector<Texture*>	textures;
	void		setModel(Model*);
	void		setShader(Shader*);
	void		addTextures(Texture*);
	void		SendCommonData();
	virtual void		Draw();
	virtual void		Update();
	SceneObject();
	SceneObject(Vector3, Vector3, Vector3, bool);
	~SceneObject();
};