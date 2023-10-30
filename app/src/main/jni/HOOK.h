#include "Unity/Vector3.h"
#include "Vector55.h"

bool (*IsLocal)(void* player);
int (*GetPlayerTeam)(void* player);
int (*GetPlayerHealthforclear)(void* player);

void *(*get_transform2)(void *component2);
void (*set_position2)(void *transform2, Vector55 newPosition2);
void (*Transform_get_position2)(void *transform2, Vector55 *out);









bool (*SetMasterClient)(void*);
bool (*SetMasterClient2)(void*);
bool (*SetMasterClient3)(void*);

bool (*CloseConnection)(void*);


void *myPlayer = NULL;
void *enemyPlayers = NULL;
void *allPlayers = NULL;
void *otherPlayers = NULL;




Vector3 get_position(void *transform) {
    if (!transform)
        return Vector3();

    Vector3 position;

    static const auto get_position_injected = reinterpret_cast<uint64_t(__fastcall *)(void *,
                                                                                      Vector3 &)>(getAbsoluteAddress(
            "libil2cpp.so", 0x6C7788));
    get_position_injected(transform, position);

    return position;
}





///////TELLEKILL

void set_position(void* transform, Vector3 test) {

    if (transform) {
        static const auto set_position_injected = reinterpret_cast<uint64_t(__fastcall*)(void*, Vector3)>
        (getAbsoluteAddress("libil2cpp.so", 0x6C7840));//set_position_injected //Ttansform
        set_position_injected(transform, test);
    }
}








//Component.get_transform();
void *get_transform(void *player) {
    if (!player)
        return NULL;

    static const auto get_transform_injected = reinterpret_cast<uint64_t(__fastcall *)(
            void *)>(getAbsoluteAddress("libil2cpp.so", 0x73094C));//So2 0.15.3 - 0x1420660

    return (void *) get_transform_injected(player);
}

//local scale

Vector3 get_localScale(void* transform) {
    if (!transform)
        return Vector3();

    Vector3 position;

    static const auto get_localScale_injected = reinterpret_cast<uint64_t(__fastcall*)(void*, Vector3&)>(getAbsoluteAddress("libil2cpp.so", 0x6C8598));//UnityEngine.CoreModule
    get_localScale_injected(transform, position);

    return position;
}

void set_localScale(void* transform, Vector3 test) {

    if (transform) {
        static const auto set_localScale_injected = reinterpret_cast<uint64_t(__fastcall*)(void*, Vector3)>(getAbsoluteAddress("libil2cpp.so", 0x6C8650));//UnityEngine.CoreModule
        set_localScale_injected(transform, test);
    }
}


/*
//CameraManager.get_main();
void *get_camera() {

    static const auto get_camera_injected = reinterpret_cast<uint64_t(__fastcall *)()>(getAbsoluteAddress(
            "libil2cpp.so", 0x1C2A64C));//0x1C2A64C

    return (void *) get_camera_injected();
}
*/



void* (*get_camera)();



//Screen.get_height();
int get_screen_height() {

    static const auto get_height_injected = reinterpret_cast<uint64_t(__fastcall *)()>(getAbsoluteAddress(
            "libil2cpp.so", 0x223A37C));

    return (int) get_height_injected();
}

//Screen.get_width();
int get_screen_width() {

    static const auto get_width_injected = reinterpret_cast<uint64_t(__fastcall *)()>(getAbsoluteAddress(
            "libil2cpp.so", 0x223A334));

    return (int) get_width_injected();
}








//Camera.WorldToScreenPoint_Injected
//public Vector3 WorldToScreenPoint(Vector3 position, MonoorSetreo..., out Vector3)
/*
Vector3 WorldToScreenPoint(void *transform, Vector3 test) {
    if (!transform)
        return Vector3();

    Vector3 position;

    static const auto WorldToScreenPoint_Injected = reinterpret_cast<uint64_t(__fastcall *)(void *,
                                                                                            Vector3,
                                                                                            int,
                                                                                            Vector3 &)>(getAbsoluteAddress(
            "libil2cpp.so", 0x1C29BF4));//So2 0.15.3 - 0x141D0C0
    WorldToScreenPoint_Injected(transform, test, 2, position);

    return position;
}

*/

Vector3 WorldToScreenPoint(void *transform, Vector3 test) {
    
    Vector3 position;

    void (*WorldToScreenPoint_Injected)(void *, Vector3, int, Vector3&) = (void (*)(void *,Vector3, int, Vector3&)) 
	 getAbsoluteAddress("libil2cpp.so", 0x1C29BF4);

    WorldToScreenPoint_Injected(transform, test, 2, position);

    return position;
}





//Ttansform
static Vector3 get_forward(void *player) {
    Vector3 (*_GetForward)(void *players) = (Vector3 (*)(void *)) getAbsoluteAddress("libil2cpp.so", 0x2243478);
    return _GetForward(player);
}




Vector55 get_position2(void *player) {
    Vector55 pos2;
    Transform_get_position2(player, &pos2);
    return pos2;
}

Vector55 GetPlayerLocation2(void *player){
    Vector55 location2;
    location2 = get_position2(get_transform2(player));

    return location2;
}



	

bool IsPlayerDead(void *player) {
    if(GetPlayerHealthforclear(player) < 1) {
        return true;
    }
    return false;
}


Vector3 GetPlayerLocation(void *player) {
    Vector3 location;
    location = get_position(get_transform(player));

    return location;
}



/*static void *get_arms(void *player) {
    return *(void **)((uint64_t) player + 0x3C);
}*/



struct enemy_t {
    void *object;
    Vector3 location;
    int health;
};



