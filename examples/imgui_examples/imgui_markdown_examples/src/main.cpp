#include <cstdio>
#include <print>

#include "IconsFontAwesome5.h" // https://github.com/juliettef/IconFontCppHeaders
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_markdown.h" // https://github.com/juliettef/imgui_markdown
#include <string>

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

void LinkCallback(ImGui::MarkdownLinkCallbackData data_);
inline ImGui::MarkdownImageData
ImageCallback(ImGui::MarkdownLinkCallbackData data_);

static ImFont* H1 = nullptr;
static ImFont* H2 = nullptr;
static ImFont* H3 = nullptr;

static ImGui::MarkdownConfig mdConfig;

void LinkCallback(ImGui::MarkdownLinkCallbackData data_) {
    std::string url(data_.link, data_.linkLength);
    /*  if (!data_.isImage) {
         ShellExecuteA(nullptr, "open", url.c_str(), nullptr, nullptr,
                       SW_SHOWNORMAL);
     } */
}

inline ImGui::MarkdownImageData
ImageCallback(ImGui::MarkdownLinkCallbackData data_) {
    // In your application you would load an image based on data_ input. Here we
    // just use the imgui font texture.
    ImTextureID image = ImGui::GetIO().Fonts->TexID;
    // > C++14 can use ImGui::MarkdownImageData imageData{ true, false, image,
    // ImVec2( 40.0f, 20.0f ) };
    ImGui::MarkdownImageData imageData;
    imageData.isValid = true;
    imageData.useLinkCallback = false;
    imageData.user_texture_id = image;
    imageData.size = ImVec2(40.0f, 20.0f);

    // For image resize when available size.x > image width, add
    ImVec2 const contentSize = ImGui::GetContentRegionAvail();
    if (imageData.size.x > contentSize.x) {
        float const ratio = imageData.size.y / imageData.size.x;
        imageData.size.x = contentSize.x;
        imageData.size.y = contentSize.x * ratio;
    }

    return imageData;
}

void LoadFonts(float fontSize_ = 12.0f) {
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    // Base font
    io.Fonts->AddFontFromFileTTF("myfont.ttf", fontSize_);
    // Bold headings H2 and H3
    H2 = io.Fonts->AddFontFromFileTTF("myfont-bold.ttf", fontSize_);
    H3 = mdConfig.headingFormats[1].font;
    // bold heading H1
    float fontSizeH1 = fontSize_ * 1.1f;
    H1 = io.Fonts->AddFontFromFileTTF("myfont-bold.ttf", fontSizeH1);
}

void ExampleMarkdownFormatCallback(
    const ImGui::MarkdownFormatInfo& markdownFormatInfo_, bool start_) {
    // Call the default first so any settings can be overwritten by our
    // implementation. Alternatively could be called or not called in a switch
    // statement on a case by case basis. See defaultMarkdownFormatCallback
    // definition for furhter examples of how to use it.
    ImGui::defaultMarkdownFormatCallback(markdownFormatInfo_, start_);

    switch (markdownFormatInfo_.type) {
        // example: change the colour of heading level 2
        case ImGui::MarkdownFormatType::HEADING: {
            if (markdownFormatInfo_.level == 2) {
                if (start_) {
                    ImGui::PushStyleColor(
                        ImGuiCol_Text,
                        ImGui::GetStyle().Colors[ImGuiCol_TextDisabled]);
                } else {
                    ImGui::PopStyleColor();
                }
            }
            break;
        }
        default: {
            break;
        }
    }
}

void Markdown(const std::string& markdown_) {
    // You can make your own Markdown function with your prefered string
    // container and markdown config. > C++14 can use ImGui::MarkdownConfig
    // mdConfig{ LinkCallback, NULL, ImageCallback, ICON_FA_LINK, { { H1, true
    // }, { H2, true }, { H3, false } }, NULL };
    mdConfig.linkCallback = LinkCallback;
    mdConfig.tooltipCallback = nullptr;
    mdConfig.imageCallback = ImageCallback;
    mdConfig.linkIcon = ICON_FA_LINK;
    mdConfig.headingFormats[0] = { H1, true };
    mdConfig.headingFormats[1] = { H2, true };
    mdConfig.headingFormats[2] = { H3, false };
    mdConfig.userData = nullptr;
    mdConfig.formatCallback = ExampleMarkdownFormatCallback;
    ImGui::Markdown(markdown_.c_str(), markdown_.length(), mdConfig);
}

void MarkdownExample() {
    const std::string markdownText = R"(
# H1 Header: Text and Links
You can add [links like this one to enkisoftware](https://www.enkisoftware.com/) and lines will wrap well.
You can also insert images ![image alt text](https://i1.hdslb.com/bfs/archive/8de351f54a34705fde718a59a384a9409a857069.jpg@672w_378h_1c_!web-home-common-cover.avif)
Horizontal rules:
***
___
*Emphasis* and **strong emphasis** change the appearance of the text.
## H2 Header: indented text.
  This text has an indent (two leading spaces).
    This one has two.
### H3 Header: Lists
  * Unordered lists
    * Lists can be indented with two extra spaces.
  * Lists can have [links like this one to Avoyd](https://www.avoyd.com/) and *emphasized text*
)";
    Markdown(markdownText);
}

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// main code
int main(int, char**) {

    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) {
        return -1;
    }

    const char* glsl_version = "#version 450";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(
        1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr) {
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::println("Failed to initialize GLAD");
        return -1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad;            // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport
                                                        // / Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform
    // windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can
    // also load multiple fonts and use ImGui::PushFont()/PopFont() to select
    // them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you
    // need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr.
    // Please handle those errors in your application (e.g. use an assertion, or
    // display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and
    // stored into a texture when calling
    // ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame
    // below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use
    // Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string
    // literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at
    // runtime from the "fonts/" folder. See Makefile.emscripten for details.
    // io.Fonts->AddFontDefault();
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    // ImFont* font =
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f,
    // nullptr, io.Fonts->GetGlyphRangesJapanese()); IM_ASSERT(font != nullptr);

    while (!glfwWindowShouldClose(window)) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to
        // tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data
        // to your main application, or clear/overwrite your copy of the mouse
        // data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input
        // data to your main application, or clear/overwrite your copy of the
        // keyboard data. Generally you may always pass all inputs to dear
        // imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in
        // ImGui::ShowDemoWindow()! You can browse its code to learn more about
        // Dear ImGui!).

        MarkdownExample();

        // 2. Show a simple window that we create ourselves. We use a Begin/End
        // pair to create a named window.

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we
        // save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call
        //  glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
