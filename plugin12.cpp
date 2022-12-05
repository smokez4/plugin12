#include "pch.h"
#include "plugin12.h"
#include "bakkesmod\wrappers\ArrayWrapper.h"
#include "bakkesmod\wrappers\GameEvent\TutorialWrapper.h"
#include "bakkesmod\wrappers\GameObject\CarWrapper.h"
#include "bakkesmod\wrappers\GameObject\BallWrapper.h"
#include "bakkesmod\wrappers\GameObject\CarComponent\DodgeComponentWrapper.h"
#include <vector>
BAKKESMOD_PLUGIN(plugin12, "pinch plugin", plugin_version, PERMISSION_OFFLINE)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void plugin12::onLoad()
{
	
	dodgemode = std::make_shared<bool>(false);
	enabled = std::make_shared<bool>(false);
	unitsme = std::make_shared<bool>(false);
	addspin = std::make_shared<bool>(false);
	reseta = std::make_shared<bool>(false);
	CVarWrapper EnabledCvar = cvarManager->registerCvar("plugin_enable", "0", "enables", true, true, 0, true, 1);
	EnabledCvar.bindTo(enabled);
	EnabledCvar.addOnValueChanged(std::bind(&plugin12::OnEnabledChanged, this));
	cvarManager->registerCvar("plugin_dodgemode", "0", "enables", true, true, 0, true, 1).bindTo(dodgemode);
	cvarManager->registerCvar("plugin_uom", "0", "enables", true, true, 0, true, 1).bindTo(unitsme);
	cvarManager->registerCvar("plugin_addspin", "0", "enables", true, true, 0, true, 1).bindTo(addspin);
	cvarManager->registerCvar("plugin_autotoggle", "0", "enables", true, true, 0, true, 1).bindTo(reseta);
	_globalCvarManager = cvarManager;
	cvarManager->registerCvar("velo_y", "0", "", true, true, -6000.f, true, 6000.f);
	cvarManager->registerCvar("velo_x", "0", "", true, true, -6000.f, true, 6000.f);
	cvarManager->registerCvar("velo_z", "0", "", true, true, -6000.f, true, 6000.f);
	cvarManager->registerCvar("velo_addedspin", "0", "", true, true, -6.f, true, 6.f);
	cvarManager->log("h)");
	cvarManager->registerNotifier("plugin_toggle", [this](std::vector<std::string> args) {
		Toggle();
		}, "", PERMISSION_ALL);
	cvarManager->registerNotifier("plugin_testshot", [this](std::vector<std::string> args) {
		TestShot();
		}, "", PERMISSION_ALL);
}

void plugin12::OnEnabledChanged() {
	
	float enabled = { cvarManager->getCvar("plugin_enable").getFloatValue() };
	if (enabled == 0) {

		Reset();

	}
	else {

		if (*dodgemode) { this->Dodge(); }
		else { this->LoadHooks(); }

	}
}

void plugin12::Toggle() {


	float enabled = { cvarManager->getCvar("plugin_enable").getFloatValue() };
	if (enabled == 1) {

		cvarManager->executeCommand("plugin_enable 0");

	}
	else {

		cvarManager->executeCommand("plugin_enable 1");

	}
}

bool::plugin12::IsValid() {

	if (!*enabled) { return false; }

}
void plugin12::TestShot() {
	ServerWrapper server = gameWrapper->GetGameEventAsServer();
	if (!server) { return; };
	BallWrapper ball = server.GetBall();
	if (ball.IsNull()) { return; };
	float velo_x = { cvarManager->getCvar("velo_x").getFloatValue() };
	float velo_y = { cvarManager->getCvar("velo_y").getFloatValue() };
	float velo_z = { cvarManager->getCvar("velo_z").getFloatValue() };
	float addedspin = { cvarManager->getCvar("velo_addedspin").getFloatValue() };

	if (*addspin) {

		ball.SetAngularVelocity(addedspin, false);

	}

	if (*unitsme) {
		Vector ballspeed = Vector(velo_x, velo_z, velo_y);

		ball.SetVelocity(ballspeed);
	}
	else {
		Vector ballspeed = Vector(velo_x * 27.7777778, velo_z * 27.7777778, velo_y * 27.7777778);

		ball.SetVelocity(ballspeed);
	}
}


void plugin12::Reset() {

	gameWrapper->UnhookEvent("Function TAGame.CarComponent_Dodge_TA.EventActivateDodge");
	gameWrapper->UnhookEvent("Function TAGame.Ball_TA.RecordCarHit");
}

void plugin12::LoadHooks() {
	
	gameWrapper->HookEvent("Function TAGame.Ball_TA.RecordCarHit", std::bind(&plugin12::GameEndedEvent, this, std::placeholders::_1));

}
void plugin12::Dodge()
{
	gameWrapper->HookEvent("Function TAGame.CarComponent_Dodge_TA.EventActivateDodge", std::bind(&plugin12::Hit, this, std::placeholders::_1));
}
void plugin12::Hit(std::string name) {


	gameWrapper->HookEvent("Function TAGame.Ball_TA.RecordCarHit", std::bind(&plugin12::GameEndedEvent, this, std::placeholders::_1));
}


void plugin12::GameEndedEvent(std::string name)
{

	if (!IsValid()) { return; }
	ServerWrapper server = gameWrapper->GetGameEventAsServer();
	if (!server) { return; };
	BallWrapper ball = server.GetBall();
	if (ball.IsNull()) { return; };
	float velo_x = { cvarManager->getCvar("velo_x").getFloatValue() };
	float velo_y = { cvarManager->getCvar("velo_y").getFloatValue() };
	float velo_z = { cvarManager->getCvar("velo_z").getFloatValue() };
	float addedspin = { cvarManager->getCvar("velo_addedspin").getFloatValue() };
	
	
	if (*addspin) {

		ball.SetAngularVelocity(addedspin, false);

	}

	if (*unitsme) {
		Vector ballspeed = Vector(velo_x, velo_z, velo_y);

		ball.SetVelocity(ballspeed);
	}
	else {
		Vector ballspeed = Vector(velo_x * 27.7777778, velo_z * 27.7777778, velo_y * 27.7777778);

		ball.SetVelocity(ballspeed);
	}



	if (*reseta) {

		cvarManager->executeCommand("sleep 50; plugin_enable 0");

	}
}
	
	


void plugin12::onUnload() {

	cvarManager->log("bye lul");

}


