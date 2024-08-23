#pragma once

#include "rdeclare.h"
#include "rinjectable.h"
#include "ukey.h"

void _UWindowCount (); //() -> void
void _UWindowAt    (); //(int index) -> void
void _UWindowRemove(); //(int id) -> void

void _UWindowTitle        (); //() -> string
void _UWindowIdentifier   (); //() -> string
void _UWindowNotifyCreate (); //() -> void
void _UWindowNotifyShow   (); //() -> void
void _UWindowNotifyHide   (); //() -> void
void _UWindowNotifyDestroy(); //() -> void

void _UWindowNotifyCursorBegin(); //(float x, float y) -> void
void _UWindowNotifyCursorWheel(); //(float x, float y, float delta) -> void
void _UWindowNotifyCursorRight(); //(float x, float y) -> void
void _UWindowNotifyCursorMove (); //(float x, float y, bool downed) -> void
void _UWindowNotifyCursorDown (); //(float x, float y) -> void
void _UWindowNotifyCursorUp   (); //(float x, float y) -> void
void _UWindowNotifyCursorEnd  (); //(float x, float y) -> void

void _UWindowNotifyKey(); //(int key, int modifiers) -> void

void _UWindowFieldVisible (); //() -> bool
void _UWindowFieldX       (); //() -> float
void _UWindowFieldY       (); //() -> float
void _UWindowFieldWidth   (); //() -> float
void _UWindowFieldHeight  (); //() -> float
void _UWindowFieldSetText (); //(string text) -> void
void _UWindowFieldText    (); //() -> string
void _UWindowFieldSetFocus(); //(bool focus) -> void
void _UWindowFieldFocus   (); //() -> bool

void _UWindowNotifyResize(); //(float w, float h) -> void
void _UWindowNotifyGLDraw(); //() -> void
void _UWindowNotifyDraw  (); //() -> void

declare_reflectable_class(UWindow)
class UWindow : public dash::extends<UWindow, reflect::injectable> {
public:
    void setTitle(const std::string &title);
    std::string title();

    void setIdentifier(const std::string &identifier);
    std::string identifier();

    void showWindow();

    bool  created();
    bool  shown  ();
    float width  ();
    float height ();

    void setFieldVisible(bool visible);
    void setFieldRect   (float x, float y, float w, float h);
    void setFieldText   (const std::string &text);
    void setFieldFocus  (bool focus);

    bool        fieldVisible();
    float       fieldX      ();
    float       fieldY      ();
    float       fieldWidth  ();
    float       fieldHeight ();
    std::string fieldText   ();
    bool        fieldFocus  ();

    bool  cursorBegan ();
    bool  cursorDowned();
    float cursorX     ();
    float cursorY     ();

public:
    virtual void onCreate ();
    virtual void onShow   ();
    virtual void onHide   ();
    virtual void OnDestroy();

    virtual void onCursorBegin(float x, float y);
    virtual void onCursorWheel(float x, float y, float delta);
    virtual void onCursorRight(float x, float y);
    virtual void onCursorMove (float x, float y, bool downed);
    virtual void onCursorDown (float x, float y);
    virtual void onCursorUp   (float x, float y);
    virtual void onCursorEnd  (float x, float y);

    virtual void onKey(UKey key, UModifiers modifiers, char ch);

    virtual void onFieldText (const std::string &text);
    virtual void onFieldFocus(bool focus);

    virtual void onResize(float w, float h);
    virtual void onGLDraw();
    virtual void onDraw  ();

public:
    void _notifyCreate ();
    void _notifyShow   ();
    void _notifyHide   ();
    void _notifyDestroy();

    void _notifyCursorBegin(float x, float y);
    void _notifyCursorWheel(float x, float y, float delta);
    void _notifyCursorRight(float x, float y);
    void _notifyCursorMove (float x, float y, bool downed);
    void _notifyCursorDown (float x, float y);
    void _notifyCursorUp   (float x, float y);
    void _notifyCursorEnd  (float x, float y);

    void _notifyKey(UKey key, UModifiers modifiers, char ch);

    void _notifyFieldText (const std::string &text);
    void _notifyFieldFocus(bool focus);

    void _notifyResize(float w, float h);
    void _notifyGLDraw();
    void _notifyDraw  ();

private:
    std::string mTitle      = "";
    std::string mIdentifier = "";

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

    bool  mCursorBegan  = false;
    bool  mCursorDowned = false;
    float mCursorX      = 0;
    float mCursorY      = 0;
};
