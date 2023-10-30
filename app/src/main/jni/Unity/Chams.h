#ifndef NORKA_CHAMS
#define NORKA_CHAMS
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <dlfcn.h>
#include <Substrate/SubstrateHook.h>
#include <Substrate/CydiaSubstrate.h>

static void *handle;
static const char* shaderName;
static bool enableWallhack;
static bool enableWallhackW;
static bool enableWallhackS;
static bool enableWallhackG;
static bool enableWallhackO;
static bool enableSkyColor;
static bool enableRainbow;
static bool enableRainbow1;
static float r = 255.0f;
static float g = 0.0f;
static float b = 0.0f;
static int w = 2;
static float gw = 7.0f;
static float ow = 6.0f;
static int a = 255;

float red = 255.0f;
float gren = 0.0f;
float blue =0.0f;
float mi = 0.0f;


void setShader(const char* s) {
	handle = dlopen("libGLESv2.so", RTLD_LAZY);
    shaderName = s;
}

const char* getShader() {
    return shaderName;
}



void SetWallhack(bool enable){
    enableWallhack = enable;
}

void SetWireframe(bool enable){
    enableWallhackW = enable;
}

void SetShading(bool enable){
    enableWallhackS = enable;
}

void SetGlow(bool enable){
    enableWallhackG = enable;
}

void SetOutline(bool enable){
    enableWallhackO = enable;
}

void SetSkyColor(bool enable){
    enableSkyColor = enable;
}

void SetRainbow(bool enable){
    enableRainbow = enable;
}
void SetRainbow1(bool enable){
    enableRainbow1 = enable;
}


void SetR(int set){
    r = set;
}

void SetG(int set){
    g = set;
}

void SetB(int set){
    b = set;
}

void SetWireframeWidth(int set){
    w = set;
}

void SetGlowWidth(int set){
    gw = set;
}

void SetOutlineWidth(int set){
    ow = set;
}


bool getWallhackEnabled(){
    return enableWallhack;
}

bool getWireframeEnabled(){
    return enableWallhackW;
}

bool getShadingEnabled(){
    return enableWallhackS;
}

bool getGlowEnabled(){
    return enableWallhackG;
}

bool getOutlineEnabled(){
    return enableWallhackO;
}

bool getRainbowEnabled(){
    return enableRainbow;
}
bool getRainbow1Enabled(){
    return enableRainbow1;
}

int (*old_glGetUniformLocation)(GLuint, const GLchar *);
GLint new_glGetUniformLocation(GLuint program, const GLchar *name) {
    return old_glGetUniformLocation(program, name);
}

bool isCurrentShader(const char *shader) {
    GLint currProgram;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);
    return old_glGetUniformLocation(currProgram, shader) != -1;
}

void (*old_glDrawElements)(GLenum mode, GLsizei count, GLenum type, const void *indices);
void new_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices) {
    old_glDrawElements(mode, count, type, indices);
    if (mode != GL_TRIANGLES || count < 1000) return;
    {
        GLint currProgram;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);

        GLint id = old_glGetUniformLocation(currProgram, getShader());
        if (id == -1) return;

        if (getWireframeEnabled()) {
			
            if (enableWallhackW) {
                glDepthRangef(1, 0.5);
            }
            else {
                glDepthRangef(0.5, 1);
            }
            glBlendColor(GLfloat(r/255), GLfloat(g/255), GLfloat(b/255), 1);
            glColorMask(1, 1, 1, 1);
            glEnable(GL_BLEND);
            glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
            glLineWidth(w);
            old_glDrawElements(GL_LINE_LOOP, count, type, indices);
        }


        if (getWallhackEnabled()) {
			glDepthRangef(1, 0.5);
			glBlendColor(GLfloat(r/255), GLfloat(g/255), GLfloat(b/255), GLfloat(a/255));
            glColorMask(r, g, b, 255);
            glEnable(GL_BLEND);
            glBlendFunc(GL_CONSTANT_ALPHA, GL_CONSTANT_COLOR);
        }

        if (getGlowEnabled()) {
            glEnable(GL_BLEND);
            glBlendColor(GLfloat(r/255), GLfloat(g/255), GLfloat(b/255), 1);
            glColorMask(1, 1, 1, 1);
            glEnable(GL_BLEND);
            glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
            glLineWidth(6);
            glDepthRangef(0.5, 1);
            old_glDrawElements(GL_LINES, count, type, indices);
            glBlendColor(1, 1, 1, 1);
            glDepthRangef(1, 0.5);
            old_glDrawElements(GL_TRIANGLES, count, type, indices);
        }
		
		if (getShadingEnabled()) {
           glDepthRangef(1, 0.5);
           glEnable(GL_BLEND);
           glBlendFunc(GL_SRC_COLOR, GL_CONSTANT_COLOR);
           glBlendEquation(GL_FUNC_ADD);
           glBlendColor(GLfloat(r/255), GLfloat(g/255), GLfloat(b/255), 1);
           glDepthFunc(GL_ALWAYS);
           old_glDrawElements(GL_TRIANGLES, count, type, indices);
           glColorMask(r, g, b, 255);
           glBlendFunc(GL_DST_COLOR, GL_ONE);
           glDepthFunc(GL_LESS);
           glBlendColor(0.0, 0.0, 0.0, 0.0);
        }

        if (getOutlineEnabled()) {
            glDepthRangef(1, 0);
            glLineWidth(ow);
            glEnable(GL_BLEND);
            glColorMask(1, 1, 1, 1);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
            glBlendColor(0, 0, 0, 1);
            old_glDrawElements(GL_TRIANGLES, count, type, indices);
            glBlendColor(GLfloat(r/100), GLfloat(g/100), GLfloat(b/100), 1);
            glDepthRangef(1, 0.5);
            glBlendColor(GLfloat(float(r)/255), GLfloat(float(g)/255), GLfloat(float(b)/255), 1);
            old_glDrawElements(GL_LINES, count, type, indices);
        }

        if (getRainbowEnabled()) {
	        if(getRainbow1Enabled){
               if (red == 255){
                   if (blue == 0 ){
                       if (gren == 255){} else{
                           gren = gren+1;
                       }
                   }
               }
               if (gren == 255){
                   if (red == 0){} else{
                       red = red-1;
                   }
               }
               if (gren == 255) {
                   if (red == 0) {
                       if (blue==255){} else{
                           blue = blue+1;
                       }
                   }
               }
               if (blue == 255) {
                   if (gren == 0) {
                       mi = 1;
                       red = red+1;
                   } 
				   else{
                        gren = gren-1;
                   }
               }
               if (mi == 1){
                   if (red == 255){
                       if (blue == 0){} else{
                           blue = blue-1;
                       }
                   }
               }
               SetR(red);
               SetG(gren);
               SetB(blue);
            }
            glBlendColor(GLfloat(r/255), GLfloat(g/255), GLfloat(b/255), GLfloat(a/255));
            glColorMask(1, 1, 1, 1);
            glEnable(GL_BLEND);
			glDepthRangef(1, 0.5);
            glBlendFunc(GL_ONE_MINUS_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_ALPHA);
        }
        old_glDrawElements(mode, count, type, indices);

        glDepthRangef(0.5, 1);

        glColorMask(1, 1, 1, 1);
        glDisable(GL_BLEND);
    }
}

bool mlovinit(){
    handle = NULL;
    handle = dlopen("libGLESv2.so", RTLD_LAZY);
    if(!handle){
        //LOGE("Cannot open library: %s", dlerror());
        return false;
    }
    return true;
}

void LogShaders(){
    auto p_glGetUniformLocation = (const void*(*)(...))dlsym(handle, "glGetUniformLocation");
    const char *dlsym_error = dlerror();
    if(dlsym_error){
        //LOGE("Cannot load symbol 'glGetUniformLocation': %s", dlsym_error);
        return;
    }else{
        MSHookFunction(reinterpret_cast<void*>(p_glGetUniformLocation), reinterpret_cast<void*>(new_glGetUniformLocation), reinterpret_cast<void**>(&old_glGetUniformLocation));
    }
}

void Wallhack(){
    auto p_glDrawElements = (const void*(*)(...))dlsym(handle, "glDrawElements");
    const char *dlsym_error = dlerror();
    if(dlsym_error){
        //LOGE("Cannot load symbol 'glDrawElements': %s", dlsym_error);
        return;
    }else{
        MSHookFunction(reinterpret_cast<void*>(p_glDrawElements), reinterpret_cast<void*>(new_glDrawElements), reinterpret_cast<void**>(&old_glDrawElements));
    }
}

#endif
