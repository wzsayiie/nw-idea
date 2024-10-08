#include "uwindow.h"
#include <map>
#include <vector>
#include "dlazy.h"
#include "lcpp.h"
#include "lreg.h"
#include "rdefine.h"

static dash::lazy<std::vector<UWindow::ptr>>   gUnregisteredWindows;
static dash::lazy<std::map<int, UWindow::ptr>> gWindows;

static int UWindowGetID(const UWindow::ptr &window) {
    return (int)(intptr_t)window.get();
}

static void UWindowRegister(const UWindow::ptr &window) {
    int id = UWindowGetID(window);

    //already registered.
    auto target = gWindows->find(id);
    if (target != gWindows->end()) {
        return;
    }

    //already added.
    for (auto &it : *gUnregisteredWindows) {
        if (it == window) {
            return;
        }
    }

    gUnregisteredWindows->push_back(window);
}

define_low_function(_UWindowPopUnregistered)
void _UWindowPopUnregistered() {
    if (gUnregisteredWindows->empty()) {
        low::ir = 0;
        return;
    }
    
    auto it = gUnregisteredWindows->begin();
    int  id = UWindowGetID(*it);

    gWindows->insert({ id, *it });
    gUnregisteredWindows->erase(it);

    low::ir = id;
}

static UWindow::ptr UWindowGet(int id) {
    auto it = gWindows->find(id);
    if (it != gWindows->end()) {
        return it->second;
    }
    return nullptr;
}

define_low_function(_UWindowTitle)
void _UWindowTitle() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        low::sr = window->title();
    }
    low::sr = "";
}

define_low_function(_UWindowIdentifier)
void _UWindowIdentifier() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        low::sr = window->identifier();
    }
    low::sr = "";
}

define_low_function(_UWindowWantShow)
void _UWindowWantShow() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        low::br = window->wantShow();
    }
    low::br = false;
}

define_low_function(_UWindowNotifyCreate)
void _UWindowNotifyCreate() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyCreate();
    }
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

define_low_function(_UWindowNotifyCursorBegin)
void _UWindowNotifyCursorBegin() {
    int   id = low::i[0];
    float x  = low::f[1];
    float y  = low::f[2];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyCursorBegin(x, y);
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

define_low_function(_UWindowNotifyCursorEnd)
void _UWindowNotifyCursorEnd() {
    int   id = low::i[0];
    float x  = low::f[1];
    float y  = low::f[2];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->_notifyCursorEnd(x, y);
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

define_low_function(_UWindowFieldVisible)
void _UWindowFieldVisible() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        low::br = window->fieldVisible();
    }
    low::br = false;
}

define_low_function(_UWindowFieldSetFocus)
void _UWindowFieldSetFocus() {
    int  id    = low::i[0];
    bool focus = low::b[1];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->setFieldFocus(focus);
    }
}

define_low_function(_UWindowFieldFocus)
void _UWindowFieldFocus() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        low::br = window->fieldFocus();
    }
    low::br = false;
}

define_low_function(_UWindowFieldX)
void _UWindowFieldX() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        low::fr = window->fieldX();
    }
    low::fr = 0;
}

define_low_function(_UWindowFieldY)
void _UWindowFieldY() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        low::fr = window->fieldY();
    }
    low::fr = 0;
}

define_low_function(_UWindowFieldWidth)
void _UWindowFieldWidth() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        low::fr = window->fieldWidth();
    }
    low::fr = 0;
}

define_low_function(_UWindowFieldHeight)
void _UWindowFieldHeight() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        low::fr = window->fieldHeight();
    }
    low::fr = 0;
}

define_low_function(_UWindowFieldSetText)
void _UWindowFieldSetText() {
    int         id   = low::i[0];
    std::string text = low::s[1];

    if (UWindow::ptr window = UWindowGet(id)) {
        window->setFieldText(text);
    }
}

define_low_function(_UWindowFieldText)
void _UWindowFieldText() {
    int id = low::i[0];

    if (UWindow::ptr window = UWindowGet(id)) {
        low::sr = window->fieldText();
    }
    low::sr = "";
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

define_reflectable_class_function(UWindow, setTitle, "args:title")
void UWindow::setTitle(const std::string &title) {
    mTitle = title;
}

define_reflectable_class_function(UWindow, title)
std::string UWindow::title() {
    return mTitle;
}

define_reflectable_class_function(UWindow, setIdentifier, "args:identifier")
void UWindow::setIdentifier(const std::string &identifier) {
    mIdentifier = identifier;
}

define_reflectable_class_function(UWindow, identifier)
std::string UWindow::identifier() {
    return mIdentifier;
}

define_reflectable_class_function(UWindow, showWindow)
void UWindow::showWindow() {
    UWindowRegister(me());
    mWantShow = true;
}

define_reflectable_class_function(UWindow, wantShow)
bool UWindow::wantShow() {
    return mWantShow;
}

define_reflectable_class_function(UWindow, created)
define_reflectable_class_function(UWindow, shown  )
define_reflectable_class_function(UWindow, width  )
define_reflectable_class_function(UWindow, height )

bool  UWindow::created() { return mCreated; }
bool  UWindow::shown  () { return mShown  ; }
float UWindow::width  () { return mWidth  ; }
float UWindow::height () { return mHeight ; }

define_reflectable_class_function(UWindow, cursorBegan )
define_reflectable_class_function(UWindow, cursorDowned)
define_reflectable_class_function(UWindow, cursorX     )
define_reflectable_class_function(UWindow, cursorY     )

bool  UWindow::cursorBegan () { return mCursorBegan ; }
bool  UWindow::cursorDowned() { return mCursorDowned; }
float UWindow::cursorX     () { return mCursorX     ; }
float UWindow::cursorY     () { return mCursorY     ; }

define_reflectable_class_function(UWindow, setFieldVisible, "args:visible")
void UWindow::setFieldVisible(bool visible) {
    if (mFieldVisible == visible) {
        return;
    }

    mFieldVisible = visible;
    if (!visible) {
        setFieldFocus(false);
    }
}

define_reflectable_class_function(UWindow, setFieldFocus, "args:focus")
void UWindow::setFieldFocus(bool focus) {
    if (mFieldFocus == focus) {
        return;
    }

    mFieldFocus = focus;
    onFieldFocus(focus);
}

define_reflectable_class_function(UWindow, setFieldRect, "args:x,y,w,h")
void UWindow::setFieldRect(float x, float y, float w, float h) {
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

    mFieldText = text;
    onFieldText(text);
}

define_reflectable_class_function(UWindow, fieldVisible)
define_reflectable_class_function(UWindow, fieldFocus  )
define_reflectable_class_function(UWindow, fieldX      )
define_reflectable_class_function(UWindow, fieldY      )
define_reflectable_class_function(UWindow, fieldWidth  )
define_reflectable_class_function(UWindow, fieldHeight )
define_reflectable_class_function(UWindow, fieldText   )

bool        UWindow::fieldVisible() { return mFieldVisible; }
bool        UWindow::fieldFocus  () { return mFieldFocus  ; }
float       UWindow::fieldX      () { return mFieldX      ; }
float       UWindow::fieldY      () { return mFieldY      ; }
float       UWindow::fieldWidth  () { return mFieldWidth  ; }
float       UWindow::fieldHeight () { return mFieldHeight ; }
std::string UWindow::fieldText   () { return mFieldText   ; }

define_reflectable_class_function(UWindow, onCreate )
define_reflectable_class_function(UWindow, onShow   )
define_reflectable_class_function(UWindow, onHide   )
define_reflectable_class_function(UWindow, onDestroy)

void UWindow::onCreate () { implement_injectable_function(void) }
void UWindow::onShow   () { implement_injectable_function(void) }
void UWindow::onHide   () { implement_injectable_function(void) }
void UWindow::onDestroy() { implement_injectable_function(void) }

define_reflectable_class_function(UWindow, onCursorBegin, "args:x,y"       )
define_reflectable_class_function(UWindow, onCursorWheel, "args:x,y,delta" )
define_reflectable_class_function(UWindow, onCursorRight, "args:x,y"       )
define_reflectable_class_function(UWindow, onCursorMove , "args:x,y,downed")
define_reflectable_class_function(UWindow, onCursorDown , "args:x,y"       )
define_reflectable_class_function(UWindow, onCursorUp   , "args:x,y"       )
define_reflectable_class_function(UWindow, onCursorEnd  , "args:x,y"       )

void UWindow::onCursorBegin(float x, float y)              { implement_injectable_function(void, x, y        ) }
void UWindow::onCursorWheel(float x, float y, float delta) { implement_injectable_function(void, x, y, delta ) }
void UWindow::onCursorRight(float x, float y)              { implement_injectable_function(void, x, y        ) }
void UWindow::onCursorMove (float x, float y, bool downed) { implement_injectable_function(void, x, y, downed) }
void UWindow::onCursorDown (float x, float y)              { implement_injectable_function(void, x, y        ) }
void UWindow::onCursorUp   (float x, float y)              { implement_injectable_function(void, x, y        ) }
void UWindow::onCursorEnd  (float x, float y)              { implement_injectable_function(void, x, y        ) }

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

void UWindow::_notifyCreate() {
    if (mCreated) {
        return;
    }

    mCreated = true;
    onCreate();
}

void UWindow::_notifyShow() {
    if (!mCreated || mShown) {
        return;
    }

    mShown = true;
    onShow();
}

void UWindow::_notifyHide() {
    if (!mShown) {
        return;
    }

    mShown = false;
    onHide();
}

void UWindow::_notifyDestroy() {
    if (!mCreated) {
        return;
    }

    mCreated = false;
    onDestroy();
}

void UWindow::_notifyCursorBegin(float x, float y) {
    //begin.
    if (!mCursorBegan) {
        mCursorBegan = true;

        mCursorX = x;
        mCursorY = y;
        onCursorBegin(x, y);

        return;
    }

    //move.
    if (mCursorX != x || mCursorY != y) {
        mCursorX = x;
        mCursorY = y;
        onCursorMove(x, y, mCursorDowned);
    }
}

void UWindow::_notifyCursorWheel(float x, float y, float delta) {
    //begin -> wheel -> end.
    if (!mCursorBegan) {
        mCursorX = x;
        mCursorY = y;

        mCursorBegan = true ; onCursorBegin(x, y);
        /* .... .... .... .*/ onCursorWheel(x, y, delta);
        mCursorBegan = false; onCursorEnd  (x, y);

        return;
    }

    //move -> wheel.
    if (mCursorX != x || mCursorY != y) {
        mCursorX = x;
        mCursorY = y;
        onCursorMove(x, y, mCursorDowned);
    }
    onCursorWheel(x, y, delta);
}

void UWindow::_notifyCursorRight(float x, float y) {
    //begin -> right -> end.
    if (!mCursorBegan) {
        mCursorX = x;
        mCursorY = y;

        mCursorBegan = true ; onCursorBegin(x, y);
        /* .... .... .... .*/ onCursorRight(x, y);
        mCursorBegan = false; onCursorEnd  (x, y);

        return;
    }

    //move -> right.
    if (mCursorX != x || mCursorY != y) {
        mCursorX = x;
        mCursorY = y;
        onCursorMove(x, y, mCursorDowned);
    }
    onCursorRight(x, y);
}

void UWindow::_notifyCursorMove(float x, float y) {
    //begin -> end.
    if (!mCursorBegan) {
        mCursorX = x;
        mCursorY = x;

        mCursorBegan = true ; onCursorBegin(x, y);
        mCursorBegan = false; onCursorEnd  (x, y);

        return;
    }

    //move.
    if (mCursorX != x || mCursorY != y) {
        mCursorX = x;
        mCursorY = y;
        onCursorMove(x, y, mCursorDowned);
    }
}

void UWindow::_notifyCursorDown(float x, float y) {
    //begin -> down.
    if (!mCursorBegan) {
        mCursorX = x;
        mCursorY = y;

        mCursorBegan  = true ; onCursorBegin(x, y);
        mCursorDowned = true ; onCursorDown (x, y);

        return;
    }

    //move -> down.
    if (mCursorX != x || mCursorY != y) {
        mCursorX = x;
        mCursorY = y;
        onCursorMove(x, y, mCursorDowned);
    }
    mCursorDowned = true;
    onCursorDown(x, y);
}

void UWindow::_notifyCursorUp(float x, float y) {
    if (!mCursorDowned) {
        return;
    }

    //move -> up.
    if (mCursorX != x || mCursorY != y) {
        mCursorX = x;
        mCursorY = y;
        onCursorMove(x, y, mCursorDowned);
    }
    mCursorDowned = false;
    onCursorUp(x, y);
}

void UWindow::_notifyCursorEnd(float x, float y) {
    if (!mCursorBegan) {
        return;
    }

    //move -> up -> end.
    if (mCursorX != x || mCursorY != y) {
        mCursorX = x;
        mCursorY = y;
        onCursorMove(x, y, mCursorDowned);
    }
    if (mCursorDowned) {
        onCursorUp(x, y);
    }
    mCursorBegan = false;
    onCursorEnd(x, y);
}

void UWindow::_notifyKey(UKey key, UModifiers modifiers) {
    char ch = UKeyGetChar(key, modifiers);
    onKey(key, modifiers, ch);
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
