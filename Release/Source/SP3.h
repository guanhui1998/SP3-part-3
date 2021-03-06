#ifndef SP3_H
#define SP3_H

//#include "Scene.h"
//#include "Mtx44.h"
//#include "Camera3.h"
//#include "Mesh.h"
//#include "MatrixStack.h"
//#include "Light.h"
#include "SceneBase.h"
#include "Minimap.h"
#include "Vector2.h"
#include "PlayerInfo.h"
#include "Enemy.h"
#include "Missile.h"
#include <irrKlang.h>
using namespace irrklang;
#include "Character.h"
using namespace CHARACTER;
#include "Monster.h"
using namespace MONSTER;
#include "Projectile.h"
#include "Collision.h"
#include "AI.h"
using namespace AI;
//#include "Panel.h"
#include "MainMenu.h"
#include "Buttons.h"
#include "GameObject.h"
//#include "SpriteManager.h"
#include "BattleStage.h"
class SP3 : public SceneBase
{
    enum GameState
    {
        Menu,
		Pause,
        Game,
        End,
		Win,
    };

public:
    SP3();
    ~SP3();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();

    void RenderTextOnScreen2(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderBackground();
    Missile* FetchMissile();
    void MissileUpdate(float dt);

	void RenderProjectile(PROJECTILE::Projectile* projectile);

    void GameStateRenderText();
    void GameStateUpdate();
    void GameStateRender();
	void Restart();
	

    void Scenetransition();
    void SpawnObjects();

	void RenderCharacter();
    void RenderList();

	void ProjectileCollision(double dt, Projectile* projectile);
    void ProjectileCollisionResponse(Projectile* projectile,
        std::vector<Monster*>::iterator monsterlist_iterator);
    void CreateParticles(int number, Vector3 position, float vel,
        float lifetime, ParticleObject_TYPE type);

    void MonsterUpdate(double dt, MapLoad* map);

    void RenderParticles();
    void UpdateParticles(double dt);
    ParticleObject* GetParticle(void);
    void renderbattlestage();


    //void SpriteAnimationUpdate(double dt);


    enum Level
    {
        LEVEL1,
        LEVEL2,
        LEVEL3,
        LEVEL4,
		LEVEL5,
    };

	CCharacter* Character;
	ArtInt* AI;

	MapLoad* LoadFile;
    
	GameObject* FetchGO();
	void RenderGO(GameObject *go);
	Vector3 Checkmousepos();

	Buttons Play;
	MainMenu Main;
	int m_objectCount = 0;

	bool MiniBossAlive;

private:
    float rotateAngle;   

	std::vector<GameObject *> m_goList;

    // Handle to the minimap
    CMinimap* m_cMinimap;

    // Handle to the tilemaps
    
    void RenderTileMap();
    // Hero's information

    // Codes for Scrolling
    int tileOffset_x, tileOffset_y;

    // Codes for Parallax Scrolling

    int rearWallOffset_x, rearWallOffset_y;
    int rearWallTileOffset_x, rearWallTileOffset_y;
    int rearWallFineOffset_x, rearWallFineOffset_y;

    // Enemies
    std::vector<Monster*> Monster_List;

    std::vector<Missile*> MissileList;
    float missileTriggerTimer;

	float firingDebounce;
	static const int fireRate = 10;
	bool Fire;
	bool chargeFire;
	float chargeTime;
	float chargeDmg;
	float BossFiringDebounce;
    int lives;
	bool Moving;
	float endScreenTimer;
	int AnimationCounter;
	float AnimationTimer;
	bool ShootingN;
	bool ShootingNet;
	bool CShooting;
	bool Shooting;

    GameState State = Menu;

    //sound
    ISoundEngine* sceneSoundEngine;
    /*ISoundSource* shootBulletSound;
    ISoundSource* win;
    ISoundSource* lose;*/
    ISoundSource* jump;
    ISoundSource* shoot;
    ISoundSource* Normal_level_sound;
    ISoundSource* Miniboss_level_sound;
    ISoundSource* Finalboss_level_sound;
    ISound* Currsound;
    float jumpsoundtimer;

    //level transition
    Level CurrLevel;

    //particles
    std::vector<ParticleObject*> particleList;//Used to store particles
    Vector3 m_gravity;//gravity affecting the particles
    int m_particleCount;// Count for particles
    unsigned MAX_PARTICLE; // Max no of particles

    //sprite manager
    //SpriteManager* spritemanager;

    //battestage
    BattleStage* Battle;

    bool battlestage;
};

#endif