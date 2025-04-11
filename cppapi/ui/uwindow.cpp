#include "uwindow.h"
#include <map>
#include <vector>
#include "dlazy.h"
#include "lcall.h"
#include "lcpp.h"
#include "lreg.h"
#include "rdefine.h"

static dash::lazy<std::map<int, UWindow::ptr>> gWindows;

static void UWindowRegister(int id, const UWindow::ptr &window) {
    gWindows->insert({ id, window });
}

static int UWindowID(const UWindow *window) {
    return (int)(intptr_t)window;
}

static UWindow::ptr UWindowGet(int id) {
    auto it = gWindows->find(id);
    if (it != gWindows->end()) {
        return it->second;
    }
    return nullptr;
}

void _UWindowCreate(int id, const std::string &session) {
    low::i[0] = id;
    low::s[1] = session;

    low::call("_UWindowCreate");
}

void _UWindowShow(int id) {
    low::i[0] = id;

    low::call("_UWindowShow");
}

void _UWindowHide(int id) {
    low::i[0] = id;

    low::call("_UWindowHide");
}

void _UWindowDestroy(int id) {
    low::i[0] = id;

    low::call("_UWindowDestroy");
}

void _UWindowSetTitle(int id, const std::string &title) {
    low::i[0] = id;
    low::s[1] = title;

    low::call("_UWindowSetTitle");
}

void _UWindowSetFieldVisible(int id, bool visible) {
    low::i[0] = id;
    low::b[1] = visible;

    low::call("_UWindowSetFieldVisible");
}

void _UWindowSetFieldFocus(int id, bool focus) {
    low::i[0] = id;
    low::b[1] = focus;

    low::call("_UWindowSetFieldFocus");
}

void _UWindowSetFieldRect(int id, float x, float y, float w, float h) {
    low::i[0] = id;
    low::f[1] = x;
    low::f[2] = y;
    low::f[3] = w;
    low::f[4] = h;

    low::call("_UWindowSetFieldRect");
}

void _UWindowSetFieldText(int id, const std::string &text) {
    low::i[0] = id;
    low::s[1] = text;

    low::call("_UWindowSetFieldText");
}

define_low_function(_UWindowNotifyShow)
void _UWindowNotifyShow() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyShow();
    }
}

define_low_function(_UWindowNotifyHide)
void _UWindowNotifyHide() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyHide();
    }
}

define_low_function(_UWindowNotifyDestroy)
void _UWindowNotifyDestroy() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyDestroy();
    }
}

define_low_function(_UWindowNotifyCursorWheel)
void _UWindowNotifyCursorWheel() {
    int   id    = low::i[0];
    float x     = low::f[1];
    float y     = low::f[2];
    float delta = low::f[3];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyCursorWheel(x, y, delta);
    }
}

define_low_function(_UWindowNotifyCursorRight)
void _UWindowNotifyCursorRight() {
    int   id = low::i[0];
    float x  = low::f[1];
    float y  = low::f[2];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyCursorRight(x, y);
    }
}

define_low_function(_UWindowNotifyCursorMove)
void _UWindowNotifyCursorMove() {
    int   id = low::i[0];
    float x  = low::f[1];
    float y  = low::f[2];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyCursorMove(x, y);
    }
}

define_low_function(_UWindowNotifyCursorDown)
void _UWindowNotifyCursorDown() {
    int   id = low::i[0];
    float x  = low::f[1];
    float y  = low::f[2];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyCursorDown(x, y);
    }
}

define_low_function(_UWindowNotifyCursorUp)
void _UWindowNotifyCursorUp() {
    int   id = low::i[0];
    float x  = low::f[1];
    float y  = low::f[2];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyCursorUp(x, y);
    }
}

define_low_function(_UWindowNotifyKey)
void _UWindowNotifyKey() {
    int  id        = /* ... .. */low::i[0];
    auto key       = (UKey      )low::i[1];
    auto modifiers = (UModifiers)low::i[2];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyKey(key, modifiers);
    }
}

define_low_function(_UWindowNotifyFieldFocus)
void _UWindowNotifyFieldFocus() {
    int  id    = low::i[0];
    bool focus = low::b[1];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyFieldFocus(focus);
    }
}

define_low_function(_UWindowNotifyFieldText)
void _UWindowNotifyFieldText() {
    int         id   = low::i[0];
    std::string text = low::s[1];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyFieldText(text);
    }
}

define_low_function(_UWindowNotifyResize)
void _UWindowNotifyResize() {
    int   id = low::i[0];
    float w  = low::f[1];
    float h  = low::f[2];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyResize(w, h);
    }
}

define_low_function(_UWindowNotifyGLDraw)
void _UWindowNotifyGLDraw() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyGLDraw();
    }
}

define_low_function(_UWindowNotifyDraw)
void _UWindowNotifyDraw() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyDraw();
    }
}

define_reflectable_class_function(UWindow, setSession, "args:session")
void UWindow::setSession(const std::string &session) {
    mSession = session;
}

define_reflectable_class_function(UWindow, session)
std::string UWindow::session() {
    return mSession;
}

define_reflectable_class_function(UWindow, setTitle, "args:title")
void UWindow::setTitle(const std::string &title) {
    if (mTitle == title) {
        return;
    }

    if (mCreated) {
        _UWindowSetTitle(UWindowID(this), title);
    }
    mTitle = title;
}

define_reflectable_class_function(UWindow, title)
std::string UWindow::title() {
    return mTitle;
}

define_reflectable_class_function(UWindow, createWindow)
void UWindow::createWindow() {
    if (mCreated) {
        return;
    }

    UWindowRegister(UWindowID(this), me());

    _UWindowCreate         (UWindowID(this), mSession);
    _UWindowSetTitle       (UWindowID(this), mTitle);
    _UWindowSetFieldVisible(UWindowID(this), mFieldVisible);
    _UWindowSetFieldRect   (UWindowID(this), mFieldX, mFieldY, mFieldWidth, mFieldHeight);
    _UWindowSetFieldText   (UWindowID(this), mFieldText);

    mCreated = true;
    onCreate();
}

define_reflectable_class_function(UWindow, showWindow)
void UWindow::showWindow() {
    if (mShown) {
        return;
    }

    //make sure the window is created.
    createWindow();

    _UWindowShow(UWindowID(this));
}

define_reflectable_class_function(UWindow, hideWindow)
void UWindow::hideWindow() {
    if (! mShown) {
        return;
    }

    _UWindowHide(UWindowID(this));
}

define_reflectable_class_function(UWindow, destroyWindow)
void UWindow::destroyWindow() {
    if (mDestroyed) {
        return;
    }

    mDestroyed = true;
    onDestroy();

    _UWindowDestroy(UWindowID(this));
}

define_reflectable_class_function(UWindow, created  )
define_reflectable_class_function(UWindow, shown    )
define_reflectable_class_function(UWindow, destroyed)

bool UWindow::created  () { return mCreated  ; }
bool UWindow::shown    () { return mShown    ; }
bool UWindow::destroyed() { return mDestroyed; }

define_reflectable_class_function(UWindow, width )
define_reflectable_class_function(UWindow, height)

float UWindow::width () { return mWidth ; }
float UWindow::height() { return mHeight; }

define_reflectable_class_function(UWindow, cursorActive)
define_reflectable_class_function(UWindow, cursorDowned)
define_reflectable_class_function(UWindow, cursorX     )
define_reflectable_class_function(UWindow, cursorY     )

bool  UWindow::cursorActive() { return mCursorActive; }
bool  UWindow::cursorDowned() { return mCursorDowned; }
float UWindow::cursorX     () { return mCursorX     ; }
float UWindow::cursorY     () { return mCursorY     ; }

define_reflectable_class_function(UWindow, setFieldVisible, "args:visible")
void UWindow::setFieldVisible(bool visible) {
    if (mFieldVisible == visible) {
        return;
    }

    _UWindowSetFieldVisible(UWindowID(this), visible);
    mFieldVisible = visible;
}

define_reflectable_class_function(UWindow, setFieldFocus, "args:focus")
void UWindow::setFieldFocus(bool focus) {
    if (! mCreated) {
        return;
    }
    if (mFieldFocus == focus) {
        return;
    }

    _UWindowSetFieldFocus(UWindowID(this), focus);
}

define_reflectable_class_function(UWindow, setFieldRect, "args:x,y,w,h")
void UWindow::setFieldRect(float x, float y, float w, float h) {
    if (mFieldX == x && mFieldWidth  == w &&
        mFieldY == y && mFieldHeight == h )
    {
        return;
    }

    _UWindowSetFieldRect(UWindowID(this), x, y, w, h);

    mFieldX      = x;
    mFieldY      = y;
    mFieldWidth  = w;
    mFieldHeight = h;
}

define_reflectable_class_function(UWindow, setFieldText, "args:text")
void UWindow::setFieldText(const std::string &text) {
    if (mFieldText == text) {
        return;
    }

    _UWindowSetFieldText(UWindowID(this), text);

    mFieldText = text;
    onFieldText(text);
}

define_reflectable_class_function(UWindow, fieldVisible)
define_reflectable_class_function(UWindow, fieldFocus  )
define_reflectable_class_function(UWindow, fieldX      )
define_reflectable_class_function(UWindow, fieldY      )
define_reflectable_class_function(UWindow, fieldWidth  )
define_reflectable_class_function(UWindow, fieldHeight )

bool  UWindow::fieldVisible() { return mFieldVisible; }
bool  UWindow::fieldFocus  () { return mFieldFocus  ; }
float UWindow::fieldX      () { return mFieldX      ; }
float UWindow::fieldY      () { return mFieldY      ; }
float UWindow::fieldWidth  () { return mFieldWidth  ; }
float UWindow::fieldHeight () { return mFieldHeight ; }

define_reflectable_class_function(UWindow, fieldText)
std::string UWindow::fieldText() {
    return mFieldText;
}

define_reflectable_class_function(UWindow, onCreate )
define_reflectable_class_function(UWindow, onShow   )
define_reflectable_class_function(UWindow, onHide   )
define_reflectable_class_function(UWindow, onDestroy)

void UWindow::onCreate () { implement_injectable_function(void) }
void UWindow::onShow   () { implement_injectable_function(void) }
void UWindow::onHide   () { implement_injectable_function(void) }
void UWindow::onDestroy() { implement_injectable_function(void) }

define_reflectable_class_function(UWindow, onCursorWheel, "args:x,y,delta" )
define_reflectable_class_function(UWindow, onCursorRight, "args:x,y"       )
define_reflectable_class_function(UWindow, onCursorMove , "args:x,y,downed")
define_reflectable_class_function(UWindow, onCursorDown , "args:x,y"       )
define_reflectable_class_function(UWindow, onCursorUp   , "args:x,y"       )

void UWindow::onCursorWheel(float x, float y, float delta) { implement_injectable_function(void, x, y, delta ) }
void UWindow::onCursorRight(float x, float y)              { implement_injectable_function(void, x, y        ) }
void UWindow::onCursorMove (float x, float y, bool downed) { implement_injectable_function(void, x, y, downed) }
void UWindow::onCursorDown (float x, float y)              { implement_injectable_function(void, x, y        ) }
void UWindow::onCursorUp   (float x, float y)              { implement_injectable_function(void, x, y        ) }

define_reflectable_class_function(UWindow, onKey, "args:key,modifiers,ch")
void UWindow::onKey(UKey key, UModifiers modifiers, char ch) {
    implement_injectable_function(void, key, modifiers, ch)
}

define_reflectable_class_function(UWindow, onFieldFocus, "args:focus")
void UWindow::onFieldFocus(bool focus) {
    implement_injectable_function(void, focus)
}

define_reflectable_class_function(UWindow, onFieldText, "args:text")
void UWindow::onFieldText(const std::string &text) {
    implement_injectable_function(void, text)
}

define_reflectable_class_function(UWindow, onResize, "args:w,h")
void UWindow::onResize(float w, float h) {
    implement_injectable_function(void, w, h)
}

define_reflectable_class_function(UWindow, onGLDraw)
void UWindow::onGLDraw() {
    implement_injectable_function(void)
}

define_reflectable_class_function(UWindow, onDraw)
void UWindow::onDraw() {
    implement_injectable_function(void)
}

void UWindow::_notifyShow() {
    if (mShown) {
        return;
    }

    mShown = true;
    onShow();
}

void UWindow::_notifyHide() {
    if (! mShown) {
        return;
    }

    mShown = false;
    onHide();
}

void UWindow::_notifyDestroy() {
    if (mDestroyed) {
        return;
    }

    mDestroyed = false;
    onDestroy();
}

void UWindow::_notifyCursorWheel(float x, float y, float delta) {
    _notifyCursorMove(x, y);
    onCursorWheel(x, y, delta);
}

void UWindow::_notifyCursorRight(float x, float y) {
    _notifyCursorMove(x, y);
    onCursorRight(x, y);
}

void UWindow::_notifyCursorMove(float x, float y) {
    if (mCursorX == x && mCursorY == y) {
        return;
    }

    onCursorMove(x, y, mCursorDowned);
}

void UWindow::_notifyCursorDown(float x, float y) {
    _notifyCursorMove(x, y);

    mCursorDowned = true;
    onCursorDown(x, y);
}

void UWindow::_notifyCursorUp(float x, float y) {
    _notifyCursorMove(x, y);

    if (mCursorDowned) {
        mCursorDowned = false;
        onCursorUp(x, y);
    }
}

void UWindow::_notifyKey(UKey key, UModifiers modifiers) {
    char ch = UKeyGetChar(key, modifiers);
    onKey(key, modifiers, ch);
}

void UWindow::_notifyFieldFocus(bool focus) {
    if (mFieldFocus == focus) {
        return;
    }

    mFieldFocus = focus;
    onFieldFocus(focus);
}

void UWindow::_notifyFieldText(const std::string &text) {
    if (mFieldText == text) {
        return;
    }

    mFieldText = text;
    onFieldText(text);
}

void UWindow::_notifyResize(float w, float h) {
    if (mWidth == w && mHeight == h) {
        return;
    }

    mWidth  = w;
    mHeight = h;
    onResize(w, h);
}

void UWindow::_notifyGLDraw() {
    onGLDraw();
}

void UWindow::_notifyDraw() {
    onDraw();
}
