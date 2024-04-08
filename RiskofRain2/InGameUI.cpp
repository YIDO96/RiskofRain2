#include "stdafx.h"
#include <sstream>
#include <iomanip>

InGameUI* InGameUI::Create(string name)
{
	InGameUI* temp = new InGameUI();

	return temp;
}

InGameUI::InGameUI()
{
	upper = UI::Create();
	upper->LoadFile("UI_InGame_Upper.xml");
	leftBottom = UI::Create();
	leftBottom->LoadFile("UI_InGame_LeftBottom.xml");
	rightBottom = UI::Create();
	rightBottom->LoadFile("UI_InGame_RightBottom.xml");

	bossHPbar = UI::Create("bossHPbar");
	bossHPbar->LoadFile("UI_InGame_BossHpBar.xml");
	bossHPbar->visible = false;
}

InGameUI::~InGameUI()
{
}

void InGameUI::Init()
{
	leftBottom->Find("LeftBottom_Exp")->scale.x = 0;
}

void InGameUI::Update()
{
	Vector3 mousePos = Utility::MouseToNDC();

	//// ������ �ý���
	//if (playerexp >= playerMaxexp)
	//{
	//	playerexp = 0;
	//	leftBottom->Find("LeftBottom_Exp")->scale.x = 0;
	//	playerlv++;
	//	playermaxhp = playermaxhp + (33 * (playerlv - 1));
	//	playerhp = playermaxhp;	// �������� �ִ�ä���� 10%ȸ��
	//	playerMaxexp = playerMaxexp * (1 + 0.1f * (playerlv - 1));
	//	playerattack = playerattack + 2.4f;
	//}
	//
	//
	//// ü�� ���̴�
	//if (INPUT->KeyDown('K')) // ü���� ���϶����� hpUI�� �����ϰ� �����ϱ� 
	//{
	//	playerhp -= 13; // 13 : ������ attack��
	//
	//	float scale = leftBottom->Find("LeftBottom_PlayerHpBar")->scale.x * (float)playerhp / (float)playermaxhp;
	//	leftBottom->Find("LeftBottom_PlayerHp")->scale.x = scale;
	//}
	//
	//// exp
	//if (INPUT->KeyDown('J')) // ���͸� ����� ��� ����ġ�� expUI�����ϰ� �����ϱ�
	//{
	//	playerexp += 11; // 11 : ���Ͱ� ������ ���� Exp��
	//
	//	float scale = leftBottom->Find("LeftBottom_ExpBarscale")->scale.x * playerexp / (float)playerMaxexp;
	//	leftBottom->Find("LeftBottom_Exp")->scale.x = scale;
	//	isGoalClear = !isGoalClear;
	//}

	if (isGoalClear)
	{
		upper->Find("UpperRightBottom_GoalClear")->visible = true;
		upper->Find("UpperRightBottom_GoalList")->visible = false;
	}
	else
	{
		upper->Find("UpperRightBottom_GoalClear")->visible = false;
		upper->Find("UpperRightBottom_GoalList")->visible = true;
	}


	upper->Update();
	leftBottom->Update();
	rightBottom->Update();
	bossHPbar->Update();
}

void InGameUI::Render()
{
	upper->Render();
	leftBottom->Render();
	rightBottom->Render();
	bossHPbar->Render();

	RenderFont();
	PlayerInvenFont();
}

void InGameUI::RenderH()
{
	//upper->RenderHierarchy();
	leftBottom->RenderHierarchy();
	//rightBottom->RenderHierarchy();
	bossHPbar->RenderHierarchy();
}

void InGameUI::ResizeScreen()
{
}

void InGameUI::PlayerInvenFont()
{
	for (int i = 0; i < 9; i++)
	{
		string s_slot = "slot" + to_string(i + 1);
		Vector3 itemSlotPos = upper->Find(s_slot)->GetWorldPos();

		string fileName = upper->Find(s_slot)->material->diffuseMap->file;
		size_t index = fileName.find_last_of('.');

		string itemName = fileName.substr(0, index);
		auto iter = GM->player->GetItemInven()->itemList.find(itemName);
		if (iter != GM->player->GetItemInven()->itemList.end())
		{
			itemSlot[i] = to_wstring(iter->second);
		}
		else itemSlot[i] = L" ";
		rect.left = (itemSlotPos.x + 1) * App.GetHalfWidth() + 10;
		rect.top = (1 - itemSlotPos.y) * App.GetHalfHeight() + 10;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();

		DWRITE->RenderText(itemSlot[i], rect, 15, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1));
	}
}

void InGameUI::RenderFont()
{
	// LeftBottom Font (Player Lv, Hp..)
	{
		Vector3 playerHpBarPos = leftBottom->Find("LeftBottom_PlayerHpFont")->GetWorldPos(); // �÷��̾�ü�¹� Pos
		Vector3 playerExpBarPos = leftBottom->Find("LeftBottom_LvFont")->GetWorldPos();

		wlv = L"Lv : ";
		rect.left = (playerExpBarPos.x + 1) * App.GetHalfWidth() - 20;
		rect.top = (1 - playerExpBarPos.y) * App.GetHalfHeight() - 10;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wlv, rect, 15, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);


		wplayerLv = to_wstring(GM->player->GetLv());
		rect.left = (playerExpBarPos.x + 1) * App.GetHalfWidth() + 10;
		rect.top = (1 - playerExpBarPos.y) * App.GetHalfHeight() - 10;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wplayerLv, rect, 15, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

		whpSlash = L" / ";
		rect.left = (playerHpBarPos.x + 1) * App.GetHalfWidth() - 10;
		rect.top = (1 - playerHpBarPos.y) * App.GetHalfHeight() - 15;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(whpSlash, rect, 20, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);


		wplayerHp = to_wstring((int)GM->player->hp);
		rect.left = (playerHpBarPos.x + 1) * App.GetHalfWidth() - 45;
		rect.top = (1 - playerHpBarPos.y) * App.GetHalfHeight() - 15;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wplayerHp, rect, 20, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

		wplayerMaxHp = to_wstring((int)GM->player->GetMaxHp());
		rect.left = (playerHpBarPos.x + 1) * App.GetHalfWidth() + 10;
		rect.top = (1 - playerHpBarPos.y) * App.GetHalfHeight() - 15;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wplayerMaxHp, rect, 20, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);
	}

	// RightTop Font (Stage, Monster Lv, Timer)
	{
		Vector3 stagePos = upper->Find("UpperRight_StageFont")->GetWorldPos(); // �÷��̾�ü�¹� Pos
		Vector3 stageScale = upper->Find("UpperRight_StageFont")->scale; // �÷��̾�ü�¹� Scale

		Vector3 timerPos = upper->Find("UpperRight_TimeBox")->GetWorldPos();
		Vector3 timerScale = upper->Find("UpperRight_TimeBox")->scale;

		wstage = L"Stage 1";
		rect.left = (stagePos.x + 1) * App.GetHalfWidth() - 25;
		rect.top = (1 - stagePos.y) * App.GetHalfHeight() - 20;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wstage, rect, 15, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

		wmonsterLv = L"Level 1";
		rect.left = (stagePos.x + 1) * App.GetHalfWidth() - 25;
		rect.top = (1 - stagePos.y) * App.GetHalfHeight();
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wmonsterLv, rect, 15, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);


		float floatVal = TIMER->GetWorldTime();
		float fractionalPart;	// �Ҽ����κ� (t��)
		float second;			// �����κ� (��)

		// �Ҽ��� ���� �κ� ����
		fractionalPart = modf(floatVal, &second);

		// �Ҽ��� ���� �κ��� ���ڿ��� ��ȯ
		wstringstream wss;
		wss << std::fixed << std::setprecision(2) << fractionalPart;
		wtimer_tsecond = wss.str();
		// �Ҽ��� ���� �κп��� 0. �κ� ����
		size_t pos = wtimer_tsecond.find(L"0");
		if (pos != wstring::npos) {
			wtimer_tsecond.erase(pos, 2);
		}

		rect.left = (timerPos.x + 1) * App.GetHalfWidth() + 30;
		rect.top = (1 - timerPos.y) * App.GetHalfHeight() - 15;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wtimer_tsecond, rect, 10, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

		int second_print = (int)second % 60;

		if (second_print < 10)
			wtimer_second = L"0" + to_wstring((int)second_print);
		else
			wtimer_second = to_wstring((int)second_print);
		rect.left = (timerPos.x + 1) * App.GetHalfWidth();
		rect.top = (1 - timerPos.y) * App.GetHalfHeight() - 10;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wtimer_second, rect, 20, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

		int minute = (int)second / 60;
		if (minute < 10)
			wtimer_minute = L"0" + to_wstring((int)minute) + L" :";
		else
			wtimer_minute = to_wstring((int)minute) + L" :";
		rect.left = (timerPos.x + 1) * App.GetHalfWidth() - 40;
		rect.top = (1 - timerPos.y) * App.GetHalfHeight() - 10;
		rect.right = App.GetWidth();
		rect.bottom = App.GetHeight();
		DWRITE->RenderText(wtimer_minute, rect, 20, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);



		if ((4 - (int)GM->player->GetM2CoolTime()) <= 3.9)
		{
			wcoolTime_M2 = to_wstring(4 - (int)GM->player->GetM2CoolTime());
			rect.left = (rightBottom->Find("Skill_M2")->GetWorldPos().x + 1) * App.GetHalfWidth() - 10;
			rect.top = (1 - rightBottom->Find("Skill_M2")->GetWorldPos().y) * App.GetHalfHeight() - 30;
			rect.right = App.GetWidth();
			rect.bottom = App.GetHeight();
			DWRITE->RenderText(wcoolTime_M2, rect, 40, L"Noto Sans CJK KR Regular", Color(0.7, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);
		}


		if (GM->player->GetLShiftCoolTime() > 0)
		{
			wcoolTime_LShift = to_wstring((int)GM->player->GetLShiftCoolTime());
			rect.left = (rightBottom->Find("Skill_LShift")->GetWorldPos().x + 1) * App.GetHalfWidth() - 10;
			rect.top = (1 - rightBottom->Find("Skill_LShift")->GetWorldPos().y) * App.GetHalfHeight() - 30;
			rect.right = App.GetWidth();
			rect.bottom = App.GetHeight();
			DWRITE->RenderText(wcoolTime_LShift, rect, 40, L"Noto Sans CJK KR Regular", Color(0.7, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);
		}

		if ((10 - (int)GM->player->GetRCoolTime()) <= 9.9)
		{
			wcoolTime_R = to_wstring(10 - (int)GM->player->GetRCoolTime());
			rect.left = (rightBottom->Find("Skill_R")->GetWorldPos().x + 1) * App.GetHalfWidth() - 20;
			rect.top = (1 - rightBottom->Find("Skill_R")->GetWorldPos().y) * App.GetHalfHeight() - 30;
			rect.right = App.GetWidth();
			rect.bottom = App.GetHeight();
			DWRITE->RenderText(wcoolTime_R, rect, 40, L"Noto Sans CJK KR Regular", Color(0.7, 0, 0, 1), DWRITE_FONT_WEIGHT_BOLD);
		}
	}
}
