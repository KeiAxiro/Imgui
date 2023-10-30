#ifndef DRAWKONTOL
#define DRAWKONTOL
#include "Main.cpp"
void PlayerContent()
{
	ImGui::BeginChild("Player Content", ImVec2((ImGui::GetContentRegionAvail().x),325), true);
	
    ImGui::Text("Player Mod");
	ImGui::Text("Bypass will protect you from banning/kick/report");
			            ImGui::Checkbox("Bypass 22%", &u64::bypass);
						//ImGui::Toggle("Bypass 22% (With Toggle)", &u64::bypass, kontol);
			            ImGui::Text("Main Cheats");
		            	ImGui::Checkbox("GodMode", &u64::health);
	            		ImGui::Checkbox("Auto Sprint", &u64::sprint);
	            		ImGui::SliderFloat("Speed", &u64::speed, 0.0f, 150.0f);
		            	ImGui::Checkbox("Respawn No Cooldown", &u64::respawn);
	            		//ImGui::Checkbox("Spam Chat", &u64::chat2);
						ImGui::Text("Chat Control");
						ImGui::SliderFloat("Chat Cooldown", &u64::chatcool, -100.0f, 100.0f);
						ImGui::Checkbox("Chat No Cooldown", &u64::chat);
						const char* spamchat[] = {"Hacked by Leminox X", "Hitoshi Its Hot", "Hello, y'all", "This Server Its Trash"};
     			        if (ImGui::Combo("Text (For Spam Chat)", &u64::chat2, spamchat, 4)) {		
						}
						ImGui::Checkbox("Set Text", &u64::setchat);
		            	ImGui::Checkbox("Silent Aimbot", &u64::aimbot);
						const char* changerID[] = {"Leminox X", "Admin", "Developer", "Hacker", "Mods", "HOST", "Owner", "Stuka V11", "Exploiter", "Hitoshi.A"};
     			        if (ImGui::Combo("ID/Name", &u64::ID2, changerID, 10)) {		
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
		            	ImGui::Checkbox("Send Explosion", &u64::sendgrena);
	
	
	ImGui::EndChild();
}

void PlayerSliderContent(){
	ImGui::BeginChild("Player Slider Content", ImVec2((ImGui::GetContentRegionAvail().x),275), true);
	ImGui::Text("Player Scale");
            ImGui::SliderInt("Scale X", &Config.FEATMenu.playerX, 0, 25);
            ImGui::SliderInt("Scale Y", &Config.FEATMenu.playerY, 0, 25);
            ImGui::SliderInt("Scale Z", &Config.FEATMenu.playerZ, 0, 25);
            ImGui::Checkbox("Set Player Scale", &Config.FEATMenu.playerscl);
    ImGui::EndChild();
}

void WeaponContent()
{
	ImGui::BeginChild("Weapon Content", ImVec2((ImGui::GetContentRegionAvail().x),0), true);
    ImGui::Text("Weapon Mod");
	ImGui::Checkbox("One Hit", &Config.FEATMenu.damage);
    ImGui::Checkbox("HitMarker", &Config.FEATMenu.headshot);
    ImGui::SliderInt("Range", &Config.FEATMenu.range, 0, 9999);
    ImGui::Checkbox("FireRate", &Config.FEATMenu.rate);
    ImGui::Checkbox("Unlimited Ammo", &Config.FEATMenu.ammo);
    ImGui::Checkbox("Auto Shoot", &Config.FEATMenu.shoot);
	ImGui::EndChild();
}

void NPCContent()
{
	ImGui::BeginChild("njir Content", ImVec2((ImGui::GetContentRegionAvail().x ),0), true);
    ImGui::Text("Content 3");
    ImGui::EndChild();
	}

void GameWorldContent()
{
	ImGui::BeginChild("njir Content", ImVec2((ImGui::GetContentRegionAvail().x ),0), true);
    ImGui::Text("Content 4");
	ImGui::EndChild();
}
#endif
