#pragma once

#include "rdeclare.h"
#include "robject.h"
#include "ukey.h"

void _UWindowCount (); //() -> void
void _UWindowAt    (); //(int index) -> void
void _UWindowRemove(); //(int id) -> void

void _UWindowTitle     (); //() -> string
void _UWindowIdentifier(); //() -> string
void _UWindowCreate    (); //() -> void
void _UWindowShow      (); //() -> void
void _UWindowHide      (); //() -> void
void _UWindowDestroy   (); //() -> void

void _UWindowCursorBegin(); //(float x, float y) -> void
void _UWindowCursorWheel(); //(float x, float y, float delta) -> void
void _UWindowCursorRight(); //(float x, float y) -> void
void _UWindowCursorMove (); //(float x, float y, bool downed) -> void
void _UWindowCursorDown (); //(float x, float y) -> void
void _UWindowCursorUp   (); //(float x, float y) -> void
void _UWindowCursorEnd  (); //(float x, float y) -> void

void _UWindowKey(); //(int key, int modifiers) -> void

void _UWindowFieldVisible (); //() -> bool
void _UWindowFieldX       (); //() -> float
void _UWindowFieldY       (); //() -> float
void _UWindowFieldWidth   (); //() -> float
void _UWindowFieldHeight  (); //() -> float
void _UWindowFieldSetText (); //(string text) -> void
void _UWindowFieldText    (); //() -> string
void _UWindowFieldSetFocus(); //(bool focus) -> void
void _UWindowFieldFocus   (); //() -> bool

void _UWindowResize(); //(float w, float h) -> void
void _UWindowGLDraw(); //() -> void
void _UWindowDraw  (); //() -> void

declare_reflectable_class(UWindow)
class UWindow : dash::extends<UWindow, reflect::object> {
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

    bool        fieldVisiable();
    float       fieldX       ();
    float       fieldY       ();
    float       fieldWidth   ();
    float       fieldHeight  ();
    std::string fieldText    ();
    bool        fieldFocus   ();

    bool  cursorBegan ();
    bool  cursorDowned();
    float cursorX     ();
    float cursorY     ();

public:
    void _handleCreate ();
    void _handleShow   ();
    void _handleHide   ();
    void _handleDestroy();

    void _handleCursorBegin(float x, float y);
    void _handleCursorWheel(float x, float y, float delta);
    void _handleCursorRight(float x, float y);
    void _handleCursorMove (float x, float y, bool downed);
    void _handleCursorDown (float x, float y);
    void _handleCursorUp   (float x, float y);
    void _handleCursorEnd  (float x, float y);

    void _handleKey(UKey key, UModifiers modifiers, char ch);

    void _handleFieldText (const std::string &text);
    void _handleFieldFocus(bool focus);

    void _handleResize(float w, float h);
    void _handleGLDraw();
    void _handleDraw  ();

protected:
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
