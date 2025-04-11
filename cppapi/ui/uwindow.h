#pragma once

#include "rdeclare.h"
#include "rinjectable.h"
#include "ukey.h"

// host api.
//

void _UWindowCreate (int id, const std::string &session);
void _UWindowShow   (int id);
void _UWindowHide   (int id);
void _UWindowDestroy(int id);

void _UWindowSetTitle(int id, const std::string &title);

void _UWindowSetFieldVisible(int id, bool visible);
void _UWindowSetFieldFocus  (int id, bool focus);
void _UWindowSetFieldRect   (int id, float x, float y, float w, float h);
void _UWindowSetFieldText   (int id, const std::string &text);

// window callback.
//

void _UWindowNotifyShow   (int id);
void _UWindowNotifyHide   (int id);
void _UWindowNotifyDestroy(int id);

void _UWindowNotifyCursorWheel(int id, float x, float y, float delta);
void _UWindowNotifyCursorRight(int id, float x, float y);
void _UWindowNotifyCursorMove (int id, float x, float y);
void _UWindowNotifyCursorDown (int id, float x, float y);
void _UWindowNotifyCursorUp   (int id, float x, float y);

void _UWindowNotifyKey(int id, int key, int modifiers);

void _UWindowNotifyFieldFocus(int id, bool focus);
void _UWindowNotifyFieldText (int id, const std::string &text);

void _UWindowNotifyResize(int id, float w, float h);
void _UWindowNotifyGLDraw(int id);
void _UWindowNotifyDraw  (int id);

// window class.
//

declare_reflectable_class(UWindow)
class UWindow : public dash::extends<UWindow, reflect::injectable> {
public:
    void setSession(const std::string &session);
    std::string session();

    void setTitle(const std::string &title);
    std::string title();

    void createWindow ();
    void showWindow   ();
    void hideWindow   ();
    void destroyWindow();

    bool created  ();
    bool shown    ();
    bool destroyed();

    float width ();
    float height();

    bool  cursorActive();
    bool  cursorDowned();
    float cursorX     ();
    float cursorY     ();

    void  setFieldVisible(bool visible);
    void  setFieldFocus  (bool focus);
    void  setFieldRect   (float x, float y, float w, float h);
    void  setFieldText   (const std::string &text);
    bool  fieldVisible   ();
    bool  fieldFocus     ();
    float fieldX         ();
    float fieldY         ();
    float fieldWidth     ();
    float fieldHeight    ();

    std::string fieldText();

public:
    virtual void onCreate ();
    virtual void onShow   ();
    virtual void onHide   ();
    virtual void onDestroy();

    virtual void onCursorWheel(float x, float y, float delta);
    virtual void onCursorRight(float x, float y);
    virtual void onCursorMove (float x, float y, bool downed);
    virtual void onCursorDown (float x, float y);
    virtual void onCursorUp   (float x, float y);

    virtual void onKey(UKey key, UModifiers modifiers, char ch);

    virtual void onFieldFocus(bool focus);
    virtual void onFieldText (const std::string &text);

    virtual void onResize(float w, float h);
    virtual void onGLDraw();
    virtual void onDraw  ();

public:
    void _notifyShow   ();
    void _notifyHide   ();
    void _notifyDestroy();

    void _notifyCursorWheel(float x, float y, float delta);
    void _notifyCursorRight(float x, float y);
    void _notifyCursorMove (float x, float y);
    void _notifyCursorDown (float x, float y);
    void _notifyCursorUp   (float x, float y);

    void _notifyKey(UKey key, UModifiers modifiers);

    void _notifyFieldFocus(bool focus);
    void _notifyFieldText (const std::string &text);

    void _notifyResize(float w, float h);
    void _notifyGLDraw();
    void _notifyDraw  ();

private:
    std::string mSession;
    std::string mTitle;

    bool  mCreated   = false;
    bool  mShown     = false;
    bool  mDestroyed = false;

    float mWidth  = 0;
    float mHeight = 0;

    bool  mCursorActive = false;
    bool  mCursorDowned = false;
    float mCursorX      = 0;
    float mCursorY      = 0;

    bool  mFieldVisible = false;
    bool  mFieldFocus   = false;
    float mFieldX       = 0;
    float mFieldY       = 0;
    float mFieldWidth   = 0;
    float mFieldHeight  = 0;

    std::string mFieldText;
};
