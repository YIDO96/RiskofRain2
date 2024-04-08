#include "stdafx.h"

PlayerBullet* PlayerBullet::Create(string name)
{
	PlayerBullet* temp = new PlayerBullet();
	temp->LoadFile("PlayerBullet.xml");
	temp->InitParticle();


	return temp;
}

PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Update()
{
	Attack();

	Bullet::Update();
}

void PlayerBullet::Render(shared_ptr<Shader> pShader)
{
	Bullet::Render();
}

void PlayerBullet::SetPos(Vector3 pos)
{
	Bullet::SetPos(pos);
}

void PlayerBullet::Fire(Vector3 dir, float power, Vector3 rotation)
{
	Bullet::Fire(dir, power, rotation);
}

void PlayerBullet::Attack()
{
	//�Ѿ˰� ���Ϳ��� �浹
	//for (auto& monster : GM->monsterPool)
	//{
	//	if (this->Intersect(monster->Find("RootNode")))
	//	{
	//		this->isCollsion = true;
	//
	//		int damage = GM->player->attack;
	//
	//		// TriTipDagger
	//		auto iter = GM->player->GetItemInven()->itemList.find("TritipDagger");
	//		if (iter != GM->player->GetItemInven()->itemList.end())
	//		{//�ִٸ� ���������� �߰�
	//			damage += GM->player->attack * iter->second;
	//		}
	//
	//		iter = GM->player->GetItemInven()->itemList.find("APRound");
	//		if (iter != GM->player->GetItemInven()->itemList.end())
	//		{//�ִٸ� �������� 20%(��ø +20%) �߰� ����
	//			if (monster->monsterType == MonsterType::BOSS)
	//			{
	//				damage += GM->player->attack * (0.2f * iter->second);
	//			}
	//		}
	//
	//
	//
	//		monster->hp -= damage;//�÷��̾� �Ǳ��
	//	}
	//}
}

Pop* PlayerBullet::InitParticle()
{
	bulletParticle = Pop::Create();
	bulletParticle->LoadFile("Particle_PlayerBullet.xml");
	bulletParticle->desc.gravity = 21;
	bulletParticle->velocityScalar = 27;
	bulletParticle->particleCount = 5;

	return bulletParticle;
}
