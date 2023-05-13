#pragma once

#include "Inspector.hpp"
#include "core/Game.hpp"
#include "lib/json.hpp"

#include <AppCore/AppCore.h>
#include <JavaScriptCore/JavaScript.h>

using Json = nlohmann::json;
using namespace ultralight;
using namespace Chess;

class GUI : public AppListener,
            public WindowListener,
            public LoadListener,
            public ViewListener
{
public:
    GUI();

    virtual ~GUI();

    // Start the run loop.
    virtual void Run();

    // This is called continuously from the app's main loop.
    virtual void OnUpdate() override;

    // This is called when the window is closing.
    virtual void OnClose(ultralight::Window *window) override;

    // This is called whenever the window resizes.
    virtual void OnResize(ultralight::Window *window, uint32_t width,
                          uint32_t height) override;

    // This is called when the page finishes a load in one of its frames.
    virtual void OnFinishLoading(ultralight::View *caller,
                                 uint64_t frame_id,
                                 bool is_main_frame,
                                 const String &url) override;

    // This is called when the DOM has loaded in one of its frames.
    virtual void OnDOMReady(ultralight::View *caller,
                            uint64_t frame_id,
                            bool is_main_frame,
                            const String &url) override;

    // This is called when the page requests to change the Cursor.
    virtual void OnChangeCursor(ultralight::View *caller,
                                Cursor cursor) override;

    virtual void OnChangeTitle(ultralight::View *caller,
                               const String &title) override;

    virtual RefPtr<View> OnCreateInspectorView(ultralight::View *caller, bool is_local,
                                               const String &inspected_url) override;

protected:
    RefPtr<App> app_;
    RefPtr<Window> window_;
    RefPtr<Overlay> overlay_;
    Inspector *inspector_;

private:
    static GUI instance_;

    static JSValueRef JsonToJSValue(JSContextRef ctx, const Json &json);

    static JSValueRef Test(JSContextRef ctx, JSObjectRef function,
                           JSObjectRef thisObject, size_t argumentCount,
                           const JSValueRef arguments[],
                           JSValueRef *exception);

    static JSValueRef GetCurrentPlayer(JSContextRef ctx, JSObjectRef function,
                                       JSObjectRef thisObject, size_t argumentCount,
                                       const JSValueRef arguments[],
                                       JSValueRef *exception);

    static JSValueRef GetBoard(JSContextRef ctx, JSObjectRef function,
                               JSObjectRef thisObject, size_t argumentCount,
                               const JSValueRef arguments[],
                               JSValueRef *exception);

    static JSValueRef GetBoardPieceMovablePos(JSContextRef ctx, JSObjectRef function,
                                              JSObjectRef thisObject, size_t argumentCount,
                                              const JSValueRef arguments[],
                                              JSValueRef *exception);

    static JSValueRef BoardMovePiece(JSContextRef ctx, JSObjectRef function,
                                     JSObjectRef thisObject, size_t argumentCount,
                                     const JSValueRef arguments[],
                                     JSValueRef *exception);

    // static JSValueRef GetBoardWidth(JSContextRef ctx, JSObjectRef function,
    //                                 JSObjectRef thisObject, size_t argumentCount,
    //                                 const JSValueRef arguments[],
    //                                 JSValueRef *exception);

    // static JSValueRef GetBoardHeight(JSContextRef ctx, JSObjectRef function,
    //                                  JSObjectRef thisObject, size_t argumentCount,
    //                                  const JSValueRef arguments[],
    //                                  JSValueRef *exception);

    // static JSValueRef GetBoardPieceType(JSContextRef ctx, JSObjectRef function,
    //                                     JSObjectRef thisObject, size_t argumentCount,
    //                                     const JSValueRef arguments[],
    //                                     JSValueRef *exception);

    // static JSValueRef GetBoardPieceOwner(JSContextRef ctx, JSObjectRef function,
    //                                      JSObjectRef thisObject, size_t argumentCount,
    //                                      const JSValueRef arguments[],
    //                                      JSValueRef *exception);
};
