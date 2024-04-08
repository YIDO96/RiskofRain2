#include "stdafx.h"

Bullet* Bullet::Create(string name)
{
	Bullet* temp = new Bullet();
	temp->type = ObType::Actor;
	temp->isFire = false;
	temp->isCollsion = false;
	temp->extinctionTime = 0.0f;

	return temp;
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::SetPos(Vector3 pos)
{
	SetWorldPos(pos);
}

void Bullet::CollisionWithMap()//맵과 총알 충돌
{

	Vector3 hit;
	BulletRay.position = GetWorldPos();
	BulletRay.direction = GetForward();
	if (Utility::RayIntersectMap(BulletRay, GM->map, hit))//맵과 몬스터 레이 이용해 몬스터 y값 잡기
	{
		if ((hit - GetWorldPos()).Length() < 1.0f)
		{
			bulletParticle = InitParticle();
			bulletParticle->SetWorldPos(GM->player->Find("RootNode")->GetWorldPos());
			GM->particlePool.push_back(bulletParticle);
			this->isCollsion = true;
		}
	}


}

Pop* Bullet::InitParticle()
{
	return nullptr;
}


void Bullet::Update()
{
	if (!isFire) return;
	Actor::Update();

	Vector3 velocity = fireDir * power;
	MoveWorldPos(velocity * DELTA);

	CollisionWithMap();


	if (TIMER->GetTick(extinctionTime, 10.0f))
	{
		this->isCollsion = true;
	}

	//if (this->Intersect(GM->player->Find("RootNode"))) //총알과 플레이어 충돌
	//{
	//	//소멸 시키고
	//	this->isCollsion = true;
	//	GM->player->hp -= 7;//플레이어 피깎기
	//}

	//for (auto& monster : GM->monsterPool)//총알과 몬스터와의 충돌
	//{
	//	if (this->Intersect(GM->player->Find("RootNode"))) //총알과 플레이어 충돌
	//	{
	//		bulletParticle = InitParticle();
	//		bulletParticle->SetWorldPos(GM->player->Find("RootNode")->GetWorldPos());
	//		GM->particlePool.push_back(bulletParticle);
	//
	//		//소멸 시키고
	//		this->isCollsion = true;
	//		GM->player->hp -= monster->attack;//플레이어 피깎기
	//		GM->player->DecreaseHP();
	//	}
	//
	//	if (this->Intersect(monster->Find("RootNode")))
	//	{
	//		if (!(monster->monsterType == MonsterType::BOSS))
	//		{
	//			bulletParticle = InitParticle();
	//			bulletParticle->SetWorldPos(monster->GetWorldPos());
	//			GM->particlePool.push_back(bulletParticle);
	//			this->isCollsion = true;
	//			monster->hp -= GM->player->attack;//몬스터 수정시에 키기
	//		}
	//		else
	//		{
	//			Vector3 collisionPos = this->GetWorldPos();
	//			bulletParticle = InitParticle();
	//			bulletParticle->SetWorldPos(collisionPos);
	//			GM->particlePool.push_back(bulletParticle);
	//			this->isCollsion = true;
	//			monster->hp -= GM->player->attack;
	//		}
	//	}
	//}

	//for (auto& feature : GM->featurePool)
	//{
	//	if (this->Intersect(feature->feature->Find("RootNode"))) //총알과 지물 충돌
	//	{
	//		bulletParticle = InitParticle();
	//		bulletParticle->SetWorldPos(feature->feature->Find("RootNode")->GetWorldPos());
	//		GM->particlePool.push_back(bulletParticle);
	//
	//		//소멸 시키고
	//		this->isCollsion = true;
	//
	//	}
	//}



}

void Bullet::Render(shared_ptr<Shader> pShader)
{
	if (!isFire) return;


	Actor::Render();

}

void Bullet::Fire(Vector3 dir, float power, Vector3 rotation)
{
	isFire = true;
	this->power = power;
	this->fireDir = dir;
	this->rotation.x = HALFPI;
	this->rotation.y = rotation.y;
}

void Bullet::PlayerToBossAttack(Boss* boss)
{
}