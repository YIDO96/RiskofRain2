#pragma once
enum class PlayerState
{
    // ������
    IDLE,       // ������ �ֱ�
    WALK,       // �ȱ�
    RUN,        // �ٱ�
    ROLL,       // ������
    SLIDE,      // �����̵�
};

enum class PlayerAttackState
{
    IDLE,
    ATTACK,
};

enum class SkillState
{
    NONE,
    LBUTTON,
    RBUTTON,
    R,
};


class Player : public Unit
{
public:
    static Player* Create(string name = "Player");


private:
    class Inventory* itemInven;

    PlayerState         playerState;    // �÷��̾� �̵�����
    PlayerAttackState   attackState;    // �÷��̾� ���ݻ��� // ���ݻ��³� �ƴϸ� 
    SkillState          skillState;         // ����       // ��Ŭ���̳� ��Ŭ���̳� R�̳�

    //Vector3             dir;            // ��ü, ���߿� UnitŬ������ ��� ���� ģ��
    Vector3             fixDir;         // ���������� ������ ���Ⱚ
    Vector3             mouseDir;       // ���콺�� ����


    float               lastRot;
    float               lastRot_root;
    float               attackStopTime; // ���� ���� �ð� (4�ʰ� �Ǹ� isAttack = false)

    bool                isRight;
    bool                isRoll;         // ������ �ִ���
    bool                isLButton;      // ��Ŭ���� ���ȴ���
    bool                isRButton;      // ��Ŭ���� ���ȴ���
    bool                isRSkill;       // R�� ���ȴ���
    bool                isDead;         // �׾����� (�ǰ� 0�̸� ���ó��)


    float               m2Timer;
    float               lShiftTimer;
    float               rTimer;

    float               LButtonFireTime; // ��Ŭ�� �߻�Ÿ��
    float               RSkillFireTime;  //  R��ų �߻�ð�(���ӿ� ���� �������� �߻簡��)
    float               RSkillFire;  //  R��ų �߻�ð�(���ӿ� ���� �������� �߻簡��)

    //�����̵� ���� ����
    Vector3				moveDir = {};
    Ray					slidingVector;
    Vector3				slidingVectorHit = {};
    /** �÷��̾ ������ ���� ����*/

    Player();
    virtual ~Player();

public:
    Vector3             gravityDir;
    float               gravity;
    bool                isJump = false;         // �����ߴ���
    bool                isJumpFinish = false;   // ���� ������ 
    float               attackSpeed = 0.16f;    // ����
    float               maxExp;
    bool                isEscape = true;       // Ž������ �ִ°�?


    void	Update() override;
    void	Render(shared_ptr<Shader> pShader = nullptr) override;

    void    FSM();
    void    AinmChange(PlayerState state);
    void    Move(Vector3 Target);
    void    Jump();
    void    LevelUp();
    void    DecreaseHP();

    void    StatGUI();
    void    SetPos(Vector3 pos);
    void    WolrdUpdate();
    void    PlayerRenderHierarchy();
    void	MoveBack(Actor* col);

    /** Get�Լ�*/
    //Vector3 GetLast() { return last; };
    PlayerState     GetPlayerState() { return playerState; }
    Inventory* GetItemInven() { return itemInven; }

    float GetM2CoolTime() { return m2Timer; }
    float GetLShiftCoolTime() { return lShiftTimer; }
    float GetRCoolTime() { return rTimer; }

    int   GetLv() { return lv; }
    float GetMaxHp() { return maxHp; }
};

