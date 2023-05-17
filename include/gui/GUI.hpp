/**
 *  File: GUI.hpp
 *  Author: 張皓鈞(HAO) m831718@gmail.com
 *  Create Date: 2023/05/17 14:04:39
 *  Editor: 張皓鈞(HAO) m831718@gmail.com
 *  Update Date: 2023/05/17 22:52:15
 *  Description: GUI
 */

#pragma once

#include "Inspector.hpp"
#include "core/Game.hpp"
#include "lib/json.hpp"
#include <JavaScriptCore/JavaScript.h>
#include <string>
#include <vector>

using Json = nlohmann::json;
using namespace ultralight;
using namespace Chess;

class GUI : public AppListener,
            public WindowListener,
            public LoadListener,
            public ViewListener
{
public:
    GUI(int argc, char *argv[]);

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

    void ParseArgs(int argc, char *argv[]);

    bool IsArgsSet(std::string arg);

protected:
    RefPtr<App> app_;
    RefPtr<Window> window_;
    RefPtr<Overlay> overlay_;
    Inspector *inspector_;
    std::vector<std::string> args_;

private:
    static GUI instance_;

    static JSValueRef JsonToJSValue(JSContextRef ctx, const Json &json);

    static JSValueRef Test(JSContextRef ctx, JSObjectRef function,
                           JSObjectRef thisObject, size_t argumentCount,
                           const JSValueRef arguments[],
                           JSValueRef *exception);

    static JSValueRef StartGame(JSContextRef ctx, JSObjectRef function,
                                JSObjectRef thisObject, size_t argumentCount,
                                const JSValueRef arguments[],
                                JSValueRef *exception);

    static JSValueRef UpdateGame(JSContextRef ctx, JSObjectRef function,
                                 JSObjectRef thisObject, size_t argumentCount,
                                 const JSValueRef arguments[],
                                 JSValueRef *exception);

    static JSValueRef GetCurrentPlayer(JSContextRef ctx, JSObjectRef function,
                                       JSObjectRef thisObject, size_t argumentCount,
                                       const JSValueRef arguments[],
                                       JSValueRef *exception);

    static JSValueRef GetGameState(JSContextRef ctx, JSObjectRef function,
                                   JSObjectRef thisObject, size_t argumentCount,
                                   const JSValueRef arguments[],
                                   JSValueRef *exception);

    static JSValueRef GetPlayerClock(JSContextRef ctx, JSObjectRef function,
                                     JSObjectRef thisObject, size_t argumentCount,
                                     const JSValueRef arguments[],
                                     JSValueRef *exception);

    static JSValueRef GetIsPromoting(JSContextRef ctx, JSObjectRef function,
                                     JSObjectRef thisObject, size_t argumentCount,
                                     const JSValueRef arguments[],
                                     JSValueRef *exception);

    static JSValueRef Promoting(JSContextRef ctx, JSObjectRef function,
                                JSObjectRef thisObject, size_t argumentCount,
                                const JSValueRef arguments[],
                                JSValueRef *exception);

    static JSValueRef Resign(JSContextRef ctx, JSObjectRef function,
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
