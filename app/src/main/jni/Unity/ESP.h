#ifndef ESP_H
#define ESP_H

#include <jni.h>
//#include "Color.h"
#include "Rect.h"
#include "Vector3.h"
#include "Vector33.hpp"
#include "Vector2.h"
#include <math.h>
class Rect {
public:
    float x;
    float y;
    float w;
    float h;
    Rect()
            : x(0)
            , y(0)
            , w(0)
            , h(0)
    {
    }
    Rect(float x1, float y1, float w1, float h1)
            : x(x1)
            , y(y1)
            , w(w1)
            , h(h1)
    {
    }
    Rect(const Rect& v);
    ~Rect();
};
Rect::Rect(const Rect& v)
        : x(v.x)
        , y(v.y)
        , w(v.w)
        , h(v.h)
{
}
Rect::~Rect() {}
class Color {
public:
    float r, b, g, a;

    Color() {
        SetColor( 0 , 0 , 0 , 255 );
    }

    Color( float r , float g , float b ) {
        SetColor( r , g , b , 255 );
    }

    Color( float r, float g, float b, float a) {
        SetColor( r , g , b , a );
    }

    void SetColor( float r1 , float g1 , float b1 , float a1 = 255 ) {
        r = r1;
        g = g1;
        b = b1;
        a = a1;
    }

    static Color Black(float a = 255){ return Color(0, 0, 0, a); }
    static Color White(float a = 255){ return Color(255 , 255 , 255, a); }
    static Color Red(float a = 255){ return Color(255 , 0 , 0, a); }
    static Color Green(float a = 255){ return Color(0 , 255 , 0, a); }
    static Color Blue(float a = 255){ return Color(0 , 0 , 255, a); }
    static Color Yellow(float a = 255){ return Color(255 , 255 , 0, a); }
    static Color Cyan(float a = 255){ return Color(0 , 255 , 255, a); }
    static Color Naranja(float a = 255){ return Color(255, 215 , 0, a); }
    static Color Magenta(float a = 255){ return Color(255 , 0 , 255, a); }
};

class ESP {
private:
    JNIEnv *_env;
    jobject _cvsView;
    jobject _cvs;

public:
    ESP() {
        _env = nullptr;
        _cvsView = nullptr;
        _cvs = nullptr;
    }

    ESP(JNIEnv *env, jobject cvsView, jobject cvs) {
        this->_env = env;
        this->_cvsView = cvsView;
        this->_cvs = cvs;
    }

    bool isValid() const {
        return (_env != nullptr && _cvsView != nullptr && _cvs != nullptr);
    }

    int getWidth() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getWidth", "()I");
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }

    int getHeight() const {
        if (isValid()) {
            jclass canvas = _env->GetObjectClass(_cvs);
            jmethodID width = _env->GetMethodID(canvas, "getHeight", "()I");
            return _env->CallIntMethod(_cvs, width);
        }
        return 0;
    }
    void DrawAlvo(Color color, float thickness, Vector2 start, Vector2 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawLine",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.X, start.Y, end.X, end.Y);
        }
    }

    void DrawLine(Color color, float thickness, Vector2 start, Vector2 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawLine",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.X, start.Y, end.X, end.Y);
        }
    }

    void DrawCornerBox(Color color, Rect rect) {

        DrawLine(color, 2.5f, Vector2(rect.x, rect.y), Vector2((rect.x + (rect.w / 3)), rect.y));
        DrawLine(color, 2.5f, Vector2(rect.x + rect.w, rect.y),
                 Vector2((rect.x + rect.w) - (rect.w / 3), rect.y));

        DrawLine(color, 2.5f, Vector2(rect.x, rect.y + rect.h),
                 Vector2((rect.x + (rect.w / 3)), rect.y + rect.h));
        DrawLine(color, 2.5f, Vector2(rect.x + rect.w, rect.y + rect.h),
                 Vector2(((rect.x + rect.w) - (rect.w / 3)), rect.y + rect.h));

        DrawLine(color, 2.5f, Vector2(rect.x, rect.y), Vector2(rect.x, rect.y + (rect.h / 6)));
        DrawLine(color, 2.5f, Vector2(rect.x + rect.w, rect.y),
                 Vector2(rect.x + rect.w, rect.y + (rect.h / 6)));

        DrawLine(color, 2.5f, Vector2(rect.x, rect.y + rect.h),
                 Vector2(rect.x, (rect.y + rect.h) - (rect.h / 6)));
        DrawLine(color, 2.5f, Vector2(rect.x + rect.w, rect.y + rect.h),
                 Vector2(rect.x + rect.w, (rect.y + rect.h) - (rect.h / 6)));
    }

    void DrawLine2(Color color, float thickness, Vector33 start, Vector33 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawLine",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.X, start.Y, end.X, end.Y);
        }
    }


    void DrawLine2(Color color, float thickness, Vector2 start, Vector2 end) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawline = _env->GetMethodID(canvasView, "DrawLine",
                                                   "(Landroid/graphics/Canvas;IIIIFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawline, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 thickness,
                                 start.X, start.Y, end.X, end.Y);
        }
    }

    void DrawVerticalHealth(Vector2 end, float h, float health) {

        float x = end.X;
        float y = end.Y;
        h = -h;

        Color clr = Color(0, 255, 0, 255);

        float hpwidth = h-h*health/100;

        if (health <= (100 * 0.6)) {
            clr = Color(255, 255, 0, 255);
        }
        if (health < (100 * 0.3)) {
            clr = Color(255, 0, 0, 255);
        }

        Rect hpbar((x+h/4)-8,y,4.0f,-h);
        Rect hp((x+h/4)-8,y-hpwidth,2.0f,-h+hpwidth);

        DrawBox(Color(0,0,0,255), 3, hpbar);

        DrawBox(clr,3, hp);

    }

    void DrawText(Color color, float stroke, std::string str, Vector2 pos, float size) {
        
		if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawText",
                                                   "(Landroid/graphics/Canvas;IIIIFLjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,stroke,
                                 _env->NewStringUTF(str.c_str()), pos.X, pos.Y, size);
        }
    }

    void DrawTextSS(Color color, const char *txt, Vector2 pos, float size, bool shd) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawText",
                                                   "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFFZ)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 _env->NewStringUTF(txt), pos.X, pos.Y, size, shd);
        }
    }
    
     
      
      void DrawTextFFFFF(Color color, const char *txt, Vector2 pos, float size) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawText",
                                                   "(Landroid/graphics/Canvas;IIIILjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,
                                 _env->NewStringUTF(txt), pos.X, pos.Y, size);
        }
    }  
         void DrawTextX(Color color, float stroke, std::string str, Vector2 pos, float size) {

        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawText",
                                                   "(Landroid/graphics/Canvas;IIIIFLjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,stroke,
                                 _env->NewStringUTF(str.c_str()), pos.X, pos.Y, size);
        }
    }
    
	void DrawName(Color color, float stroke, std::string str, Vector3 pos, float size) {
        
		if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawtext = _env->GetMethodID(canvasView, "DrawName",
                                                   "(Landroid/graphics/Canvas;IIIIFLjava/lang/String;FFF)V");
            _env->CallVoidMethod(_cvsView, drawtext, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b,stroke,
                                 _env->NewStringUTF(str.c_str()), pos.x, pos.y, size);
        }
    }
	
    void DrawFilledCircle(Color color, Vector2 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawfilledcircle = _env->GetMethodID(canvasView, "DrawFilledCircle",
                                                           "(Landroid/graphics/Canvas;IIIIFFF)V");
            _env->CallVoidMethod(_cvsView, drawfilledcircle, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.X, pos.Y, radius);
        }
    }
	
	
	

	void DrawCircle(Color Color,float stroke, Vector2 pos, float radius) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawcircle = _env->GetMethodID(canvasView, "DrawCircle",
                                                     "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawcircle, _cvs, (int) Color.a, (int) Color.r,
                                 (int) Color.g, (int) Color.b,stroke, pos.X, pos.Y, radius);
        }
    }
	
	
	
	
	void DrawFilledRect(Color color, Vector2 pos, float width, float height) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawfilledrect = _env->GetMethodID(canvasView, "DrawFilledRect",
                                                         "(Landroid/graphics/Canvas;IIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawfilledrect, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.X, pos.Y, width, height);
        }
    }

    void DrawRect(Color color, float stroke, Vector2 pos, float width, float height) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawrect = _env->GetMethodID(canvasView, "DrawRect",
                                                           "(Landroid/graphics/Canvas;IIIIIFFFF)V");
            _env->CallVoidMethod(_cvsView, drawrect, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, stroke, pos.X, pos.Y, width, height);
        }
    }

    void DrawEspBoxGradient(Color color, Vector2 pos, float width, float height, float radious, float stroke) {
        if (isValid()) {
            jclass canvasView = _env->GetObjectClass(_cvsView);
            jmethodID drawrect = _env->GetMethodID(canvasView, "DrawEspBoxGradient",
                                                           "(Landroid/graphics/Canvas;IIIIFFFFFF)V");
            _env->CallVoidMethod(_cvsView, drawrect, _cvs, (int) color.a, (int) color.r,
                                 (int) color.g, (int) color.b, pos.X, pos.Y, width, height, radious, stroke);
        }
    }
	
    void DrawBox(Color color, float stroke, Rect rect) {
        Vector2 v1 = Vector2(rect.x, rect.y);
        Vector2 v2 = Vector2(rect.x + rect.w, rect.y);
        Vector2 v3 = Vector2(rect.x + rect.w, rect.y + rect.h);
        Vector2 v4 = Vector2(rect.x, rect.y + rect.h);

        DrawLine(color, stroke, v1, v2); // LINE UP
        DrawLine(color, stroke, v2, v3); // LINE RIGHT
        DrawLine(color, stroke, v3, v4); // LINE DOWN
        DrawLine(color, stroke, v4, v1); // LINE LEFT
    }


    void DrawBox3D(Rect rect, Rect rect2, float stroke, Color color){

        Vector33 v1 = Vector33(rect.x, rect.y);
        Vector33 v2 = Vector33(rect.x + rect.w, rect.y);
        Vector33 v3 = Vector33(rect.x + rect.w, rect.y + rect.h);
        Vector33 v4 = Vector33(rect.x, rect.y + rect.h);

        Vector33 vv1 = Vector33(rect2.x, rect2.y);
        Vector33 vv2 = Vector33(rect2.x + rect2.w, rect2.y);
        Vector33 vv3 = Vector33(rect2.x + rect2.w, rect2.y + rect2.h);
        Vector33 vv4 = Vector33(rect2.x, rect2.y + rect2.h);

        DrawLine2(color, stroke, v1, v2); // LINE UP
        DrawLine2(color, stroke, v2, v3); // LINE RIGHT
        DrawLine2(color, stroke, v3, v4); // LINE DOWN
        DrawLine2(color, stroke, v4, v1); // LINE LEFT


        DrawLine2(color, stroke, vv1, vv2); // LINE UP
        DrawLine2(color, stroke, vv2, vv3); // LINE RIGHT
        DrawLine2(color, stroke, vv3, vv4); // LINE DOWN
        DrawLine2(color, stroke, vv4, vv1); // LINE LEFT


        DrawLine2(color, stroke, vv1, v1); // LINE UP
        DrawLine2(color, stroke, vv2, v2); // LINE RIGHT
        DrawLine2(color, stroke, vv3, v3); // LINE DOWN
        DrawLine2(color, stroke, vv4, v4); // LINE LEFT



    }

    void DrawCrosshair(Color clr, Vector2 center, float size = 20) {
        float x = center.X - (size / 2.0f);
        float y = center.Y - (size / 2.0f);
        DrawLine(clr, 3, Vector2(x, center.Y), Vector2(x + size, center.Y));
        DrawLine(clr, 3, Vector2(center.X, y), Vector2(center.X, y + size));
    }
};

int isOutsideSafezone(Vector2 pos, Vector2 screen) {
    Vector2 mSafezoneTopLeft(screen.X * 0.04f, screen.Y * 0.04f);
    Vector2 mSafezoneBottomRight(screen.X * 0.96f, screen.Y * 0.96f);

    int result = 0;
    if (pos.Y < mSafezoneTopLeft.Y) {
        result |= 1;
    }
    if (pos.X > mSafezoneBottomRight.X) {
        result |= 2;
    }
    if (pos.Y > mSafezoneBottomRight.Y) {
        result |= 4;
    }
    if (pos.X < mSafezoneTopLeft.X) {
        result |= 8;
    }
    return result;
}

Vector2 pushToScreenBorder(Vector2 Pos, Vector2 screen, int borders, int offset) {
    int x = (int)Pos.X;
    int y = (int)Pos.Y;
    if ((borders & 1) == 1) {
        y = 0 - offset;
    }
    if ((borders & 2) == 2) {
        x = (int)screen.X + offset;
    }
    if ((borders & 4) == 4) {
        y = (int)screen.Y + offset;
    }
    if ((borders & 8) == 8) {
        x = 0 - offset;
    }
    return Vector2(x, y);
}

#endif
