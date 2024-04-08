#pragma once
#include "../2DFrameWork/framework.h"
#pragma comment (lib,"../Build/2DFrameWork/2DFrameWork.lib")

// GM
#include "GameManager.h"

// GameObject
#include "Unit.h"
#include "Bullet.h"

// Player
#include "Player.h"
#include "PlayerBullet.h"
#include "Inventory.h"


// Scene
#include "MainPlayScene.h"

// UI
#include "InGameUI.h"


#define GM			GameManager::GetInstance()