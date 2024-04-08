#pragma once
class Unit : public Actor
{
public:
	static Unit* Create(string name = "Unit");
	static Unit* Create(Unit* src);
	float	hp;			// 체력					// Get함수로 변경
	float	maxHp;		// 최대 체력
	int		exp;		// 경험치 (플레이어 : 몬스터 처치시 얻게 되는 exp, 몬스터 : 죽을때 플레이어에게 주게 되는 exp)
	int		gold;		// 소유 골드
	float	attack;		// 공격력				// Get함수로 변경
	int		defend;		// 방어막
	float	moveSpeed;

	Unit();
	virtual ~Unit();
protected:
	/*Unit();
	virtual ~Unit();*/
	Vector3 dir;


	/** 공통 스텟*/
		// 이동 속도
	int lv;				// 레벨 (플레이어 : 경험치로, 몬스터 : 시간으로?)
	int luna;			// 소유 루나





	void Update();
	void Render(shared_ptr<Shader> pShader = nullptr) override;
	virtual void Move(Vector3 Target);
	virtual void WolrdUpdate();
};

