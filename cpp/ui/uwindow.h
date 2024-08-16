#pragma once

#include "rdeclare.h"
#include "robject.h"
#include "ukey.h"

declare_reflectable_class(UWindow)
class UWindow : dash::extends<UWindow, reflect::object> {
public:
    void setTitle(const std::string &title);
    std::string title();

    void setMark(const std::string &mark);
    std::string mark();

    void showWindow();

    bool  created();
    bool  shown  ();
    float width  ();
    float height ();

    void setFieldVisible(bool visible);
    void setFieldRect   (float x, float y, float w, float h);
    void setFieldText   (const std::string &text);
    void setFieldFocus  (bool focus);

    bool        fieldVisiable();
    float       fieldX       ();
    float       fieldY       ();
    float       fieldWidth   ();
    float       fieldHeight  ();
    std::string fieldText    ();
    bool        fieldFocus   ();

    bool  mouseBegan ();
    bool  mouseDowned();
    float mouseX     ();
    float mouseY     ();

protected:
    virtual void onCreate ();
    virtual void onShow   ();
    virtual void onHide   ();
    virtual void OnDestroy();

    virtual void onMouseBegin(float x, float y);
    virtual void onMouseWheel(float x, float y, float delta);
    virtual void onMouseMove (float x, float y, bool downed);
    virtual void onMouseDown (float x, float y);
    virtual void onMouseUp   (float x, float y);
    virtual void onMouseEnd  (float x, float y);

    virtual void onKey(UKey key, UModifiers modifiers);

    virtual void onFieldText (const std::string &text);
    virtual void onFieldFocus(bool focus);

    virtual void onResize(float w, float h);
    virtual void onGLDraw();
    virtual void onDraw  ();

private:
    std::string mTitle = "";
    std::string mMark  = "";

    bool  mCreated = false;
    bool  mShown   = false;
    float mWidth   = 0;
    float mHeight  = 0;

    float       mFieldVisible = false;
    float       mFieldX       = 0;
    float       mFieldY       = 0;
    float       mFieldWidth   = 0;
    float       mFieldHeight  = 0;
    std::string mFieldText    = "";
    bool        mFieldFocus   = false;

    bool  mMouseBegan  = false;
    bool  mMouseDowned = false;
    float mMouseX      = 0;
    float mMouseY      = 0;
};
