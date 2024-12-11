#include "UIManager.hpp"

#include <filesystem>

#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <Config.hpp>

UIManager::UIManager() :
    m_lastError(EngineError::EE_OK),
    m_currentContext(nullptr),
    m_currentIO(nullptr),
    m_style(nullptr),
    m_window(nullptr),
    m_show_engine_about(false)
{}

UIManager::~UIManager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
	if(m_currentContext)
		ImGui::DestroyContext(m_currentContext);
}

std::optional<EngineError> UIManager::Init(GLFWwindow *window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    m_currentContext = ImGui::CreateContext();
    PTRCHECK_M(m_currentContext, EngineError::EE_IMGUI_CREATE_CONTEXT_FAILED, "ERROR::UIMANAGER::INIT::IMGUI_CREATE_CONTEXT_FAILED");
   
    // Setup Dear ImGui IO config
    m_currentIO = &ImGui::GetIO(); (void)m_currentIO;
    PTRCHECK_M(m_currentIO, EngineError::EE_IMGUI_GET_IO_FAILED, "ERROR::UIMANAGER::INIT::IMGUI_GET_IO_FAILED");
 
    m_currentIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    m_currentIO->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    m_currentIO->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    m_currentIO->WantCaptureMouse = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    m_style = &ImGui::GetStyle();
    PTRCHECK_M(m_style, EngineError::EE_IMGUI_GET_STYLE_FAILED, "ERROR::UIMANAGER::INIT::IMGUI_GET_STYLE_FAILED");

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    if(m_currentIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        m_style->WindowRounding = 0.0f;
        m_style->Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    //std::string fontPath = "fonts/OregonLDO_Regular.ttf";
    std::filesystem::path fontPath(Config::DEFAULT_FONT_PATH);
    if (!std::filesystem::exists(fontPath))
    {
        std::cout << "ERROR::UIMANAGER::INIT::FONT_NOT_FOUD:" << fontPath.generic_string() << std::endl;
        m_lastError = EngineError::EE_UIMANAGER_INIT_FONT_NOT_FOUND;
        return m_lastError;
    }
    
    m_currentIO->Fonts->AddFontFromFileTTF(fontPath.generic_string().c_str(), Config::DEFAULT_UI_FONT_SIZE);

    // Window related setup
    m_window = window;
    PTRCHECK_M(m_window, EngineError::EE_UIMANAGER_INIT_INVALID_WINDOW_PROVIDED, "ERROR::UIMANAGER::INIT::INVALID_WINDOW_PROVIDED");

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(Config::GLSL_VERSION);

	return std::nullopt;
}

// TODO: will this ever fail?
std::optional<EngineError> UIManager::ProcessInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
    return std::nullopt;
}

// TODO: will this ever fail?
std::optional<EngineError> UIManager::BuildUI()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if(buildMainMenuBar().has_value())
        return m_lastError;

    if (m_show_engine_about)
        showEngineAboutWindow();

    return std::nullopt;
}

// TODO: will this ever fail?
std::optional<EngineError> UIManager::buildMainMenuBar()
{
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 10));
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Project"))
        {
            //if (ImGui::MenuItem("New")) {}
            //if (ImGui::MenuItem("Open", "Ctrl+o")) {}
            if (ImGui::MenuItem("Exit"))
                glfwSetWindowShouldClose(m_window, GLFW_TRUE);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About", NULL, &m_show_engine_about)) {}
        
            ImGui::EndMenu();
        }
       
        ImGui::EndMainMenuBar();
    }
    ImGui::PopStyleVar();

    return std::nullopt;
}

std::optional<EngineError> UIManager::UpdateAndRenderPlatformWindows()
{
    if (m_currentIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    return std::nullopt;
}

void UIManager::showEngineAboutWindow()
{   
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(Config::WINDOW_WIDTH / 4, Config::WINDOW_HEIGHT / 4));
    if (!ImGui::Begin("About", &m_show_engine_about, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_AlwaysUseWindowPadding))
    {
        ImGui::End();
        ImGui::PopStyleVar();
        return;
    }
    ImGui::Text("Version: %s", Config::CUBE_ENGINE_CURRENT_VERSION);
    ImGui::End();
    ImGui::PopStyleVar();
}

EngineError UIManager::GetLastError() noexcept 
{ 
    return m_lastError; 
}