#pragma once

class Main : public Scene
{
private:



public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

/**
플레이어는 간단하게 본인의 스텟이나 경험치 등의 값이 변동하는 정도의 함수를 구현
Scene에서 플레이어의 함수를 사용해서 구현하는 방식
*/