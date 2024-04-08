#include "stdafx.h"



Unit::Unit()
{
}

Unit::~Unit()
{
}

void Unit::Update()
{
	Actor::Update();
}

void Unit::Render(shared_ptr<Shader> pShader)
{
	Actor::Render(pShader);
}

void Unit::Move(Vector3 Target)
{
}

void Unit::WolrdUpdate()
{
}
