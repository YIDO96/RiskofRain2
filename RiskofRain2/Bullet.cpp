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

void Bullet::CollisionWithMap()//�ʰ� �Ѿ� �浹
{

	Vector3 hit;
	BulletRay.position = GetWorldPos();
	BulletRay.direction = GetForward();
	if (Utility::RayIntersectMap(BulletRay, GM->map, hit))//�ʰ� ���� ���� �̿��� ���� y�� ���
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

	//if (this->Intersect(GM->player->Find("RootNode"))) //�Ѿ˰� �÷��̾� �浹
	//{
	//	//�Ҹ� ��Ű��
	//	this->isCollsion = true;
	//	GM->player->hp -= 7;//�÷��̾� �Ǳ��
	//}

	//for (auto& monster : GM->monsterPool)//�Ѿ˰� ���Ϳ��� �浹
	//{
	//	if (this->Intersect(GM->player->Find("RootNode"))) //�Ѿ˰� �÷��̾� �浹
	//	{
	//		bulletParticle = InitParticle();
	//		bulletParticle->SetWorldPos(GM->player->Find("RootNode")->GetWorldPos());
	//		GM->particlePool.push_back(bulletParticle);
	//
	//		//�Ҹ� ��Ű��
	//		this->isCollsion = true;
	//		GM->player->hp -= monster->attack;//�÷��̾� �Ǳ��
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
	//			monster->hp -= GM->player->attack;//���� �����ÿ� Ű��
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
	//	if (this->Intersect(feature->feature->Find("RootNode"))) //�Ѿ˰� ���� �浹
	//	{
	//		bulletParticle = InitParticle();
	//		bulletParticle->SetWorldPos(feature->feature->Find("RootNode")->GetWorldPos());
	//		GM->particlePool.push_back(bulletParticle);
	//
	//		//�Ҹ� ��Ű��
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