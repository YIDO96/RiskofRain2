#pragma once
class Unit : public Actor
{
public:
	static Unit* Create(string name = "Unit");
	static Unit* Create(Unit* src);
	float	hp;			// ü��					// Get�Լ��� ����
	float	maxHp;		// �ִ� ü��
	int		exp;		// ����ġ (�÷��̾� : ���� óġ�� ��� �Ǵ� exp, ���� : ������ �÷��̾�� �ְ� �Ǵ� exp)
	int		gold;		// ���� ���
	float	attack;		// ���ݷ�				// Get�Լ��� ����
	int		defend;		// ��
	float	moveSpeed;

	Unit();
	virtual ~Unit();
protected:
	/*Unit();
	virtual ~Unit();*/
	Vector3 dir;


	/** ���� ����*/
		// �̵� �ӵ�
	int lv;				// ���� (�÷��̾� : ����ġ��, ���� : �ð�����?)
	int luna;			// ���� �糪





	void Update();
	void Render(shared_ptr<Shader> pShader = nullptr) override;
	virtual void Move(Vector3 Target);
	virtual void WolrdUpdate();
};

