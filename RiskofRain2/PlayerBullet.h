#pragma once
class PlayerBullet : public Bullet
{
public:
    static PlayerBullet* Create(string name = "PlayerBullet");

private:

    PlayerBullet();
    virtual ~PlayerBullet();
public:

    void	Update();
    void	Render(shared_ptr<Shader> pShader = nullptr);

    void    SetPos(Vector3 pos) override;
    void    Fire(Vector3 dir, float power, Vector3 rotation) override;

    void    Attack();
    Pop*    InitParticle();

    //bool    GetIsFire() { return isFire; }
};

