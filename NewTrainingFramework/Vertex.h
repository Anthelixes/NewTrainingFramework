#pragma once
#include "../Utilities/Math.h"

struct Vertex 
{
	Vector3 pos;
	Vector3 col;
	Vector3 norm;
	Vector3 binorm;
	Vector3 tgt;
	Vector2 uv;
	Vector2	uv_blend;
public:
	Vertex()
	{

	}
	Vertex(const Vertex &a):pos(a.pos), col(a.col), norm(a.norm), binorm(a.binorm), tgt(a.tgt), uv(a.uv), uv_blend(a.uv_blend) {

	}
};