//
// Renderer.h - Direct2D/Direct3D renderer for the memo application
// This file defines the rendering interface and implementation for Windows platform
//

#pragma once

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <d2d1.h>
    #include <d3d11.h>
    #include <dxgi1_4.h>
#else
    #error "This renderer is Windows-only"
#endif

#include <memory>
#include <string>

namespace Memo {
namespace Render {

/**
 * @brief Renderer class for drawing document elements on Windows platform
 *
 * This class provides the rendering functionality using Direct2D and Direct3D.
 * It handles the low-level graphics operations needed to display notes, strokes,
 * and other visual elements of the memo application.
 */
class Renderer {
public:
    /**
     * @brief Construct a new Renderer object
     * @param hwnd Handle to the window that will be rendered to
     */
    explicit Renderer(HWND hwnd);

    /**
     * @brief Destroy the Renderer object
     */
    ~Renderer();

    /**
     * @brief Initialize the renderer with device context
     * @return bool True if initialization was successful, false otherwise
     */
    bool initialize();

    /**
     * @brief Render the document content to the screen
     * @param document_title Title of the document to render
     * @param document_content Content of the document to render
     * @param stroke_count Number of strokes in the document
     * @return bool True if rendering was successful, false otherwise
     */
    bool render(const std::string& document_title,
                const std::string& document_content,
                size_t stroke_count);

    /**
     * @brief Clear the rendering surface
     * @return bool True if clearing was successful, false otherwise
     */
    bool clear();

    /**
     * @brief Resize the rendering surface
     * @param width New width of the surface
     * @param height New height of the surface
     * @return bool True if resize was successful, false otherwise
     */
    bool resize(UINT width, UINT height);

private:
    HWND hwnd_;                           // Window handle for rendering
    ID2D1Factory* d2d_factory_;           // Direct2D factory
    ID2D1HwndRenderTarget* render_target_; // Direct2D render target
    ID3D11Device* d3d_device_;            // Direct3D device
    ID3D11DeviceContext* d3d_context_;    // Direct3D device context
    IDXGISwapChain* swap_chain_;          // DXGI swap chain

    /**
     * @brief Create the Direct2D render target
     * @return bool True if creation was successful, false otherwise
     */
    bool createRenderTarget();

    /**
     * @brief Create the Direct3D device and context
     * @return bool True if creation was successful, false otherwise
     */
    bool createDevice();
};

} // namespace Render
} // namespace Memo