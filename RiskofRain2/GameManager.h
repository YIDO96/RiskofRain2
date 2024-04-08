#pragma once
class GameManager : public Singleton<GameManager>
{
public:
	/**GameManager에서 다룰 클래스
	Player, Monsters, Boss, 지형물, Map (여러 클래스에서 관여를 해야하는 클래스들)
	*/
	/*class Player* pl;*/
	//class InGameUI* ui;
	//vector<class Item*> items;//아이템 담아놓는 벡터
	//vector<class Bullet*> bulletPool;//총알 담는 벡터

	class Player* player;//플레이어
	vector<class Monster*> monsterPool;//몬스터 담아놓는 벡터
	vector<class Feature*> featurePool;//지형물 담는 벡터
	vector<class Pop*> particlePool; // 파티클
	class Terrain* map; // 맵

	virtual ~GameManager();
	virtual void Init();
	virtual void Release();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
	virtual void ResizeScreen();
};

