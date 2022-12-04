#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);

#pragma comment( lib, "pluginsdk.lib" )

class plugin12 : public BakkesMod::Plugin::BakkesModPlugin
{
private:
    std::shared_ptr<bool> enabled;
    std::shared_ptr<bool> dodgemode;
    std::shared_ptr<bool> unitsme;
    std::shared_ptr<bool> reseta;
    std::shared_ptr<bool> addspin;

public:
    virtual void onLoad();
    virtual void onUnload();
    void Dodge();
    void LoadHooks();
    void GameEndedEvent(std::string name);
    void Hit(std::string name);
    void Reset();
    void TestShot();
    bool IsValid();
    void Toggle();
    void OnEnabledChanged();
   

    void Render(CanvasWrapper canvas);
    void Log();
    void OnRoundStarted();
    void OnCarHitBall(BallWrapper HitBall, void* Params);
    void OnBallHitGoal(BallWrapper Ball, void* Params);

    Vector GetRelativeVectorComponents(Rotator RootObjectRotation, Vector RootObjectVector, Vector RelativeObjectVector);
};

struct RecordCarHitParams
{
    uintptr_t HitCar; //CarWrapper
    Vector HitLocation;
    Vector HitNormal;
    unsigned char HitType;
};






