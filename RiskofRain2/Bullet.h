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
    
    Vector3     fireDir;            // ��� ����
    float       power;              // �߻� �Ŀ�
    bool        isFire;             // �߻��ߴ����� �ľ��ϱ� ���� bool��
    bool        isCollsion;         // �浹���� bool��
    Ray         BulletRay;          // �Ѿ� Ray
    float       extinctionTime;     // �Ѿ� ���󰡴� �ð� (ex, extinctionTime = 10�̸� 10���� �������)
    Pop*        bulletParticle;     // �Ѿ� ��ƼŬ

    virtual Pop* InitParticle();
    void	Update();
    void	Render(shared_ptr<Shader> pShader = nullptr);
    void    CollisionWithMap();
    virtual void    SetPos(Vector3 pos);
    virtual void    Fire(Vector3 dir, float power, Vector3 rotation);

    virtual void PlayerToBossAttack(class Boss* boss);
    //bool    GetIsFire() { return isFire; }
};

