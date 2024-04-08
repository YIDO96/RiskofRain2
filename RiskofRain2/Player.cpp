#include "stdafx.h"

Player* Player::Create(string name)
{
	///11
	Player* temp = new Player();
	temp->LoadFile("Player.xml");
	temp->type = ObType::Actor;
	temp->playerState = PlayerState::IDLE;
	temp->attackState = PlayerAttackState::IDLE;
	temp->skillState = SkillState::NONE;
	temp->anim->ChangeAnimation(AnimationState::LOOP, 3, 0.1f);
	temp->Find("mdlCommandoDualies")->rotation.y = 180.0f * ToRadian;
	temp->Find("PlayerCam")->rotation.x = 0.0f;
	temp->rotation.y = 0;

	/** ����*/
	temp->moveSpeed = 7.0f;
	temp->lv = 1;
	temp->maxHp = 110; // ������� + 33
	temp->hp = 110;
	temp->exp = 0;
	temp->maxExp = 100;	// ������� + 10%
	temp->attack = 12; // ������� + 2.4
	temp->defend = 0;
	temp->gold = 15;
	temp->luna = 2;
	/** ����*/

	temp->isRight = false;
	temp->isRoll = false;
	temp->isLButton = false;
	temp->isRButton = false;
	temp->isRSkill = false;
	temp->slidingVector.direction = temp->GetForward();

	return temp;
}

Player::Player()
{
	itemInven = new Inventory();

}

Player::~Player()
{
}

void Player::Update()
{
	//ImGui::Text("M2CoolTime : %.2f", m2Timer);
	//ImGui::Text("isRButton : %d\n", (int)isRButton);
	//ImGui::Text("RCoolTime : %.2f", rTimer);
	//ImGui::Text("isRSkill : %d\n", (int)isRSkill);


	StatGUI();


	// ������ �ý���
	// ������ ���� maxHp , maxExp ����
	LevelUp();


	lastRot = Find("RootNode")->rotation.y;
	lastRot_root = rotation.y;
	dir = Vector3();

	if (INPUT->KeyPress('W'))
	{
		if (attackState == PlayerAttackState::ATTACK)
			dir += GetForward();
		else if (attackState == PlayerAttackState::IDLE)
			dir += Vector3(1, 0, 0);
	}
	else if (INPUT->KeyPress('S'))
	{
		if (attackState == PlayerAttackState::ATTACK)
			dir += -GetForward();
		else if (attackState == PlayerAttackState::IDLE)
			dir += Vector3(-1, 0, 0);
	}
	if (INPUT->KeyPress('A'))
	{
		if (attackState == PlayerAttackState::ATTACK)
			dir += -GetRight();
		else if (attackState == PlayerAttackState::IDLE)
			dir += Vector3(0, 0, -1);
	}
	else if (INPUT->KeyPress('D'))
	{
		if (attackState == PlayerAttackState::ATTACK)
			dir += GetRight();
		else if (attackState == PlayerAttackState::IDLE)
			dir += Vector3(0, 0, 1);
	}
	dir.Normalize();

	// ����
	MoveWorldPos(Vector3(0, -1, 0) * gravity * DELTA);
	gravity += 5.f * DELTA;

	if (INPUT->KeyDown(VK_SPACE))
	{
		isJump = true;
		anim->ChangeAnimation(AnimationState::ONCE_LAST, 15, 0.1f);
		gravity = -5.0f;
	}




	if (isRoll) //������ ������
	{
		fixDir = dir;
		isRoll = false;
	}

	if (INPUT->KeyPress('W') or INPUT->KeyPress('S') or
		INPUT->KeyPress('A') or INPUT->KeyPress('D'))
	{
		Move(dir);
	}

	FSM();




	Unit::Update();
}

void Player::Render(shared_ptr<Shader> pShader)
{
	Unit::Render();
}

void Player::FSM()
{
	// �÷��̾� �̵� FSM
	if (not isJump)
	{
		if (playerState == PlayerState::IDLE)
		{
			moveSpeed = 7.0f;
			// IDLE-> WALK Ű�� ������ ��
			if (INPUT->KeyPress('W') or INPUT->KeyPress('S') or
				INPUT->KeyPress('A') or INPUT->KeyPress('D'))
			{
				playerState = PlayerState::WALK;
				AinmChange(playerState);
			}
		}
		else if (playerState == PlayerState::WALK)
		{
			moveSpeed = 7.0f;

			if (attackState == PlayerAttackState::ATTACK)
			{
				// Ű�� �������� �ִϸ��̼� ��ȯ
				if (INPUT->KeyDown('W'))
					anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
				if (INPUT->KeyDown('S'))
					anim->ChangeAnimation(AnimationState::LOOP, 2, 0.1f);
				if (INPUT->KeyDown('A'))
					anim->ChangeAnimation(AnimationState::LOOP, 4, 0.1f);
				if (INPUT->KeyDown('D'))
					anim->ChangeAnimation(AnimationState::LOOP, 5, 0.1f);
			}

			// WALK -> IDLE Ű�� �ƹ��͵� ������ �ʾ�����
			if (not(INPUT->KeyPress('W') or INPUT->KeyPress('S') or
				INPUT->KeyPress('A') or INPUT->KeyPress('D')))
			{
				playerState = PlayerState::IDLE;
				AinmChange(playerState);
			}

			// WALK ->RUN // L��Ʈ���� ������ ��
			if (INPUT->KeyDown(VK_LCONTROL))
			{
				playerState = PlayerState::RUN;
				AinmChange(playerState);
			}

			// WALK ->ROLL // L����Ʈ�� ������ ��
			if (INPUT->KeyDown(VK_LSHIFT))
			{
				playerState = PlayerState::ROLL;
				isRoll = true;
				AinmChange(playerState);
			}
		}
		else if (playerState == PlayerState::RUN)
		{
			moveSpeed = 10.0f;

			// RUN -> WALK
			if (not INPUT->KeyPress('W') or INPUT->KeyPress('S') or INPUT->KeyPress(VK_LBUTTON))
			{
				playerState = PlayerState::WALK;
				AinmChange(playerState);
			}

			// RUN -> IDLE
			if (not(INPUT->KeyPress('W') or INPUT->KeyPress('S') or
				INPUT->KeyPress('A') or INPUT->KeyPress('D')))
			{
				playerState = PlayerState::IDLE;
				AinmChange(playerState);
			}
		}
		else if (playerState == PlayerState::ROLL)
		{
			moveSpeed = 12.0f;

			// ������ �ִϸ��̼��� ������ ROLL-> WALK or IDLE�� ���� ����
			if (anim->GetPlayTime() >= 0.99)
			{
				//ROLL -> WALK
				playerState = PlayerState::WALK;
				AinmChange(playerState);


				// ROLL -> IDLE
				if (not(INPUT->KeyPress('W') or INPUT->KeyPress('S') or
					INPUT->KeyPress('A') or INPUT->KeyPress('D')))
				{
					playerState = PlayerState::IDLE;
					AinmChange(playerState);
				}
			}
		}
	}

	// �÷��̾� �̵� FSM

	// �÷��̾� ����
	// �÷��̾� ����

	// ��Ŭ����ų ��Ÿ��
	if (isRButton)
	{
		if (TIMER->GetTick(m2Timer, 4.0f))
		{
			isRButton = false;
		}
	}

	// R��ų ��Ÿ��
	if (isRSkill)
	{
		if (TIMER->GetTick(rTimer, 10.0f))
		{
			isRSkill = false;
		}
	}

	// �÷��̾� ���� FSM
	if (attackState == PlayerAttackState::IDLE)
	{
		//IDLE -> ATTACK
		if (INPUT->KeyPress(VK_LBUTTON)
			or (isRButton == false and INPUT->KeyPress(VK_RBUTTON))
			or (isRSkill == false and INPUT->KeyPress('R')))
		{
			attackState = PlayerAttackState::ATTACK;
			//anim->ChangeAnimation(AnimationState::LOOP, 21, 0.1f);
			attackStopTime = 0.0f;

			// �÷��̾��� ���ݻ��°� �������� �ٲ�鼭 �÷��̾ �ȴ� �����϶�; ����Ű�� ������ ���� �ִϸ��̼� �������ֱ�
			if (playerState == PlayerState::WALK)
			{
				if (INPUT->KeyDown('W'))
					anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
				if (INPUT->KeyDown('S'))
					anim->ChangeAnimation(AnimationState::LOOP, 2, 0.1f);
				if (INPUT->KeyDown('A'))
					anim->ChangeAnimation(AnimationState::LOOP, 4, 0.1f);
				if (INPUT->KeyDown('D'))
					anim->ChangeAnimation(AnimationState::LOOP, 5, 0.1f);
			}
		}
	}
	else if (attackState == PlayerAttackState::ATTACK)
	{
		Ray mouseRay = Utility::MouseToRay((Camera*)Find("PlayerCam"));
		//ImGui::Text("MouseRay posx : %.2f", mouseRay.position.x);
		//ImGui::Text("MouseRay posy : %.2f", mouseRay.position.y);
		//ImGui::Text("MouseRay posz : %.2f", mouseRay.position.z);
		//
		//ImGui::Text("\n\nplayer posx : %.2f", GetWorldPos().x);
		//ImGui::Text("player posy : %.2f", GetWorldPos().y);
		//ImGui::Text("player posz : %.2f", GetWorldPos().z);
		/** M1 ��ų */
		{
			if (INPUT->KeyPress(VK_LBUTTON))
			{
				attackStopTime = 0.0f;
				skillState = SkillState::LBUTTON;
			}
			if (INPUT->KeyUp(VK_LBUTTON))
			{
				skillState = SkillState::NONE;
			}
			if (skillState == SkillState::LBUTTON)
			{
				if (TIMER->GetTick(LButtonFireTime, attackSpeed))
				{
					isRight = !isRight;

					PlayerBullet* temp = PlayerBullet::Create();
					Vector3 pos;

					if (isRight)
						pos = Find("gun.r.muzzle")->GetWorldPos();
					else pos = Find("gun.l.muzzle")->GetWorldPos();
					temp->SetPos(pos);

					Vector3 dir = pos - mouseRay.position; // �� ����
					dir.Normalize();

					//temp->rotation.x = -asinf(dir.y); // �� �������� �ٶ󺸴�

					temp->scale = Vector3(0.05, 0.05, 0.05);

					//GM->bulletPool.push_back(temp);
					//
					//for (auto it = GM->bulletPool.begin(); it != GM->bulletPool.end(); it++)
					//{
					//	if (not (*it)->isFire)
					//	{
					//		(*it)->Fire(mouseRay.direction, 200.0f, rotation);
					//		break;
					//	}
					//}
				}
			}
		}

		/** M2 ��ų */
		{
			if (isRButton)
			{
				if (skillState == SkillState::RBUTTON)
				{
					PlayerBullet* temp = PlayerBullet::Create();
					Vector3 pos;

					pos = Find("gun.r.muzzle")->GetWorldPos();

					temp->SetPos(pos);
					temp->scale = Vector3(0.4, 0.4, 0.4);
					//GM->bulletPool.push_back(temp);
					//
					//for (auto it = GM->bulletPool.begin(); it != GM->bulletPool.end(); it++)
					//{
					//	if (not (*it)->isFire)
					//	{
					//		(*it)->Fire(GetForward(), 200.0f, rotation);
					//		break;
					//	}
					//}
					skillState = SkillState::NONE;
				}
			}
			else
			{
				if (INPUT->KeyPress(VK_RBUTTON))
				{
					attackStopTime = 0.0f;
					skillState = SkillState::RBUTTON;
					isRButton = true;
				}
			}
		}

		/** R ��ų*/
		{
			if (isRSkill)
			{
				if (skillState == SkillState::R)
				{
					RSkillFireTime += DELTA;

					if (RSkillFireTime <= 1.0f)
					{
						if (TIMER->GetTick(RSkillFire, attackSpeed))
						{
							PlayerBullet* temp = PlayerBullet::Create();
							Vector3 pos;

							pos = Find("gun.r.muzzle")->GetWorldPos();

							temp->SetPos(pos);
							temp->scale = Vector3(0.05, 0.05, 0.05);
							//GM->bulletPool.push_back(temp);
							//
							//for (auto it = GM->bulletPool.begin(); it != GM->bulletPool.end(); it++)
							//{
							//	if (not (*it)->isFire)
							//	{
							//		(*it)->Fire(GetForward(), 200.0f, rotation);
							//		break;
							//	}
							//}
						}
					}
					else // RSkillFireTime�� 1.0f�� �Ѿ��
					{
						skillState = SkillState::NONE;
					}
				}
			}
			else
			{
				if (INPUT->KeyPress('R'))
				{
					attackStopTime = 0.0f;
					skillState = SkillState::R;
					isRSkill = true;
				}
			}
		}

		// ATTACK -> IDLE
		// ���������ʰ� 4�ʰ� �����鼭 ���ݻ��´� IDLE�� �ٲ��, �÷��̾��� �ִϸ��̼ǵ� ����
		if (TIMER->GetTick(attackStopTime, 4.0f))
		{
			attackState = PlayerAttackState::IDLE;
			skillState = SkillState::NONE;


			if (playerState == PlayerState::WALK)
				anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
		}
	}
	// �÷��̾� ���� FSM
}

void Player::AinmChange(PlayerState state)
{
	if (state == PlayerState::IDLE)
	{
		anim->ChangeAnimation(AnimationState::LOOP, 3, 0.1f);
	}
	else if (state == PlayerState::WALK)
	{
		if (attackState == PlayerAttackState::IDLE)
		{
			anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
		}
		else if (attackState == PlayerAttackState::ATTACK)
		{
			if (INPUT->KeyPress('W'))
				anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
			if (INPUT->KeyPress('S'))
				anim->ChangeAnimation(AnimationState::LOOP, 2, 0.1f);
			if (INPUT->KeyPress('A'))
				anim->ChangeAnimation(AnimationState::LOOP, 4, 0.1f);
			if (INPUT->KeyPress('D'))
				anim->ChangeAnimation(AnimationState::LOOP, 5, 0.1f);
		}
	}
	else if (state == PlayerState::RUN)
	{
		anim->ChangeAnimation(AnimationState::LOOP, 7, 0.1f);
	}
	else if (state == PlayerState::ROLL)
	{
		if (attackState == PlayerAttackState::IDLE)
		{
			anim->ChangeAnimation(AnimationState::ONCE_LAST, 11, 0.1f);
		}
		else if (attackState == PlayerAttackState::ATTACK)
		{
			if (INPUT->KeyPress('W'))
				anim->ChangeAnimation(AnimationState::ONCE_LAST, 11, 0.1f);
			if (INPUT->KeyPress('S'))
				anim->ChangeAnimation(AnimationState::ONCE_LAST, 12, 0.1f);
			if (INPUT->KeyPress('A'))
				anim->ChangeAnimation(AnimationState::ONCE_LAST, 9, 0.1f);
			if (INPUT->KeyPress('D'))
				anim->ChangeAnimation(AnimationState::ONCE_LAST, 10, 0.1f);
		}
	}
}

void Player::Move(Vector3 Target)
{
	if (attackState == PlayerAttackState::IDLE)
	{
		Vector3 Dir;

		MoveWorldPos(Find("RootNode")->GetForward() * moveSpeed * DELTA);

		if (playerState == PlayerState::IDLE)
			Find("RootNode")->rotation.y = lastRot;

		else if (playerState != PlayerState::ROLL and playerState != PlayerState::IDLE)
			Find("RootNode")->rotation.y = atan2f(Target.z, Target.x);
	}
	else if (attackState == PlayerAttackState::ATTACK)
	{
		Vector3 Dir;
		if (playerState != PlayerState::ROLL)
		{
			Dir = Target;
		}
		else
		{
			Dir = fixDir;
		}

		MoveWorldPos(Dir * moveSpeed * DELTA);
		Find("RootNode")->rotation.y = 0;
	}
}

void Player::Jump()
{
	gravityDir = -GetUp();
	gravity += 1.0f * DELTA;

	MoveWorldPos(gravityDir * gravity);
}

void Player::LevelUp()
{ // ui : leftBottom;
	if (exp >= maxExp)
	{
		//exp = 0;
		//GM->ui->leftBottom->Find("LeftBottom_Exp")->scale.x = 0;
		//lv++;
		//maxHp = maxHp + (33 * (lv - 1));
		//hp = maxHp;	// �������� �ִ�ä���� 10%ȸ��
		//maxExp = maxExp * (1 + 0.1f * (lv - 1));
		//attack = attack + 2.4f;
	}
}

void Player::DecreaseHP()
{
	//float scale = GM->ui->leftBottom->Find("LeftBottom_PlayerHpBar")->scale.x * (float)hp / (float)maxHp;
	//GM->ui->leftBottom->Find("LeftBottom_PlayerHp")->scale.x = scale;
}

void Player::WolrdUpdate()
{
	GameObject::Update();
}

void Player::PlayerRenderHierarchy()
{
	this->RenderHierarchy();

}

void Player::MoveBack(Actor* col)
{
	Vector3 slidingDir = col->GetWorldPos() - GM->player->GetWorldPos();
	slidingDir.y = 0;
	slidingDir.Normalize();
	Vector3 normal = col->collider->GetNormalVector(slidingDir);
	moveDir = slidingDir - normal * (slidingDir.Dot(normal));
	moveDir.Normalize();
	moveDir = -moveDir;
	GM->player->MoveWorldPos(moveDir * moveSpeed * DELTA);
}

void Player::StatGUI()
{
	ImGui::Begin("Stat");
	ImGui::Text("\tPlayer Stat\t\t");
	ImGui::Text("player Gold\t : %d", gold);
	ImGui::Text("player Luna\t : %d", luna);
	ImGui::Text("player Lv\t : %d\t\t", lv);
	ImGui::Text("player Hp\t : %d", (int)hp);
	ImGui::Text("player MaxHp\t : %d\t\t", (int)maxHp);
	ImGui::Text("player attack\t : %.2f", attack);
	ImGui::Text("player attackSpeed : %.2f", attackSpeed);
	ImGui::Text("player defend\t : %d", defend);
	ImGui::Text("player moveSpeed : %.2f", moveSpeed);
	ImGui::Text("player moveSpeed : %.2f", moveSpeed);
	ImGui::End();
}

void Player::SetPos(Vector3 pos)
{
	SetWorldPos(pos);
}
