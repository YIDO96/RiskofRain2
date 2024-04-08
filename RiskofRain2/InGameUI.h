#pragma once
class InGameUI
{
public:
	static InGameUI* Create(string name = "InGameUI");
	/** 인게임 UI */
	UI* upper;
	UI* leftBottom;
	UI* rightBottom;

	UI* bossHPbar;
	bool isGoalClear = false;


private:
	wstring wplayerHp;
	wstring whpSlash;
	wstring wplayerMaxHp;
	wstring wlv;
	wstring wplayerLv;

	wstring wstage;
	wstring wmonsterLv;
	wstring wtimer_tsecond;
	wstring wtimer_second;
	wstring wtimer_minute;

	wstring wcoolTime_M2;
	wstring wcoolTime_LShift;
	wstring wcoolTime_R;

	wstring itemSlot[9];

	// 임시
	//int playerlv = 1;
	//int playerhp = 120;
	//int playermaxhp = 120;
	//float playerattack = 12;
	//
	//int playerexp = 0;
	//int playerMaxexp = 150;
	//
	//bool isGoalClear = false;
	//
	//float coolTime_M2 = 0;
	//float coolTime_LShift = 0;
	//float coolTime_R = 0;

	RECT rect;

public:
	InGameUI();
	~InGameUI();

	void Init();
	void Update();
	void Render();
	void RenderH();
	void ResizeScreen();


	void PlayerInvenFont();
	void RenderFont();
};

