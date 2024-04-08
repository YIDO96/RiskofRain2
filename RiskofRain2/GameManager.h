#pragma once
class GameManager : public Singleton<GameManager>
{
public:
	/**GameManager���� �ٷ� Ŭ����
	Player, Monsters, Boss, ������, Map (���� Ŭ�������� ������ �ؾ��ϴ� Ŭ������)
	*/
	/*class Player* pl;*/
	//class InGameUI* ui;
	//vector<class Item*> items;//������ ��Ƴ��� ����
	//vector<class Bullet*> bulletPool;//�Ѿ� ��� ����

	class Player* player;//�÷��̾�
	vector<class Monster*> monsterPool;//���� ��Ƴ��� ����
	vector<class Feature*> featurePool;//������ ��� ����
	vector<class Pop*> particlePool; // ��ƼŬ
	class Terrain* map; // ��

	virtual ~GameManager();
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void ResizeScreen();
};

