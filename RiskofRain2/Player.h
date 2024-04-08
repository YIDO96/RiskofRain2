#pragma once
enum class PlayerState
{
    // 움직임
    IDLE,       // 가만히 있기
    WALK,       // 걷기
    RUN,        // 뛰기
    ROLL,       // 구르기
    SLIDE,      // 슬라이딩
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

    PlayerState         playerState;    // 플레이어 이동상태
    PlayerAttackState   attackState;    // 플레이어 공격상태 // 공격상태냐 아니면 
    SkillState          skillState;         // 공격       // 좌클릭이냐 우클릭이냐 R이냐

    //Vector3             dir;            // 대체, 나중에 Unit클래스를 상속 받을 친구
    Vector3             fixDir;         // 굴렀을때의 고정된 방향값
    Vector3             mouseDir;       // 마우스의 방향


    float               lastRot;
    float               lastRot_root;
    float               attackStopTime; // 공격 멈춘 시간 (4초가 되면 isAttack = false)

    bool                isRight;
    bool                isRoll;         // 구르고 있는지
    bool                isLButton;      // 좌클릭이 눌렸는지
    bool                isRButton;      // 우클릭이 눌렸는지
    bool                isRSkill;       // R이 눌렸는지
    bool                isDead;         // 죽었는지 (피가 0이면 사망처리)


    float               m2Timer;
    float               lShiftTimer;
    float               rTimer;

    float               LButtonFireTime; // 좌클릭 발사타임
    float               RSkillFireTime;  //  R스킬 발사시간(공속에 따라 더빠르게 발사가능)
    float               RSkillFire;  //  R스킬 발사시간(공속에 따라 더빠르게 발사가능)

    //슬라이딩 벡터 관련
    Vector3				moveDir = {};
    Ray					slidingVector;
    Vector3				slidingVectorHit = {};
    /** 플레이어만 가지고 있을 스텟*/

    Player();
    virtual ~Player();

public:
    Vector3             gravityDir;
    float               gravity;
    bool                isJump = false;         // 점프했는지
    bool                isJumpFinish = false;   // 점프 마지막 
    float               attackSpeed = 0.16f;    // 공속
    float               maxExp;
    bool                isEscape = true;       // 탐사정에 있는가?


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

    /** Get함수*/
    //Vector3 GetLast() { return last; };
    PlayerState     GetPlayerState() { return playerState; }
    Inventory* GetItemInven() { return itemInven; }

    float GetM2CoolTime() { return m2Timer; }
    float GetLShiftCoolTime() { return lShiftTimer; }
    float GetRCoolTime() { return rTimer; }

    int   GetLv() { return lv; }
    float GetMaxHp() { return maxHp; }
};

