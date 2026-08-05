#include "aurora_debug.h"

#include <aurora/gfx.h>
#include <aurora/imgui.h>
#include <dolphin/pad.h>

#include "jsyswrap.h"
#include "pc_platform.h"

#include <array>
#include <cstddef>

namespace {

bool s_showPerformance = true;
bool s_showRenderer = true;
bool s_showInput = true;

const char* widescreen_mode_name(int mode)
{
    switch (mode) {
        case 0: return "hor+";
        case 1: return "fullscreen stretch";
        case 2: return "4:3 UI";
        default: return "unknown";
    }
}

float normalized_axis(s8 value)
{
    return static_cast<float>(value) / (value < 0 ? 128.0f : 127.0f);
}

void draw_axis(const char* label, s8 value)
{
    const float normalized = normalized_axis(value);
    ImGui::Text("%s", label);
    ImGui::SameLine(80.0f);
    ImGui::ProgressBar((normalized + 1.0f) * 0.5f, ImVec2(150.0f, 0.0f), "");
    ImGui::SameLine();
    ImGui::Text("%4d", static_cast<int>(value));
}

void draw_performance_window()
{
    static std::array<float, 180> history{};
    static size_t next = 0;
    const float fps = aurora_get_fps();
    history[next] = fps;
    next = (next + 1) % history.size();

    ImGui::SetNextWindowPos(ImVec2(10.0f, 40.0f), ImGuiCond_Appearing);
    ImGui::SetNextWindowSize(ImVec2(340.0f, 165.0f), ImGuiCond_Appearing);
    if (!ImGui::Begin("Performance", &s_showPerformance)) {
        ImGui::End();
        return;
    }

    ImGui::Text("Aurora: %.1f FPS (%.2f ms)", fps, fps > 0.0f ? 1000.0f / fps : 0.0f);
    ImGui::PlotLines("##fps", history.data(), static_cast<int>(history.size()),
                     static_cast<int>(next), nullptr, 0.0f, 75.0f, ImVec2(320.0f, 70.0f));
    ImGui::Text("Audio buffer: %d", pc_audio_get_buffer_fill());
    ImGui::Text("Audio active: %s", pc_audio_is_active() ? "yes" : "no");
    ImGui::End();
}

void draw_renderer_window()
{
    ImGui::SetNextWindowPos(ImVec2(360.0f, 40.0f), ImGuiCond_Appearing);
    ImGui::SetNextWindowSize(ImVec2(440.0f, 280.0f), ImGuiCond_Appearing);
    if (!ImGui::Begin("Renderer", &s_showRenderer)) {
        ImGui::End();
        return;
    }

    const AuroraStats* stats = aurora_get_stats();
    ImGui::Text("Render size: %d x %d", g_pc_window_w, g_pc_window_h);
    ImGui::Text("Aspect factor: %.4f", pc_widescreen_get_aspect_factor());
    ImGui::Text("Widescreen mode: %d (%s)", g_pc_widescreen_stretch,
                widescreen_mode_name(g_pc_widescreen_stretch));
    ImGui::Separator();

    if (stats != nullptr) {
        ImGui::Text("Draw calls: %u", stats->drawCallCount);
        ImGui::Text("Merged draws: %u", stats->mergedDrawCallCount);
        ImGui::Text("Pipelines: %u queued, %u created", stats->queuedPipelines,
                    stats->createdPipelines);
        ImGui::Text("Uploads: vertices %u KB, indices %u KB, uniforms %u KB",
                    stats->lastVertSize / 1024, stats->lastIndexSize / 1024,
                    stats->lastUniformSize / 1024);
        ImGui::Text("Textures: %u KB", stats->lastTextureUploadSize / 1024);
    }

    ImGui::Separator();
    ImGui::Text("emu64 commands: %d", pc_emu64_frame_cmds);
    ImGui::Text("Triangles: %d  Vertices: %d  Display lists: %d",
                pc_emu64_frame_tri_cmds, pc_emu64_frame_vtx_cmds, pc_emu64_frame_dl_cmds);
    ImGui::Text("Cull visible/rejected: %d / %d", pc_emu64_frame_cull_visible,
                pc_emu64_frame_cull_rejected);
    ImGui::End();
}

void draw_input_window()
{
    PADStatus pads[PAD_MAX_CONTROLLERS]{};
    JW_getPadStatus(pads);
    const PADStatus& pad = pads[0];

    ImGui::SetNextWindowPos(ImVec2(10.0f, 215.0f), ImGuiCond_Appearing);
    ImGui::SetNextWindowSize(ImVec2(340.0f, 285.0f), ImGuiCond_Appearing);
    if (!ImGui::Begin("Input", &s_showInput)) {
        ImGui::End();
        return;
    }

    ImGui::Text("Port 0   status %d", static_cast<int>(pad.err));
    ImGui::Text("Buttons 0x%04X", pad.button);
    draw_axis("Stick X", pad.stickX);
    draw_axis("Stick Y", pad.stickY);
    draw_axis("C-stick X", pad.substickX);
    draw_axis("C-stick Y", pad.substickY);
    ImGui::Text("Triggers L/R: %3u / %3u", pad.triggerLeft, pad.triggerRight);
    ImGui::TextDisabled("F3 hides the debug UI");
    ImGui::End();
}

} // namespace

extern "C" {

int g_pc_debug_ui_visible = 0;

void ac_debug_imgui_init(const AuroraWindowSize*)
{
    ImGui::StyleColorsDark();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
}

void ac_debug_imgui_draw(void)
{
    if (ImGui::IsKeyPressed(ImGuiKey_F3, false)) {
        g_pc_debug_ui_visible = !g_pc_debug_ui_visible;
    }
    if (!g_pc_debug_ui_visible) {
        return;
    }

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Debug")) {
            ImGui::MenuItem("Performance", nullptr, &s_showPerformance);
            ImGui::MenuItem("Renderer", nullptr, &s_showRenderer);
            ImGui::MenuItem("Input", nullptr, &s_showInput);
            ImGui::Separator();
            if (ImGui::MenuItem("Hide (F3)")) {
                g_pc_debug_ui_visible = 0;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    if (s_showPerformance) draw_performance_window();
    if (s_showRenderer) draw_renderer_window();
    if (s_showInput) draw_input_window();
}

} // extern "C"
