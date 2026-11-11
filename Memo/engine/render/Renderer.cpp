//
// Renderer.cpp - Implementation of the Renderer class
// This file contains the Direct2D/Direct3D rendering implementation for Windows
//

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <d2d1.h>
    #include <d3d11.h>
    #include <dxgi1_4.h>
#else
    #error "This renderer is Windows-only"
#endif

#include "Renderer.h"
#include <iostream>

namespace Memo {
namespace Render {

Renderer::Renderer(HWND hwnd) : hwnd_(hwnd),
                               d2d_factory_(nullptr),
                               render_target_(nullptr),
                               d3d_device_(nullptr),
                               d3d_context_(nullptr),
                               swap_chain_(nullptr) {
    // Constructor implementation
}

Renderer::~Renderer() {
    // Cleanup resources
    if (render_target_) {
        render_target_->Release();
    }

    if (d2d_factory_) {
        d2d_factory_->Release();
    }

    if (swap_chain_) {
        swap_chain_->Release();
    }

    if (d3d_context_) {
        d3d_context_->Release();
    }

    if (d3d_device_) {
        d3d_device_->Release();
    }
}

bool Renderer::initialize() {
    // Initialize Direct2D factory
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory_);
    if (FAILED(hr)) {
        std::cerr << "Failed to create Direct2D factory" << std::endl;
        return false;
    }

    // Create device and context
    if (!createDevice()) {
        std::cerr << "Failed to create Direct3D device" << std::endl;
        return false;
    }

    // Create render target
    if (!createRenderTarget()) {
        std::cerr << "Failed to create render target" << std::endl;
        return false;
    }

    return true;
}

bool Renderer::render(const std::string& document_title,
                      const std::string& document_content,
                      size_t stroke_count) {
    // Clear the render target
    if (!clear()) {
        return false;
    }

    // TODO: Implement actual rendering logic
    // This would involve:
    // 1. Drawing document title
    // 2. Drawing document content
    // 3. Drawing strokes
    // 4. Applying appropriate styling and effects

    std::cout << "Rendering document: " << document_title
              << " with " << stroke_count << " strokes" << std::endl;

    return true;
}

bool Renderer::clear() {
    if (render_target_) {
        render_target_->BeginDraw();
        render_target_->Clear(D2D1::ColorF(D2D1::ColorF::White));
        render_target_->EndDraw();
        return true;
    }
    return false;
}

bool Renderer::resize(UINT width, UINT height) {
    if (render_target_) {
        // Resize the render target
        D2D1_SIZE_U size = D2D1::SizeU(width, height);
        render_target_->Resize(size);
        return true;
    }
    return false;
}

bool Renderer::createRenderTarget() {
    RECT rc;
    GetClientRect(hwnd_, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(
        static_cast<UINT>(rc.right - rc.left),
        static_cast<UINT>(rc.bottom - rc.top)
    );

    HRESULT hr = d2d_factory_->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hwnd_, size),
        &render_target_
    );

    return SUCCEEDED(hr);
}

bool Renderer::createDevice() {
    // Create DXGI factory
    IDXGIFactory4* dxgi_factory = nullptr;
    HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory4),
                                    reinterpret_cast<void**>(&dxgi_factory));

    if (FAILED(hr)) {
        return false;
    }

    // Create D3D device and context
    hr = D3D11CreateDevice(
        nullptr,                    // default adapter
        D3D_DRIVER_TYPE_HARDWARE,   // hardware device
        0,                          // no software device
        D3D11_CREATE_DEVICE_DEBUG,  // enable debug layer
        nullptr,                    // default feature levels
        0,                          // default feature levels count
        D3D11_SDK_VERSION,          // SDK version
        &d3d_device_,               // device output
        nullptr,                    // feature level output
        &d3d_context_               // context output
    );

    dxgi_factory->Release();

    return SUCCEEDED(hr);
}

} // namespace Render
} // namespace Memo