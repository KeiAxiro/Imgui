#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "includes/Dobby/dobby.h"
#define targetLibName OBFUSCATE("libil2cpp.so")
#include "Includes/Macros.h"
#include "Includes/Loader.h"
#include "Unity/Chams.h"
#include "imgui.h"
#include "imgui_internal.h"
//#include "Misc/ImGuiStuff.h"
#include "backends/imgui_impl_opengl3.h"
#include "../ImGui/imgui_internal.h"
#include "ImGui/ToggleFunc.h"
#include "Unity/Unity.h"
#include "Color.h"
#include "HOOK.h"
#include "Chams.h"
#include "Unity/Vector3.h"

struct Patches {
    MemoryPatch ;
}lxPatches;

namespace u64
{
	//for function
    static bool serverdest, mapdest, bypass, health, sprint, respawn, accuracy, chat, /*chat2,*/ damage, rate, ammo, shoot, npckill, npcshoot, npcdead, friendly, playerscl, headshot, /*chat2,*/ voted, masskill, telekill, mappos, revote, cfe, npcdiffi, spawnnpc1, spawnnpc2, explosionradius, grenadexplode, grenades, hidecross, showcross, npcrun, aimbot, gravity, autoexplode, setfov, setchat, setID, kicker, throwgrenade, enablesizebutton, setbackcol, mapname, grasshack, recoil;
	static bool skyfog, scanefog, grass, water, hideC, particle, camshake, shadow, setmatch;
	//for poly editor
	static bool editedmap1, editedmap2, loadmap, savemap, delemap, remoforest;
	//only for script activated
	static bool enablescript;
	//script function
	static bool camsensi, adssensi, gyrolooksensi, gyroadssensi, setvol, setpitch, loopsound, mutesound, booster, particle2, bothealth, shutdown;
	//Game NetWork
	static bool setnPort, cusfig, bindtoip, ruiback, sendper, stopserver, stopclient, loadscene, crc;
	//Menu Controlling Func
	static bool data, checkframe, setSOCIAL;
	//Teleport
	static bool tpspawn,
	            tpleft,
				tpright,
				tpup,
				tpdown,
				tpfor,
				tpback;
	//for slider
    static float fov, npcrate, speed, speedx, latencyc, time, playerX, playerY, playerZ, hud, mapscale, gravityX, gravityY, gravityZ, buttonheight, buttonwidth;
    static int killc, deathc, bscore, rscore, maxscore, maxtime, yes, no, graphics, tpp, grassdist, range, maxnpc, grenadetimer, banBy, target;
	//slider func for script
	static float camsensi2, adssensi2, gyrolooksensi2, gyroadssensi2, valume, pitch;
	//slider func for Network
	static int nPort;
	//Input Value
	//static float speed = 0.0f;
	//static int banBy = 0;
	//static int target = 0;
	//Combo Func
	static int chat2 = 0;
	static int ID2 = 0;
	static int SOCIAL = 0;
	static int matchtype = 0;
	//ColorEdit3
	static float backcol = 0.0f;
	static const char* spamchat[] = {"Hacked by Leminox X", "Hitoshi Its Hot", "Hello, y'all", "This Server Its Trash", "Kei"};
    static const char* changerID[] = {"Leminox X", "Admin", "Developer", "Hacker", "Mods", "HOST", "Owner", "Stuka V11", "Exploiter", "Hitoshi.A", "Kei"};
	static const char* socialID[] = {"YouTube (Leminox X)", "Discord (Leminox X)", "Telegram (Leminox X)", "YouTube (Kei)"};
	static const char* matchID[] = {"Team Match", "Conquest"};
}

//static bool kontol;

/*other namespace
//For Activated
bool backup = true;
//For Working
int lxAimFov;*/

namespace Variables2
	{
        int ActiveTab = 1;
    }

using namespace std;
std::string utf16le_to_utf8(const std::u16string &u16str) {
    if (u16str.empty()) { return std::string(); }
    const char16_t *p = u16str.data();
    std::u16string::size_type len = u16str.length();
    if (p[0] == 0xFEFF) {
        p += 1;
        len -= 1;
    }

    std::string u8str;
    u8str.reserve(len * 3);

    char16_t u16char;
    for (std::u16string::size_type i = 0; i < len; ++i) {

        u16char = p[i];

        if (u16char < 0x0080) {
            u8str.push_back((char) (u16char & 0x00FF));
            continue;
        }
        if (u16char >= 0x0080 && u16char <= 0x07FF) {
            u8str.push_back((char) (((u16char >> 6) & 0x1F) | 0xC0));
            u8str.push_back((char) ((u16char & 0x3F) | 0x80));
            continue;
        }
        if (u16char >= 0xD800 && u16char <= 0xDBFF) {
            uint32_t highSur = u16char;
            uint32_t lowSur = p[++i];
            uint32_t codePoint = highSur - 0xD800;
            codePoint <<= 10;
            codePoint |= lowSur - 0xDC00;
            codePoint += 0x10000;
            u8str.push_back((char) ((codePoint >> 18) | 0xF0));
            u8str.push_back((char) (((codePoint >> 12) & 0x3F) | 0x80));
            u8str.push_back((char) (((codePoint >> 06) & 0x3F) | 0x80));
            u8str.push_back((char) ((codePoint & 0x3F) | 0x80));
            continue;
        }
        {
            u8str.push_back((char) (((u16char >> 12) & 0x0F) | 0xE0));
            u8str.push_back((char) (((u16char >> 6) & 0x3F) | 0x80));
            u8str.push_back((char) ((u16char & 0x3F) | 0x80));
            continue;
        }
    }

    return u8str;
}
typedef struct _monoString {
    void *klass;
    void *monitor;
    int length;
    char chars[1];
    int getLength() {
        return length;
    }
    const char *toChars(){
        u16string ss((char16_t *) getChars(), 0, getLength());
        string str = utf16le_to_utf8(ss);
        return str.c_str();
    }
    char *getChars() {
        return chars;
    }
    std::string get_string() {

      return std::string(toChars());
}
} monoString;

//call function

void (*Auto)(void *instance);
void* (*PlayerKick1)(int banningBy);
void* (*PlayerKick2)(int target);
void (*Message)(void *instance, monoString*);
void (*Shot)(void *instance, bool head);
void (*Character)(void *instance, bool hide);
void (*BlueNPC)(void *instance, int val, monoString*);
void (*RedNPC)(void *instance, int val, monoString*);
void (*Explode)(void *instance);
void (*Silent)(void *instance, float dist);
void (*ThrowPlayer)(void *instance);
void (*ThrowNPC)(void *instance);
void (*LoadMap)(void *instance);
void (*SaveMap)(void *instance);
void (*DeleteMap)(void *instance);
void (*DeleteForest)(void *instance);
void (*DeleteAllData)(void *instance);
void (*CheckFrameRate)(void *instance);
void (*OpenSocialYT)(void *instance, monoString*);
void (*OpenSocialDC)(void *instance, monoString*);
void (*OpenSocialTG)(void *instance, monoString*);
void (*OpenSocialYT2)(void *instance, monoString*);
void (*Shutdown)(void *instance);


struct Variables {
    bool BooleanExample = false;
	//dont add bool on here.
} FT;

//static int tabe = 2;

EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

    if (!setup) {
        SetupImgui();
        setup = true;
    }

    ImGuiIO &io = ImGui::GetIO();
    switch (g_LastTouchEvent.action) {
    case TOUCH_ACTION_MOVE:
        if (g_LastTouchEvent.pointers > 1) {
            io.MouseWheel = g_LastTouchEvent.y_velocity;
            io.MouseDown[0] = false;
        }
        else {
            io.MouseWheel = 0;
        }
        break;
    case TOUCH_ACTION_DOWN:
        io.MouseDown[0] = true;
        break;
    case TOUCH_ACTION_UP:
        io.MouseDown[0] = false;
        //g_KeyEventQueues[event_key_code].push(event_action);
        break;
    default:
        break;
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();
	
	io.KeyMap[ImGuiKey_Backspace] = 259;
    io.KeyMap[ImGuiKey_A] = 65;
	
	int (*Screen_get_height)();

    int (*Screen_get_width)();
    ImVec4 color = ImVec4(1, 1, 1, 1);
	
	    static bool fps_detector = false;
	    static bool uf_info = false;
	    static bool game_cheat = false;
		static bool config = false;
		static bool menucont = false;
		
		{
			
			ImGui::Begin("Leminox X - Powered By Ignatius Team");
			ImGui::SetNextWindowSize(ImVec2(995, 500));	
			
        if (ImGui::BeginTabBar(OBFUSCATE("#tabbar"))) {
	
	    if (ImGui::BeginTabItem(OBFUSCATE("Home"))) {
		
		    ImGui::BeginChild("Menu One", ImVec2((ImGui::GetContentRegionAvail().x ),50), 50);
		{
		ImGui::Text("In Development");
			
		ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
        ImGui::GetColorU32(ImGuiCol_Border));
        ImGui::Spacing();
			
        ImGui::Text("In Development");
		
	}
	ImGui::EndChild();
		
        ImGui::BeginChild("Menu Two", ImVec2((ImGui::GetContentRegionAvail().x ),50), 50);
		{
		ImGui::Text("In Development");
			
		ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
        ImGui::GetColorU32(ImGuiCol_Border));
        ImGui::Spacing();
			
        ImGui::Text("In Development");
		
	}
    ImGui::EndChild();
			
	    ImGui::EndTabItem();
	    }
		if (ImGui::BeginTabItem(OBFUSCATE("Mod Menu"))) {
		    
			//if (!ImGui::Begin("StrikeFotressBox Mod Menu | E.C.F.A Team"));
			static int selected_tab = 0;
            static const char* tabs[] = {"Player", "NPC", "Server", "Teleport", "Gravity", "Game Debug", "Poly Editor", "Etc"};
			{
			
	ImDrawList *drawlist = ImGui::GetWindowDrawList();
	ImGui::TextColored(ImVec4(1,0,0,1), "YouTube: https://www.youtube.com/@LeminoxX");

    // Draw tabs on the left
    ImGui::BeginChild("Tab Buttons", ImVec2((ImGui::GetContentRegionAvail().x / 3.0f), ImGui::GetContentRegionAvail().y), true);

    for (int i = 0; i < 8; i++)
    {
        if (ImGui::Button(tabs[i], ImVec2(ImGui::GetContentRegionAvail().x, 60)))
        {
            selected_tab = i;
        }
    }
    ImGui::EndChild();
	ImVec4 backgroundCol = ImVec4(0.5,0.5,0.5,1);
    ImGui::SameLine();
	
    // Draw content on the right
    ImGui::BeginGroup();
    switch (selected_tab)
    {
    case 0:
        ImGui::BeginChild("Player Hacks", ImVec2((ImGui::GetContentRegionAvail().x), 0), true);
		{
		ImGui::Text("Player Hacks");
			
		ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
        ImGui::GetColorU32(ImGuiCol_Border));
        ImGui::Spacing();
			
        ImGui::Text("Bypass will protect you from banning/kick/report");
        ImGui::Checkbox("Bypass 22%", &u64::bypass);
        ImGui::Text("Main Cheats");
        ImGui::Checkbox("GodMode", &u64::health);
        ImGui::Checkbox("Auto Sprint", &u64::sprint);
        ImGui::SliderFloat("Speed", &u64::speed, 0.0f, 150.0f);
        ImGui::Checkbox("Respawn No Cooldown", &u64::respawn);
        ImGui::Text("Chat Control");
        ImGui::Checkbox("Chat No Cooldown", &u64::chat);
        
        if (ImGui::Combo("Text (For Spam Chat)", &u64::chat2, u64::spamchat, 5))
        {
        }
        ImGui::Checkbox("Set Text", &u64::setchat);
        ImGui::Checkbox("Silent Aimbot", &u64::aimbot);
        
        if (ImGui::Combo("ID/Name", &u64::ID2, u64::changerID, 11))
        {
        }
        ImGui::Checkbox("Set Player ID/Name", &u64::setID);
        ImGui::Checkbox("Accuracy 100x", &u64::accuracy);
        ImGui::SliderInt("Kill Count", &u64::killc, 0, 10000);
        ImGui::SliderInt("Death Count", &u64::deathc, 0, 10000);
        ImGui::SliderFloat("Latency Count", &u64::latencyc, 0.0f, 10000.0f);
	            		ImGui::Checkbox("Masskill", &u64::masskill);
		            	ImGui::Checkbox("Telekill", &u64::telekill);
	            		ImGui::SliderFloat("FOV", &u64::fov, 0.0f, 200.0f);
						ImGui::Checkbox("Set FOV", &u64::setfov);
	            		ImGui::Checkbox("One Hit", &u64::damage);
	            		ImGui::Checkbox("HitMarker", &u64::headshot);
	            		ImGui::SliderInt("Range", &u64::range, 0, 9999);
		            	ImGui::Checkbox("FireRate", &u64::rate);
						ImGui::Checkbox("No Recoil", &u64::recoil);
						ImGui::Checkbox("No Shake", &u64::camshake);
		            	ImGui::Checkbox("Unlimited Ammo", &u64::ammo);
		            	ImGui::Checkbox("Unlimited Grenade (Having CoolDown)", &u64::grenades);
		            	ImGui::Checkbox("Auto Shoot", &u64::shoot);
		            	ImGui::Text("Player Scale");
		            	ImGui::SliderFloat("Player Scale X", &u64::playerX, 0.0f, 100.0f);
		            	ImGui::SliderFloat("Player Scale Y", &u64::playerY, 0.0f, 100.0f);
		            	ImGui::SliderFloat("Player Scale Z", &u64::playerZ, 0.0f, 100.0f);
		            	ImGui::Checkbox("Set Player Scale", &u64::playerscl);
		            	ImGui::Text("Grenades Manager");
	            		ImGui::Checkbox("Highest Radius", &u64::explosionradius);
		            	ImGui::SliderInt("Grenades Timer", &u64::grenadetimer, -200, 200);
	}
	
	ImGui::EndChild();
	
        break;
    case 1:
        ImGui::BeginChild("NPC Hacks", ImVec2((ImGui::GetContentRegionAvail().x),0), true);
		{
		ImGui::Text("NPC Hacks");
			
		ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
        ImGui::GetColorU32(ImGuiCol_Border));
        ImGui::Spacing();
			
	ImGui::Checkbox("0 Kill", &u64::npckill);
	            		ImGui::Checkbox("Can't Shoot", &u64::npcshoot);
		            	ImGui::Checkbox("NPC Dead", &u64::npcdead);
	            		ImGui::SliderFloat("NPC FireRate", &u64::npcrate, 0.0f, 999.0f);
	            		ImGui::Checkbox("Cant Find Enemy", &u64::cfe);
		            	ImGui::Checkbox("Make NPC Difficulty", &u64::npcdiffi);
		            	ImGui::SliderInt("Max NPC", &u64::maxnpc, 0, 200);
		            	ImGui::Text("Spawner");
	            		if(ImGui::Button("Spawn NPC | Team Blue")) {
                                  u64::spawnnpc1 = true;
                        }
		            	ImGui::SameLine();
		            	if(ImGui::Button("Spawn NPC | Team Red")) {
                                  u64::spawnnpc2 = true;
                        }
		            	ImGui::Checkbox("NPC Running", &u64::npcrun);
	}
	ImGui::EndChild();
        break;
    case 2:
        ImGui::BeginChild("Server Hacks", ImVec2((ImGui::GetContentRegionAvail().x ),0), true);
	{
		ImGui::Text("Server Hacks");
		
		ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
        ImGui::GetColorU32(ImGuiCol_Border));
        ImGui::Spacing();
		
    ImGui::Checkbox("Friendly Fire", &u64::friendly);
	            		ImGui::SliderInt("Blue Score", &u64::bscore, 0, 999);
	            		ImGui::SliderInt("Red Score", &u64::rscore, 0, 999);
		            	ImGui::SliderInt("Max Score", &u64::maxscore, 0, 9999);
	            		ImGui::SliderFloat("Server Time", &u64::time, 0.00f, 999.00f);
						ImGui::SliderInt("Max Time", &u64::maxtime, 0, 9999);
		            	ImGui::Text("Control Vote");
		            	ImGui::SliderInt("Vote Yes", &u64::yes, 0, 999);
		            	ImGui::SliderInt("Vote No", &u64::no, 0, 999);
		            	ImGui::Checkbox("Set Vote Value", &u64::voted);
						ImGui::Text("Player Kicker (Alternative)");
						ImGui::SliderInt("Your Player ID", &u64::banBy, 1000, 2000);
						ImGui::SliderInt("Target Player ID", &u64::target, 1000, 2000);
						ImGui::Text("You can only kick players whose ID is more than 1000 to 2000 (max) number");
						if(ImGui::Button("Kick Player")) {
                                  u64::kicker = true;
                        }
	}
    ImGui::EndChild();
        break;
    case 3:
        ImGui::BeginChild("Teleport Hacks", ImVec2((ImGui::GetContentRegionAvail().x ),0), true);
		{
		ImGui::Text("Teleport Hacks");
			
		ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
        ImGui::GetColorU32(ImGuiCol_Border));
        ImGui::Spacing();
			
    ImGui::SliderInt("Teleport Power", &u64::tpp, 1, 101);
	            		if(ImGui::Button("Teleport Left")) {
                                  u64::tpleft = true;
                        }
		            	if(ImGui::Button("Teleport Right")) {
                                  u64::tpright = true;
                        }
		            	if(ImGui::Button("Teleport Up")) {
                                  u64::tpup = true;
                        }
		            	if(ImGui::Button("Teleport Down")) {
                                  u64::tpdown = true;
                        }
		            	if(ImGui::Button("Teleport Forward")) {
                                  u64::tpfor = true;
                        }
		            	if(ImGui::Button("Teleport Backward")) {
                                  u64::tpback = true;
                        }
		            	if(ImGui::Button("Teleport To [x:0,y:25,z:0]")) {
                                  u64::tpspawn = true;
                        }
	}
    ImGui::EndChild();
        break;
    case 4:
        ImGui::BeginChild("Gravity Hacks", ImVec2((ImGui::GetContentRegionAvail().x ),0), true);
		{
		ImGui::Text("Gravity Hacks");
			
		ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
        ImGui::GetColorU32(ImGuiCol_Border));
        ImGui::Spacing();
			
    ImGui::Checkbox("Set Gravity", &u64::gravity);
		            	ImGui::SliderFloat("Gravity X", &u64::gravityX, 9.8f, 100.0f);
		            	ImGui::SliderFloat("Gravity Y", &u64::gravityY, 9.8f, 100.0f);
		            	ImGui::SliderFloat("Gravity Z", &u64::gravityZ, 9.8f, 100.0f);
	}
    ImGui::EndChild();
        break;
	case 5:
        ImGui::BeginChild("Game Debug Hacks", ImVec2((ImGui::GetContentRegionAvail().x ),0), true);
		{
		ImGui::Text("Game Debug Hacks");
			
		ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
        ImGui::GetColorU32(ImGuiCol_Border));
        ImGui::Spacing();
			
    ImGui::Checkbox("Nil Sky Fog", &u64::skyfog);
		            	ImGui::Checkbox("Nil Scane Fog", &u64::scanefog);
		            	ImGui::Checkbox("Remove all grass", &u64::grass);
		            	ImGui::SliderInt("Grass Distance", &u64::grassdist, 0, 100);
		            	ImGui::SliderInt("Graphics Amount", &u64::graphics, 15, 300);
		            	ImGui::SliderFloat("Hud Opacity", &u64::hud, 20.0f, 100.0f);
		            	ImGui::Checkbox("Is UnderWater", &u64::water);
		            	ImGui::SliderFloat("Map Distance", &u64::mapscale, 0.00f, 50.00f);
		            	ImGui::Checkbox("Map Following Camera", &u64::mappos);
		            	ImGui::Checkbox("Remove Voting", &u64::revote);
						if (ImGui::Combo("Match Type", &u64::matchtype, u64::matchID, 2))
                        {
                        }
                        ImGui::Checkbox("Set Match Type", &u64::setmatch);
		            	ImGui::Checkbox("Hide Character", &u64::hideC);
		            	ImGui::Checkbox("Remove Particle", &u64::particle);
		            	if(ImGui::Button("Hide Crosshair")) {
                                  u64::hidecross = true;
                        }
		            	ImGui::SameLine();
		            	if(ImGui::Button("Show Crosshair")) {
                                  u64::showcross = true;
                        }
		            	ImGui::Checkbox("No Shadow", &u64::shadow);//82
	}
    ImGui::EndChild();
        break;
	case 6:
        ImGui::BeginChild("Poly Editor Hacks", ImVec2((ImGui::GetContentRegionAvail().x ),0), true);
		{
		ImGui::Text("Poly Editor Hacks");
			
		ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
        ImGui::GetColorU32(ImGuiCol_Border));
        ImGui::Spacing();
		
		if(ImGui::Button("Load Map")) {
                                  u64::loadmap = true;
                        }
		            	ImGui::SameLine();
						if(ImGui::Button("Save Map")) {
                                  u64::savemap = true;
                        }
		            	ImGui::SameLine();
						if(ImGui::Button("Delete Map")) {
                                  u64::delemap = true;
                        }
    ImGui::Checkbox("Edit Height Map", &u64::editedmap1);
						ImGui::Checkbox("Edit Color Map", &u64::editedmap2);
						ImGui::Checkbox("Remove all forest", &u64::remoforest);
						ImGui::Checkbox("Name Map: Leminox X GODs", &u64::mapname);
						ImGui::Checkbox("Modify Grass (Rendering, Amount, Distance)", &u64::grasshack);
	}
    ImGui::EndChild();
        break;
		
	case 7:
        ImGui::BeginChild("Etc Hacks", ImVec2((ImGui::GetContentRegionAvail().x ),350), true);
		{
		ImGui::Text("Etc Hacks");
			
		ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
        ImGui::GetColorU32(ImGuiCol_Border));
        ImGui::Spacing();
			
        ImGui::Checkbox("Update/Fixed Information", &uf_info);
		ImGui::Checkbox("Frame/FPS Detector", &fps_detector);
		ImGui::Checkbox("Game Info", &game_cheat);
		ImGui::Checkbox("Game Controlling", &config);
		ImGui::Checkbox("Menu Controlling (game)", &menucont);
		
	}
	ImGui::EndChild();
    break;
    }
    ImGui::EndGroup();
	}
	ImGui::EndTabItem();
	}
	if (ImGui::BeginTabItem(OBFUSCATE("Script"))) {
		
		ImGui::BeginChild("Enable Cheats", ImVec2((ImGui::GetContentRegionAvail().x ),88), true);
		{
		ImGui::Checkbox("Enable Script", &u64::enablescript);
	}
	ImGui::EndChild();
		
        ImGui::BeginChild("Menu Two", ImVec2((ImGui::GetContentRegionAvail().x ),550), true);
		{
		ImGui::Text("Script - Config Feature");
			
		ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
        ImGui::GetColorU32(ImGuiCol_Border));
        ImGui::Spacing();
			
                        ImGui::Checkbox("Destroy Server", &u64::serverdest);
			            ImGui::SliderFloat("Speed", &u64::speedx, 0.0f, 50.0f);
						ImGui::Checkbox("Bot GodMode", &u64::bothealth);
						ImGui::SameLine();
						ImGui::Checkbox("Shutdown Server", &u64::shutdown);
						if(ImGui::Button("Cam: 45")) {
                                  u64::camsensi = true;
                        }
						ImGui::SameLine();
						if(ImGui::Button("Ads: 54")) {
                                  u64::adssensi = true;
                        }
						ImGui::SameLine();
						if(ImGui::Button("Gyro Look: 100")) {
                                  u64::gyrolooksensi = true;
                        }
						ImGui::SameLine();
						if(ImGui::Button("Gyro Ads: 100")) {
                                  u64::gyroadssensi = true;
                        }
						ImGui::SliderFloat("Cam", &u64::camsensi2, 0.0f, 50.0f);
		                ImGui::SliderFloat("Ads", &u64::adssensi2, 0.0f, 50.0f);
		                ImGui::SliderFloat("Gyro Look", &u64::gyrolooksensi2, 0.0f, 50.0f);
		                ImGui::SliderFloat("Gyro Ads", &u64::gyroadssensi2, 0.0f, 50.0f);
						ImGui::Checkbox("Valume Changer", &u64::setvol);
						ImGui::SameLine();
						ImGui::Checkbox("Pitch Changer", &u64::setpitch);
			            ImGui::SliderFloat("Valume", &u64::valume, 0.00f, 100.00f);
			            ImGui::SliderFloat("Pitch", &u64::pitch, 0.00f, 100.00f);
						ImGui::Checkbox("Loop the sound", &u64::loopsound);
						ImGui::SameLine();
						ImGui::Checkbox("Mute the sound", &u64::mutesound);
						ImGui::SameLine();
						ImGui::Checkbox("Boost Game", &u64::booster);
						ImGui::TextColored(ImVec4(0,1,0,1), "Network Function no need to enable script.");
						ImGui::SliderInt("NetWork Port", &u64::nPort, 1000, 9999);
						ImGui::Checkbox("Set Port", &u64::setnPort);
						ImGui::SameLine();
						ImGui::Checkbox("Custom Config", &u64::cusfig);
						ImGui::SameLine();
						ImGui::Checkbox("Server Bind To Ip", &u64::bindtoip);
						ImGui::SameLine();
						ImGui::Checkbox("Run In Background", &u64::ruiback);
						ImGui::Checkbox("Send Peer Info", &u64::sendper);
						ImGui::SameLine();
						ImGui::Checkbox("Stop The Server", &u64::stopserver);
						ImGui::SameLine();
						ImGui::Checkbox("Stop The Client", &u64::stopclient);
						ImGui::SameLine();
						ImGui::Checkbox("Finished Load Scene", &u64::loadscene);
						ImGui::Checkbox("Check CRC Script", &u64::crc);
						
	}
    ImGui::EndChild();
	}
  }
}
			
			
			if (fps_detector)
        {
            ImGui::Begin("FPS/Frame Detector", &fps_detector);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text(("Mod Menu FPS: %d (%f Frames)"), (int)io.Framerate, 1000 / io.Framerate);
            ImGui::End();
        }
		
	if (uf_info)
        {
           ImGui::Begin("Update/Fixed Information", &uf_info);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
if (ImGui::BeginTabBar(OBFUSCATE("#tabbar"))) {
	
	if (ImGui::BeginTabItem(OBFUSCATE("Fixed"))) {
		
		    ImGui::Text("!: Get Fixed All");
			
	ImGui::EndTabItem();
	}    
	if (ImGui::BeginTabItem(OBFUSCATE("Update"))) {
		
			ImGui::Text("!: Get Update");
			
	ImGui::EndTabItem();
	}
  }
}
    if (game_cheat)
        {
            ImGui::Begin("Game Info", &game_cheat);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Name: Polyfield");
			ImGui::Text("Version: 0.5.0 (Latest New Version)");
			ImGui::Text("SDK Ori: 33");
			ImGui::Text("Modified SDK: 27");    
			ImGui::Text("Status: Get Cheated");
			ImGui::Text("Library: il2cpp");
			ImGui::Text("Messages: Exploiting polyfield will making you're smile with the devil (Leminox X)");
            ImGui::End();
        }
	if (config)
        {
            ImGui::Begin("Game Controlling", &config);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			
            ImGui::Checkbox("Spam Explode", &u64::autoexplode);
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1,0.921569,0.0156863,1), "For Automatic");
            if(ImGui::Button("Explode")) {
               u64::grenadexplode = true;
            }
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1,0.921569,0.0156863,1), "For Manualy");
			ImGui::Checkbox("Map Destruction", &u64::mapdest);
			ImGui::Checkbox("Throw Grenade (Player, NPC)", &u64::throwgrenade);
			ImGui::Checkbox("Button Scale", &u64::enablesizebutton);
			ImGui::SliderFloat("Height", &u64::buttonheight, 0.00f, 100.00f);
			ImGui::SliderFloat("Width", &u64::buttonwidth, 0.00f, 100.00f);
			ImGui::Checkbox("Set Background Color", &u64::setbackcol);
			ImGui::ColorEdit3("Background Color", &u64::backcol);
			
            ImGui::End();
        }
	if (menucont)
        {
            ImGui::Begin("Menu Controlling", &menucont);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("This Is A Bypass?? (unknown)");
			ImGui::Checkbox("Delete all data", &u64::data);
			ImGui::Text("The Func");
			ImGui::Checkbox("Check FrameRate", &u64::checkframe);
			if (ImGui::Combo("Social", &u64::SOCIAL, u64::socialID, 4))
            {
            }
            ImGui::Checkbox("Open The Social", &u64::setSOCIAL);
            ImGui::End();
        }
	/*if (script)
        {
            ImGui::Begin("Script C++ Language | By Leminox X", &script);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			{
			
            ImGui::Columns(2);
                ImGui::SetColumnOffset(0, 5);
				
				//ImGui::Spacing();
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1,0,0,1), "Script Category");

                ImGui::Columns(2);
                ImGui::SetColumnOffset(1, 210);
				
				ImGui::BeginChild("Scrolling");
				
                ImGui::Spacing();
                if (ImGui::Button("Exploit", ImVec2(125, 60)))
                    Variables2::ActiveTab = 1;
					
				ImGui::Spacing();
                if (ImGui::Button("Sensivity", ImVec2(125, 60)))
                    Variables2::ActiveTab = 2;
					
				ImGui::Spacing();
                if (ImGui::Button("Sound Control", ImVec2(125, 60)))
                    Variables2::ActiveTab = 3;
					
				ImGui::Spacing();
                if (ImGui::Button("FPS BOOST", ImVec2(125, 60)))
                    Variables2::ActiveTab = 4;
					
				ImGui::Spacing();
                if (ImGui::Button("Game NetWork", ImVec2(125, 60)))
                    Variables2::ActiveTab = 5;
					
				ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
                ImGui::GetWindowDrawList()->AddLine(cursor_pos,
                ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
                ImGui::GetColorU32(ImGuiCol_Border));
                ImGui::Spacing();
					
				ImGui::Checkbox("Enable Script", &u64::enablescript);
				
				}
				ImGui::NextColumn();
                {
					
				    ImGui::TextColored(ImVec4(1,0,0,1), "Script");
					
					ImGui::Separator();
					
					ImGui::BeginChild("Scrolling");
					
                    if (Variables2::ActiveTab == 1)
                    {
						ImGui::BeginChild("Exploit Script", ImVec2((ImGui::GetContentRegionAvail().x ),0), true);
		                {
			
                        ImGui::Checkbox("Destroy Server", &u64::serverdest);
			            ImGui::Text("Enable The (Destroy Server) First.");
			            ImGui::SliderFloat("Speed", &u64::speedx, 0.0f, 50.0f);
						ImGui::Checkbox("Bot GodMode", &u64::bothealth);
						ImGui::Text("Use this when you're found a Bot in the other Server.");
						ImGui::Checkbox("Shutdown Server", &u64::shutdown);
		
	                    }
                        ImGui::EndChild();
                    }
					if (Variables2::ActiveTab == 2)
                    {
						
						ImGui::BeginChild("Sensitivity Script", ImVec2((ImGui::GetContentRegionAvail().x ),350), true);
		                {
                        ImGui::Text("Button");
						
						ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
                        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
                        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
                        ImGui::GetColorU32(ImGuiCol_Border));
                        ImGui::Spacing();
						
						if(ImGui::Button("Cam: 45")) {
                                  u64::camsensi = true;
                        }
						if(ImGui::Button("Ads: 54")) {
                                  u64::adssensi = true;
                        }
						if(ImGui::Button("Gyro Look: 100")) {
                                  u64::gyrolooksensi = true;
                        }
						if(ImGui::Button("Gyro Ads: 100")) {
                                  u64::gyroadssensi = true;
                        }
	                    }
                        ImGui::EndChild();
						
						ImGui::Separator();
		
                        ImGui::BeginChild("Slider Script", ImVec2((ImGui::GetContentRegionAvail().x ),250), true);
		                {
		                ImGui::Text("Slider");
			
		                ImVec2 cursor_pos = ImGui::GetCursorScreenPos();
                        ImGui::GetWindowDrawList()->AddLine(cursor_pos,
                        ImVec2(cursor_pos.x + ImGui::GetContentRegionAvail().x, cursor_pos.y),
                        ImGui::GetColorU32(ImGuiCol_Border));
                        ImGui::Spacing();
			
                        ImGui::SliderFloat("Cam", &u64::camsensi2, 0.0f, 50.0f);
		                ImGui::SliderFloat("Ads", &u64::adssensi2, 0.0f, 50.0f);
		                ImGui::SliderFloat("Gyro Look", &u64::gyrolooksensi2, 0.0f, 50.0f);
		                ImGui::SliderFloat("Gyro Ads", &u64::gyroadssensi2, 0.0f, 50.0f);
		
	                    }
                        ImGui::EndChild();
                    }
					if (Variables2::ActiveTab == 3)
                    {
						
						ImGui::BeginChild("Sound Script", ImVec2((ImGui::GetContentRegionAvail().x ),0), true);
		                {
			
						ImGui::TextColored(ImVec4(1,0.921569,0.0156863,1), "!: You can use this when youre in match.");
                        ImGui::Checkbox("Valume Changer", &u64::setvol);
			            ImGui::SliderFloat("Valume", &u64::valume, 0.00f, 100.00f);
						ImGui::Checkbox("Pitch Changer", &u64::setpitch);
			            ImGui::SliderFloat("Pitch", &u64::pitch, 0.00f, 100.00f);
						ImGui::Checkbox("Loop the sound", &u64::loopsound);
						ImGui::Checkbox("Mute the sound", &u64::mutesound);
		
	                    }
                        ImGui::EndChild();
						
                    }
					if (Variables2::ActiveTab == 4)
                    {
                        ImGui::BeginChild("Fps Booster Script", ImVec2((ImGui::GetContentRegionAvail().x ),0), true);
		                {
			
                        ImGui::Text("Information!:");
						ImGui::TextColored(ImVec4(0,1,0,1), "Fps Boost Will Incrase Your Fps,");
						ImGui::TextColored(ImVec4(0,1,0,1), "When youre on game/match.");
						ImGui::TextColored(ImVec4(0,1,0,1), "This fps booster only for 3,4,5,6 gb RAM");
						ImGui::TextColored(ImVec4(0,1,0,1), "If your phone has 3gb maybe your max fps its 40+ fps.");
						ImGui::TextColored(ImVec4(0,1,0,1), "you can get 40 fps if the player its little");
						ImGui::TextColored(ImVec4(0,1,0,1), "if you want to incrase your fps, incrase your RAM too.");
						ImGui::Text("FPS BOOSTER:");
						ImGui::Checkbox("Boost Game", &u64::booster);
		
	                    }
                        ImGui::EndChild();
                    }
					if (Variables2::ActiveTab == 5)
                    {
                        ImGui::BeginChild("NetWork Script", ImVec2((ImGui::GetContentRegionAvail().x ),0), true);
		                {
			
						ImGui::TextColored(ImVec4(0,1,0,1), "Network Function no need to enable script.");
						ImGui::SliderInt("NetWork Port", &u64::nPort, 1000, 9999);
						ImGui::Checkbox("Set Port", &u64::setnPort);
						ImGui::Checkbox("Custom Config", &u64::cusfig);
						ImGui::Checkbox("Server Bind To Ip", &u64::bindtoip);
						ImGui::Checkbox("Run In Background", &u64::ruiback);
						ImGui::Checkbox("Send Peer Info", &u64::sendper);
						ImGui::Checkbox("Stop The Server", &u64::stopserver);
						ImGui::Checkbox("Stop The Client", &u64::stopclient);
						ImGui::Checkbox("Finished Load Scene", &u64::loadscene);
						ImGui::Checkbox("Check CRC Script", &u64::crc);
		
	                    }
                        ImGui::EndChild();
                    }
					
			}
            ImGui::EndChild();
			ImGui::End();
            }*/
	
    // Rendering
    ImGui::EndFrame();
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return old_eglSwapBuffers(dpy, surface);
}

//For Hooking


monoString *(*CretStr)(void *instance, const char *str);
monoString *String(const char *str) {
    //CreateString(sbyte* value)
    return CretStr(NULL, str);
}

/*monoString *CreateMonoString(const char *str) {
monoString *(*String_CreateString)(void *instance, const char *str) = (monoString *(*)(void *, const char *))getAbsoluteAddress("libil2cpp.so", 0x4406FC);

    return String_CreateString(NULL, str);
}*/

void (*old_PlayerUpdate)(void* instance);
    void PlayerUpdate(void* instance){
		enemyPlayers = instance;
		allPlayers = instance;
        //if(instance != NULL){
		if(u64::bypass) {
            *(bool*)((uint64_t) instance + 0x41) = false;
			*(bool*)((uint64_t) instance + 0x42) = false;
        }
        if(u64::health) {
            *(int*)((uint64_t) instance + 0x24) = 100;
        }
		if(u64::setID)
		{
			
			for(int i = 0; i <= 10; i++) {
    if(u64::ID2 == i){
		*(monoString **)((char *) instance + 0x3C) = String(u64::changerID[i]);
	}
	}
			/*
		if (u64::ID2 == 0) {
			*(monoString **)((char *) instance + 0x3C) = String("Leminox X");
		} else if (u64::ID2 == 1) {
			*(monoString **)((char *) instance + 0x3C) = String("Admin");
        } else if (u64::ID2 == 2) {
			*(monoString **)((char *) instance + 0x3C) = String("Developer");
        } else if (u64::ID2 == 3) {
			*(monoString **)((char *) instance + 0x3C) = String("Hacker");
        } else if (u64::ID2 == 4) {
			*(monoString **)((char *) instance + 0x3C) = String("Mods");
        } else if (u64::ID2 == 5) {
			*(monoString **)((char *) instance + 0x3C) = String("HOST");
        } else if (u64::ID2 == 6) {
			*(monoString **)((char *) instance + 0x3C) = String("Owner");
        } else if (u64::ID2 == 7) {
			*(monoString **)((char *) instance + 0x3C) = String("Stuka V11");
        } else if (u64::ID2 == 8) {
			*(monoString **)((char *) instance + 0x3C) = String("Exploiter");
        } else if (u64::ID2 == 9) {
			*(monoString **)((char *) instance + 0x3C) = String("Hitoshi.A");
        }
		*/
	   }
		if(u64::sprint) {
            *(bool*)((uint64_t) instance + 0x8D) = true;
        }
		else {
			*(bool*)((uint64_t) instance + 0x8D) = false;
		}
		if(u64::water) {
            *(bool*)((uint64_t) instance + 0x40) = true;
        }
		else {
			*(bool*)((uint64_t) instance + 0x40) = false;
		}
		if(u64::speed) {
            *(float*)((uint64_t) instance + 0x70) = u64::speed;
        }
		if(u64::hud) {
            *(float*)((uint64_t) instance + 0x214) = u64::hud;
			*(float*)((uint64_t) instance + 0x218) = u64::hud;
        }
		if(u64::respawn) {
            *(float*)((uint64_t) instance + 0x20) = 0.0f;
        }
		if(u64::accuracy) {
            *(float*)((uint64_t) instance + 0x150) = 100.0f;
        }
		if(u64::killc) {
            *(int*)((uint64_t) instance + 0x68) = u64::killc;
        }
		if(u64::deathc) {
            *(int*)((uint64_t) instance + 0x6C) = u64::deathc;
        }
		if(u64::latencyc) {
            *(float*)((uint64_t) instance + 0x23C) = u64::latencyc;
        }
		if(u64::headshot) {
            Shot(instance, true);
        }
		if(u64::chat) {
            *(float*)((uint64_t) instance + 0x234) = 0.0f;
        }
		if(u64::setchat)
		{/*
			if (u64::chat2 == 0) {
			Message(instance, String("Hacked by Leminox X"));
		} else if (u64::chat2 == 1) {
            Message(instance, String("Hitoshi Its Hot"));
        } else if (u64::chat2 == 2) {
            Message(instance, String("Hello, y'all"));
        } else if (u64::chat2 == 3) {
            Message(instance, String("This Server Its Trash"));
        }*/
		for(int i = 0; i <= 4; i++) {
    if(u64::chat2 == i){
		Message(instance, String(u64::spamchat[i]));
	}
}

	   }
		
		if (u64::playerscl) {
            set_localScale(get_transform(enemyPlayers),Vector3(u64::playerX,u64::playerY,u64::playerZ));
        }
		if (u64::masskill) {
            set_position(get_transform(enemyPlayers), Vector3(10,3,0));
        }
		if (u64::telekill) {
            Vector3 enemy = get_position(get_transform(enemyPlayers));
            set_position(get_transform(allPlayers), Vector3(enemy.x - 1.2, enemy.y, enemy.z));
        }
	    if (u64::tpdown) {
             Vector3 PlayerLocation = GetPlayerLocation(allPlayers);
             set_position(get_transform(allPlayers), Vector3(PlayerLocation.x, PlayerLocation.y - u64::tpp, PlayerLocation.z));
             u64::tpdown = false;
        }
        if (u64::tpup) {
            Vector3 PlayerLocation = GetPlayerLocation(allPlayers);
            set_position(get_transform(allPlayers), Vector3(PlayerLocation.x, PlayerLocation.y + u64::tpp, PlayerLocation.z));
            u64::tpup = false;
        }
        if (u64::tpleft) {
            Vector3 PlayerLocation = GetPlayerLocation(allPlayers);
            set_position(get_transform(allPlayers),Vector3(PlayerLocation.x - u64::tpp, PlayerLocation.y,PlayerLocation.z));
            u64::tpleft = false;
        }
        if (u64::tpright) {
            Vector3 PlayerLocation = GetPlayerLocation(allPlayers);
            set_position(get_transform(allPlayers),Vector3(PlayerLocation.x + u64::tpp, PlayerLocation.y, PlayerLocation.z));
            u64::tpright = false;
        }
	    if (u64::tpfor) {
            Vector3 PlayerLocation = GetPlayerLocation(allPlayers);
            set_position(get_transform(allPlayers), Vector3(PlayerLocation.x, PlayerLocation.y, PlayerLocation.z + u64::tpp));
            u64::tpfor = false;
        }
        if (u64::tpback) {
            Vector3 PlayerLocation = GetPlayerLocation(allPlayers);
            set_position(get_transform(allPlayers), Vector3(PlayerLocation.x, PlayerLocation.y, PlayerLocation.z - u64::tpp));
            u64::tpback = false;
        }
	    if (u64::tpspawn) {
            set_position(get_transform(allPlayers), Vector3(10,30,10));
            u64::tpspawn = false;
        }
		if(u64::hideC) {
            Character(instance, true);
        }
		if(u64::grenades) {
            *(int*)((uint64_t) instance + 0x114) = 0;
        }
		if(u64::hidecross) {
            *(bool*)((uint64_t) instance + 0x130) = false;
			u64::hidecross = false;
        }
		if(u64::throwgrenade) {
            ThrowPlayer(instance);
        }
		if(u64::showcross) {
            *(bool*)((uint64_t) instance + 0x130) = true;
			u64::showcross = false;
        }
		if(u64::camshake) {
            *(float*)((uint64_t) instance + 0x1E0) = 0.0f;
        }
		if(u64::enablescript) {
		 if(u64::serverdest) {
             *(int*)((uint64_t) instance + 0x6C) = 999999;
			 *(int*)((uint64_t) instance + 0x68) = 999999;
			 *(float*)((uint64_t) instance + 0x23C) = 999999;
			 *(float*)((uint64_t) instance + 0x70) = u64::speedx;
			 *(float*)((uint64_t) instance + 0x20) = 0.0f;
			 *(int*)((uint64_t) instance + 0x24) = 100;
			 *(int*)((uint64_t) instance + 0x9C) = 64;
         }
		 if(u64::camsensi) {
            *(int*)((uint64_t) instance + 0x74) = 0;
			u64::tpup = false;
         }
		 if(u64::adssensi) {
            *(int*)((uint64_t) instance + 0x78) = 0;
			u64::tpup = false;
         }
		 if(u64::gyrolooksensi) {
            *(int*)((uint64_t) instance + 0x7C) = 0;
			u64::tpup = false;
         }
		 if(u64::gyroadssensi) {
            *(int*)((uint64_t) instance + 0x80) = 0;
			u64::tpup = false;
         }
		 if(u64::camsensi2) {
            *(float*)((uint64_t) instance + 0x74) = u64::camsensi2;
         }
		 if(u64::adssensi2) {
            *(float*)((uint64_t) instance + 0x78) = u64::adssensi2;
         }
		 if(u64::gyrolooksensi2) {
            *(float*)((uint64_t) instance + 0x7C) = u64::gyrolooksensi2;
         }
		 if(u64::gyroadssensi2) {
            *(float*)((uint64_t) instance + 0x80) = u64::gyroadssensi2;
         }
		}
		if(u64::recoil) {
            *(float*)((uint64_t) instance + 0x154) = 0.0f;
        }
		if(u64::enablescript) {
		 if(u64::booster) {
            *(bool*)((uint64_t) instance + 0x40) = true;
         }
		}
        return old_PlayerUpdate(instance);
}

void (*old_FovHack1)(void *instance, float fov);
void FovHack1(void *instance, float fov) {
    if (instance != NULL) {
        if (u64::setfov) {
            fov = u64::fov;
        }
    }
    old_FovHack1(instance, fov);
}

float (*old_FovHack2)(void *instance);
float FovHack2(void *instance) {
    if (instance != NULL) {
        if (u64::setfov) {
            return u64::fov;
        }
    }
    return old_FovHack2(instance);
}

/*float (*old_FieldOfView)(void* instance);
   float FieldOfView(void* instance){
        if(instance != nullptr & u64::setfov != NULL) {
            return u64::fov;
        }
        return old_FieldOfView(instance);
}*/

float (*old_GetHeight)(void* instance);
   float GetHeight(void* instance){
        if(instance != nullptr & u64::enablesizebutton != NULL) {
            return u64::buttonheight;
        }
        return old_GetHeight(instance);
}

float (*old_GetWidth)(void* instance);
   float GetWidth(void* instance){
        if(instance != nullptr & u64::enablesizebutton != NULL) {
            return u64::buttonwidth;
        }
        return old_GetWidth(instance);
}

float (*old_BackgroundColor)(void* instance);
   float BackgroundColor(void* instance){
        if(instance != nullptr & u64::setbackcol != NULL) {
            return u64::backcol;
        }
        return old_BackgroundColor(instance);
}

void (*old_WeaponUpdate)(void* instance);
    void WeaponUpdate(void* instance){
        //if(instance != NULL){
			
        if(u64::damage) {
            *(int*)((uint64_t) instance + 0x28) = 9999;
        }
		if(u64::rate) {
            *(int*)((uint64_t) instance + 0x1C) = 999;
        }
		if(u64::ammo) {
            *(int*)((uint64_t) instance + 0x88) = 9999;
			*(int*)((uint64_t) instance + 0x8C) = 9999;
        }
		if(u64::range) {
            *(int*)((uint64_t) instance + 0x24) = u64::range;
        }
		if(u64::shoot) {
            Auto(instance);
        }
		if(u64::enablescript) {
		 if(u64::serverdest) {
             *(int*)((uint64_t) instance + 0x28) = 9999;
			 *(int*)((uint64_t) instance + 0x1C) = 999;
			 *(int*)((uint64_t) instance + 0x88) = 9999;
			 *(int*)((uint64_t) instance + 0x8C) = 9999;
         }
		}
        return old_WeaponUpdate(instance);
}

void (*old_NPCUpdate)(void* instance);
    void NPCUpdate(void* instance){
        //if(instance != NULL){
        if(u64::npckill) {
            *(int*)((uint64_t) instance + 0x5C) = 0;
        }
		if(u64::npcshoot) {
            *(bool*)((uint64_t) instance + 0x40) = false;
        }
		else {
			*(bool*)((uint64_t) instance + 0x40) = true;
		}
		if(u64::npcdead) {
            *(bool*)((uint64_t) instance + 0x2C) = true;
        }
		else {
			*(bool*)((uint64_t) instance + 0x2C) = false;
		}
		if(u64::npcrate) {
            *(float*)((uint64_t) instance + 0xE4) = u64::npcrate;
        }
		if(u64::cfe) {
            *(float*)((uint64_t) instance + 0x80) = 9999.0f;
        }
		if(u64::npcdiffi) {
            *(int*)((uint64_t) instance + 0x54) = 999;
        }
		if(u64::npcrun) {
            *(bool*)((uint64_t) instance + 0x2D) = true;
        }
		else {
			*(bool*)((uint64_t) instance + 0x2D) = false;
		}
		if(u64::throwgrenade) {
            ThrowNPC(instance);
        }
		if(u64::enablescript) {
		 if(u64::bothealth) {
            *(int*)((uint64_t) instance + 0x28) = 9999;
         }
		}
        return old_NPCUpdate(instance);
}

void (*old_NPCManager)(void* instance);
    void NPCManager(void* instance){
        //if(instance != NULL){
        if(u64::npcdiffi) {
            *(int*)((uint64_t) instance + 0x5C) = 999;
        }
		if(u64::maxnpc) {
            *(int*)((uint64_t) instance + 0xE4) = u64::maxnpc;
        }
		if(u64::spawnnpc1) {
            BlueNPC(instance, 1, String("Blue"));
			u64::spawnnpc1 = false;
        }
		if(u64::spawnnpc2) {
            RedNPC(instance, 1, String("Red"));
			u64::spawnnpc2 = false;
        }
        return old_NPCManager(instance);
}

void (*old_GameManager)(void* instance);
    void GameManager(void* instance){
        //if(instance != NULL){
        if(u64::friendly) {
            *(bool*)((uint64_t) instance + 0x23) = true;
        }
		else {
			*(bool*)((uint64_t) instance + 0x23) = false;
		}
		if(u64::bscore) {
            *(int*)((uint64_t) instance + 0x6C) = u64::bscore;
        }
		if(u64::rscore) {
            *(int*)((uint64_t) instance + 0x70) = u64::rscore;
        }
		if(u64::maxscore) {
            *(int*)((uint64_t) instance + 0x68) = u64::maxscore;
        }
		if(u64::time) {
            *(float*)((uint64_t) instance + 0x60) = u64::time;
        }
		if(u64::maxtime) {
            *(int*)((uint64_t) instance + 0x64) = u64::maxscore;
        }
		if(u64::voted) {
            *(int*)((uint64_t) instance + 0x2A8) = u64::yes;
			*(int*)((uint64_t) instance + 0x2AC) = u64::no;
        }
		if(u64::bypass) {
            *(int*)((uint64_t) instance + 0x2AC) = 999;
			*(float*)((uint64_t) instance + 0x2A4) = 0.0f;
        }
		if(u64::skyfog) {
            *(float*)((uint64_t) instance + 0x158) = 0.0f;
        }
		if(u64::scanefog) {
            *(float*)((uint64_t) instance + 0x170) = 0.0f;
        }
		if(u64::grass) {
            *(int*)((uint64_t) instance + 0x19C) = 0;
        }
		if(u64::graphics) {
            *(int*)((uint64_t) instance + 0x2C8) = u64::graphics;
        }
		if(u64::grassdist) {
            *(int*)((uint64_t) instance + 0x1A0) = u64::grassdist;
        }
		if(u64::revote) {
            *(bool*)((uint64_t) instance + 0x21) = false;
        }
		else {
			*(bool*)((uint64_t) instance + 0x21) = true;
		}
		if(u64::mapdest) {
            *(bool*)((uint64_t) instance + 0x22) = true;
        }
		else {
			*(bool*)((uint64_t) instance + 0x22) = false;
		}
		if(u64::shadow) {
            *(int*)((uint64_t) instance + 0xCC) = 0;
        }
		if(u64::kicker) {
		    PlayerKick1(u64::banBy);
            PlayerKick2(u64::target);
			u64::kicker = false;
        }
		if(u64::enablescript) {
		 if(u64::serverdest) {
             *(int*)((uint64_t) instance + 0x19C) = 0;
			 *(bool*)((uint64_t) instance + 0x21) = false;
			 *(float*)((uint64_t) instance + 0x60) = 1000.9f;
			 *(int*)((uint64_t) instance + 0x6C) = 999;
			 *(int*)((uint64_t) instance + 0x70) = 999;
			 *(int*)((uint64_t) instance + 0x68) = 9999;
         }
		 if(u64::booster) {
            *(float*)((uint64_t) instance + 0x158) = 0.0f;
			*(float*)((uint64_t) instance + 0x170) = 0.0f;
			*(int*)((uint64_t) instance + 0x19C) = 0;
			*(int*)((uint64_t) instance + 0x2C8) = 1000;
			*(int*)((uint64_t) instance + 0xCC) = 0;
         }
		 if(u64::shutdown) {
            Shutdown(instance);
         }
		}
		if(u64::setmatch)
		{
			if (u64::matchtype == 0) {
			*(int*)((uint64_t) instance + 0x1C) = 0;
		} else if (u64::matchtype == 1) {
            *(int*)((uint64_t) instance + 0x1C) = 1;
        }
       }
        return old_GameManager(instance);
}

bool (*old_ParticleControl2)(void* instance);
bool ParticleControl2(void* instance){
	   if(u64::enablescript) {
        if(u64::particle2) {
            return false;
        }
	   }
        return old_ParticleControl2(instance);
}

void (*old_Minimaps)(std::uintptr_t instance);
    void Minimaps(std::uintptr_t instance){
        //if(instance != NULL){
		if(u64::mapscale) {
            *(float*)((uint64_t) instance + 0x10) = u64::mapscale;
        }
		if(u64::mappos) {
            *(bool*)((uint64_t) instance + 0xC) = true;
        }
		else {
			*(bool*)((uint64_t) instance + 0xC) = false;
		}
        return old_Minimaps(instance);
}

bool (*old_ParticleControl)(void* instance);
bool ParticleControl(void* instance){
        if(instance != nullptr & u64::particle != NULL) {
            return false;
        }
        return old_ParticleControl(instance);
}

void (*old_Bullet)(void* instance);
    void Bullet(void* instance){
        //if(instance != NULL)
		if(u64::aimbot) {
		    *(float*)((uint64_t) instance + 0x28) = 9999.0f;
			*(float*)((uint64_t) instance + 0x14) = 9999.0f;
            Silent(instance, 9999.0f);
        }
		if(u64::enablescript) {
		 if(u64::serverdest) {
			 *(int*)((uint64_t) instance + 0xC) = 99999;
		     *(float*)((uint64_t) instance + 0x28) = 9999.0f;
			 *(float*)((uint64_t) instance + 0x14) = 9999.0f;
			 *(float*)((uint64_t) instance + 0x44) = 0.0f;
			 *(bool*)((uint64_t) instance + 0x34) = true;
			 *(bool*)((uint64_t) instance + 0x35) = true;
             Silent(instance, 9999.0f);
         }
		}
        return old_Bullet(instance);
}

void (*old_Grenades)(void* instance);
    void Grenades(void* instance){
        //if(instance != NULL){
        if(u64::explosionradius) {
            *(int*)((uint64_t) instance + 0xC) = 99999;
        }
		if(u64::grenadetimer) {
            *(int*)((uint64_t) instance + 0x1C) = u64::grenadetimer;
        }
		if(u64::grenadexplode) {
            Explode(instance);
			u64::grenadexplode = false;
        }
		if(u64::autoexplode) {
            Explode(instance);
        }
		if(u64::enablescript) {
		 if(u64::serverdest) {
			 *(int*)((uint64_t) instance + 0xC) = 99999;
			 *(int*)((uint64_t) instance + 0x1C) = 500;
			 Explode(instance);
         }
		}
        return old_Grenades(instance);
}

void (*old_GravityHack)(void* physics);
    void GravityHack(void* physics){
    
		if(u64::gravity) {
        Vector3 gravity1 = get_position(get_transform(physics));
        Vector3 gravity2 = gravity1 + Vector3(u64::gravityX,u64::gravityY,u64::gravityZ);
        set_position(get_transform(physics), gravity2);
        
        }
        return old_GravityHack(physics);
}

void (*old_PolyEditor)(void* instance);
    void PolyEditor(void* instance){
        //if(instance != NULL){
			
        if(u64::editedmap1) {
            *(bool*)((uint64_t) instance + 0x40) = true;
        }
		if(u64::editedmap2) {
            *(bool*)((uint64_t) instance + 0x41) = true;
        }
		if(u64::loadmap) {
            LoadMap(instance);
			u64::loadmap = false;
        }
		if(u64::savemap) {
            SaveMap(instance);
			u64::savemap = false;
        }
		if(u64::delemap) {
            DeleteMap(instance);
			u64::delemap = false;
        }
		if(u64::remoforest) {
            DeleteForest(instance);
        }
		if (u64::mapname) {
			*(monoString **)((char *) instance + 0x44) = String("Leminox X GODs");
		}
		if(u64::grasshack) {
            *(bool*)((uint64_t) instance + 0x19C) = true;
			*(bool*)((uint64_t) instance + 0x1A0) = 0;
			*(bool*)((uint64_t) instance + 0x1A4) = 0;
        }
        return old_PolyEditor(instance);
}

void (*old_SoundVolume)(void *instance, float valume);
void SoundVolume(void *instance, float valume) {
    if (instance != NULL) {
	  if(u64::enablescript) {
        if (u64::setvol) {
            valume = u64::valume;
        }
	  }
    }
    old_SoundVolume(instance, valume);
}

void (*old_SoundPitch)(void *instance, float pitch);
void SoundPitch(void *instance, float pitch) {
    if (instance != NULL) {
	  if(u64::enablescript) {
        if (u64::setpitch) {
            pitch = u64::pitch;
        }
	  }
    }
    old_SoundPitch(instance, pitch);
}

bool (*old_Looping)(std::uintptr_t instance);
bool Looping(std::uintptr_t instance){
	   if(u64::enablescript) {
        if(u64::loopsound) {
            return true;
        }
	   }
        return old_Looping(instance);
}

void (*old_SoundGetMute)(void *instance, bool mute);
void SoundGetMute(void *instance, bool mute) {
    if (instance != NULL) {
	  if(u64::enablescript) {
        if (u64::mutesound) {
            mute = true;
        }
	  }
    }
    old_SoundGetMute(instance, mute);
}

void (*old_MenuControl)(void* instance);
    void MenuControl(void* instance){
        if(instance != NULL){
			
		if(u64::data) {
            DeleteAllData(instance);
        }
		if(u64::checkframe) {
            CheckFrameRate(instance);
        }
		if(u64::setSOCIAL)
		{
			if (u64::SOCIAL == 0) {
			OpenSocialYT(instance, String("https://youtube.com/@LeminoxX"));
		} else if (u64::SOCIAL == 1) {
            OpenSocialDC(instance, String("https://discord.gg/DPT93e9Y"));
        } else if (u64::SOCIAL == 2) {
            OpenSocialTG(instance, String("https://t.me/leminox"));
        } else if (u64::SOCIAL == 3) {
            OpenSocialYT2(instance, String("https://youtube.com/@keidjaru.a2115"));
        }
       }
		
	    }
        return old_MenuControl(instance);
}

void (*old_NetworkPort1)(void *instance, int port);
void NetworkPort1(void *instance, int port) {
    if (instance != NULL) {
        if (u64::setnPort) {
            port = u64::nPort;
        }
    }
    old_NetworkPort1(instance, port);
}

int (*old_NetworkPort2)(void *instance);
int NetworkPort2(void *instance) {
    if (instance != NULL) {
        if (u64::setnPort) {
            return u64::nPort;
        }
    }
    return old_NetworkPort2(instance);
}

bool (*old_CustomConfig)(std::uintptr_t instance);
bool CustomConfig(std::uintptr_t instance){
        if(u64::cusfig) {
            return true;
        }
        return old_CustomConfig(instance);
}

bool (*old_ServerBindToIp)(std::uintptr_t instance);
bool ServerBindToIp(std::uintptr_t instance){
        if(u64::bindtoip) {
            return true;
        }
        return old_ServerBindToIp(instance);
}

bool (*old_RunInBackground)(std::uintptr_t instance);
bool RunInBackground(std::uintptr_t instance){
        if(u64::ruiback) {
            return true;
        }
        return old_RunInBackground(instance);
}

bool (*old_SendPeerInfo)(std::uintptr_t instance);
bool SendPeerInfo(std::uintptr_t instance){
        if(u64::sendper) {
            return true;
        }
        return old_SendPeerInfo(instance);
}

bool (*old_StopServer)(std::uintptr_t instance);
bool StopServer(std::uintptr_t instance){
        if(u64::stopserver) {
            return true;
        }
        return old_StopServer(instance);
}

bool (*old_StopClient)(std::uintptr_t instance);
bool StopClient(std::uintptr_t instance){
        if(u64::stopclient) {
            return true;
        }
        return old_StopClient(instance);
}

bool (*old_FinishLoadScene)(std::uintptr_t instance);
bool FinishLoadScene(std::uintptr_t instance){
        if(u64::loadscene) {
            return true;
        }
        return old_FinishLoadScene(instance);
}

bool (*old_CheckCRCScript)(std::uintptr_t instance);
bool CheckCRCScript(std::uintptr_t instance){
        if(u64::crc) {
            return true;
        }
        return old_CheckCRCScript(instance);
}

void *hack_thread(void *) {
    LOGI(OBFUSCATE("Its Loaded Wuahahahaha!. . ."));

    sleep(5);

    //Check if target lib is loaded
    do {
        sleep(1);
    } while (!isLibraryLoaded("libil2cpp.so"));
	
	//Anti-lib rename
	do {
        sleep(1);
    } while (!isLibraryLoaded("libLeminoxX.so"));

    address = findLibrary("libil2cpp.so");

    // Hook eglSwapBuffers
    auto addr = (uintptr_t)dlsym(RTLD_NEXT, "eglSwapBuffers");
    LOGD("eglSwapBuffers address: 0x%X", addr);
    DobbyHook((void *)addr, (void *)hook_eglSwapBuffers, (void **)&old_eglSwapBuffers);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x318EE4), (void*) PlayerUpdate, (void**)&old_PlayerUpdate);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x72D29C), (void*) FovHack1, (void**)&old_FovHack1);//set_fieldofview
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x72D24C), (void*) FovHack2, (void**)&old_FovHack2);//get_fieldofview
	
	//DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x72D24C), (void*) FieldOfView, (void**)&old_FieldOfView);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xA90E74), (void*) WeaponUpdate, (void**)&old_WeaponUpdate);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x301554), (void*) NPCUpdate, (void**)&old_NPCUpdate);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x36B738), (void*) GameManager, (void**)&old_GameManager);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x2FBB18), (void*) Minimaps, (void**)&old_Minimaps);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xB171A8), (void*) ParticleControl, (void**)&old_ParticleControl);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xB171A8), (void*) ParticleControl2, (void**)&old_ParticleControl2);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x30E6B8), (void*) NPCManager, (void**)&old_NPCManager);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x3879F8), (void*) Grenades, (void**)&old_Grenades);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x35AB4C), (void*) Bullet, (void**)&old_Bullet);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xB02888), (void*) GravityHack, (void**)&old_GravityHack);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x75113C), (void*) GetHeight, (void**)&old_GetHeight);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x75112C), (void*) GetWidth, (void**)&old_GetWidth);

	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x72D70C), (void*) BackgroundColor, (void**)&old_BackgroundColor);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x3D1F8C), (void*) PolyEditor, (void**)&old_PolyEditor);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xB12E58), (void*) SoundVolume, (void**)&old_SoundVolume);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xB12EB0), (void*) SoundPitch, (void**)&old_SoundPitch);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xB133E8), (void*) Looping, (void**)&old_Looping);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0xB135F0), (void*) SoundGetMute, (void**)&old_SoundGetMute);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x3962E0), (void*) MenuControl, (void**)&old_MenuControl);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x63F400), (void*) NetworkPort1, (void**)&old_NetworkPort1);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x63F3F8), (void*) NetworkPort2, (void**)&old_NetworkPort2);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x63F634), (void*) CustomConfig, (void**)&old_CustomConfig);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x63F408), (void*) ServerBindToIp, (void**)&old_ServerBindToIp);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x63F448), (void*) RunInBackground, (void**)&old_RunInBackground);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x63F468), (void*) SendPeerInfo, (void**)&old_SendPeerInfo);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x642724), (void*) StopServer, (void**)&old_StopServer);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x6428FC), (void*) StopClient, (void**)&old_StopClient);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x642EF8), (void*) FinishLoadScene, (void**)&old_FinishLoadScene);
	
	DobbyHook((void*)getAbsoluteAddress("libil2cpp.so", 0x63F458), (void*) CheckCRCScript, (void**)&old_CheckCRCScript);
	
	//call function hook
	Auto = (void (*)(void*))getAbsoluteAddress("libil2cpp.so", 0xA91E20);//private void Shoot() { }
	PlayerKick1 = (void* (*)(int))getAbsoluteAddress("libil2cpp.so", 0x377F74);//public void RpcVoteKick(uint _id, uint _by) { } (1)
	PlayerKick2 = (void* (*)(int))getAbsoluteAddress("libil2cpp.so", 0x377F74);//public void RpcVoteKick(uint _id, uint _by) { } (2)
	Message =  (void (*)(void*, monoString*))getAbsoluteAddress("libil2cpp.so", 0x32AFEC);//private void RpcSendChat(string _chat) { }
	CretStr = (monoString *(*)(void *, const char *))getAbsoluteAddress("libil2cpp.so", 0x4406FC);//CreateString(sbyte* value)
	Shot = (void (*)(void*, bool))getAbsoluteAddress("libil2cpp.so", 0x324560);//public void HitMarker(bool _headshot) { }
	Character = (void (*)(void*, bool))getAbsoluteAddress("libil2cpp.so", 0x3152A4);//private void HideCharacter(bool _hide) { }
	BlueNPC = (void (*)(void*, int, monoString*))getAbsoluteAddress("libil2cpp.so", 0x30F134);//private void SpawnNpc(int _count, string _team) { }
	RedNPC = (void (*)(void*, int, monoString*))getAbsoluteAddress("libil2cpp.so", 0x30F134);//private void SpawnNpc(int _count, string _team) { }
	Explode = (void (*)(void*))getAbsoluteAddress("libil2cpp.so", 0x389AA0);//public void Explode() { }
	Silent = (void (*)(void*, float))getAbsoluteAddress("libil2cpp.so", 0x35AADC);//private void CheckCollisionPercision(float _dist) { }
	ThrowPlayer = (void (*)(void*))getAbsoluteAddress("libil2cpp.so", 0x31FA84);//private IEnumerator ThrowGrenade() { } (Player)
	ThrowNPC = (void (*)(void*))getAbsoluteAddress("libil2cpp.so", 0x3051B4);//private IEnumerator ThrowGrenade() { } (NPC)
	LoadMap = (void (*)(void*))getAbsoluteAddress("libil2cpp.so", 0x3DF2D8);//public void LoadMap() { }
	SaveMap = (void (*)(void*))getAbsoluteAddress("libil2cpp.so", 0x3DF22C);//public void SaveMap() { }
	DeleteMap = (void (*)(void*))getAbsoluteAddress("libil2cpp.so", 0x3DF384);//public void DeleteMap() { }
	DeleteForest = (void (*)(void*))getAbsoluteAddress("libil2cpp.so", 0x3DDDC8);//public void DeleteForest() { }
	DeleteAllData = (void (*)(void*))getAbsoluteAddress("libil2cpp.so", 0x398F60);//public void DeleteAllData() { }
	CheckFrameRate = (void (*)(void*))getAbsoluteAddress("libil2cpp.so", 0x392D08);//private void CheckFrameRate() { }
	OpenSocialYT =  (void (*)(void*, monoString*))getAbsoluteAddress("libil2cpp.so", 0x3989E0);//public void OpenSocial(string _id) { }
	OpenSocialDC =  (void (*)(void*, monoString*))getAbsoluteAddress("libil2cpp.so", 0x3989E0);//same as
	OpenSocialTG =  (void (*)(void*, monoString*))getAbsoluteAddress("libil2cpp.so", 0x3989E0);//same as
	OpenSocialYT2 =  (void (*)(void*, monoString*))getAbsoluteAddress("libil2cpp.so", 0x3989E0);//same as
	Shutdown = (void (*)(void*))getAbsoluteAddress("libil2cpp.so", 0x643934);//public static void Shutdown() { }
	
	

    /*


            hexPatches.MemoryExample = MemoryPatch:createWithHex(targetLibName,
                                                                 string2Offset(OBFUSCATE("0x000000")),
                                                                 OBFUACATE("00 00 00 00 00 00 00 00")));

            HOOK_LIB(targetLibName, "0x000000", Hook_Example, Orig_Example);


    */


    pthread_exit(nullptr);
    return nullptr;


}
void StartBackend(JNIEnv* env) {
    //Input
    DobbyHook((void*)env->functions->RegisterNatives, (void*)hook_RegisterNatives, (void **)&old_RegisterNatives);

}

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *globalEnv;
    vm->GetEnv((void **) &globalEnv, JNI_VERSION_1_6);

    StartBackend(globalEnv);

    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
    return JNI_VERSION_1_6;
}

