#pragma once

class MainPlayScene : public Scene
{
private:

public:
    MainPlayScene();
    ~MainPlayScene();

    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;
};

