#pragma once
#include "Actor.h"
#include"Math.h"
// �G�l�~�[�N���X
class Enemy : public Actor {
public:
    Enemy(class Game* game);
    ~Enemy();
    void UpdateActor(float deltaTime) override;
    void SetPosition(const Vector2& pos);

    // �ړ��^�C�v
    enum MoveType
    {
        STRAIGHT, // �����ړ�
        SHAKE,    // �h��Ȃ���ړ�
    };

private:
    MoveType mEnemyMoveType; // �ړ��^�C�v
    float mEnemySpeed;       // �ړ����x
    float mEnemyShakeHeight;  // �h��镝
    Vector2* mInitPosition;  // �ŏ��̈ʒu
    float mTimeCount; // �o�ߎ���
    float mWaitTime;  // �ҋ@����
    class ColliderComponent* mCollider;  // �R���C�_

public:
    // Getter, Setter
    void SetEnemyMoveType(const MoveType moveType) { mEnemyMoveType = moveType; }
    void SetEnemySpeed(const float speed) { mEnemySpeed = speed; }
    void SetEnemyShakeHeight(const float height) { mEnemyShakeHeight = height; }
    void SetWaitTime(const float time) { mWaitTime = time; }
    class ColliderComponent* GetCollider() const { return mCollider; }
};