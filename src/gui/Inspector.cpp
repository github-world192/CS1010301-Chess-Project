#include "gui/Inspector.hpp"

#include <iostream>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

Inspector::Inspector(RefPtr<App> app)
{
    ///
    /// Create a resizable window by passing by OR'ing our window flags with
    /// kWindowFlags_Resizable.
    ///
    window_ = Window::Create(app->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
                             false, kWindowFlags_Titled | kWindowFlags_Resizable);

    ///
    /// Create our HTML overlay-- we don't care about its initial size and
    /// position because it'll be calculated when we call OnResize() below.
    ///
    overlay_ = Overlay::Create(window_, 1, 1, 0, 0);

    ///
    /// Force a call to OnResize to perform size/layout of our overlay.
    ///
    OnResize(window_.get(), window_->width(), window_->height());

    ///
    /// Register our Inspector instance as a WindowListener so we can handle the
    /// Window's OnResize event below.
    ///
    window_->set_listener(this);

    ///
    /// Register our Inspector instance as a LoadListener so we can handle the
    /// View's OnFinishLoading and OnDOMReady events below.
    ///
    overlay_->view()->set_load_listener(this);

    ///
    /// Register our Inspector instance as a ViewListener so we can handle the
    /// View's OnChangeCursor and OnChangeTitle events below.
    ///
    overlay_->view()->set_view_listener(this);
}

Inspector::~Inspector()
{
}

void Inspector::OnClose(ultralight::Window *window)
{
}

void Inspector::OnResize(ultralight::Window *window, uint32_t width, uint32_t height)
{
    ///
    /// This is called whenever the window changes size (values in pixels).
    ///
    /// We resize our overlay here to take up the entire window.
    ///
    overlay_->Resize(width, height);
}

void Inspector::OnFinishLoading(ultralight::View *caller,
                                uint64_t frame_id,
                                bool is_main_frame,
                                const String &url)
{
    ///
    /// This is called when a frame finishes loading on the page.
    ///
}

void Inspector::OnDOMReady(ultralight::View *caller,
                           uint64_t frame_id,
                           bool is_main_frame,
                           const String &url)
{
    ///
    /// This is called when a frame's DOM has finished loading on the page.
    ///
    /// This is the best time to setup any JavaScript bindings.
    ///
}

void Inspector::OnChangeCursor(ultralight::View *caller,
                               Cursor cursor)
{
    ///
    /// This is called whenever the page requests to change the cursor.
    ///
    /// We update the main window's cursor here.
    ///
    window_->SetCursor(cursor);
}

void Inspector::OnChangeTitle(ultralight::View *caller,
                              const String &title)
{
    ///
    /// This is called whenever the page requests to change the title.
    ///
    /// We update the main window's title here.
    ///
    window_->SetTitle(title.utf8().data());
}

// void Inspector::SetWindow(RefPtr<Window> window)
// {
//     window_ = window;
// }

RefPtr<Window> Inspector::GetWindow() const { return window_; }

// void Inspector::SetOverlay(RefPtr<Overlay> overlay)
// {
//     overlay_ = overlay;
// }

RefPtr<Overlay> Inspector::GetOverlay() const { return overlay_; }