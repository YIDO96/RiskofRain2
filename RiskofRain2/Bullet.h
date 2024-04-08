#pragma once

enum class BulletType
{
    LEMURIAN,
    GOLEM,
    BOSS1,
    BOSS2,
    PLAYER
};

class Bullet : public Actor
{
public:
    static Bullet* Create(string name = "Bullet");
    Bullet();
    virtual ~Bullet();
    BulletType  bulletType;
    
    Vector3     fireDir;            // 쏘는 방향
    float       power;              // 발사 파워
    bool        isFire;             // 발사했는지를 파악하기 위한 bool값
    bool        isCollsion;         // 충돌판정 bool값
    Ray         BulletRay;          // 총알 Ray
    float       extinctionTime;     // 총알 날라가는 시간 (ex, extinctionTime = 10이면 10초후 사라진다)
    Pop*        bulletParticle;     // 총알 파티클

    virtual Pop* InitParticle();
    void	Update();
    void	Render(shared_ptr<Shader> pShader = nullptr);
    void    CollisionWithMap();
    virtual void    SetPos(Vector3 pos);
    virtual void    Fire(Vector3 dir, float power, Vector3 rotation);

    virtual void PlayerToBossAttack(class Boss* boss);
    //bool    GetIsFire() { return isFire; }
};

