#include "ColorPickerScreen.h"

#include "imgui.h"
#include "Logger.h"

ColorPickerScreen::ColorPickerScreen() : UIScreen("ColorPickerScreen")
{
    isActive = false;
    debug::Logger::log(this, "Initialized");
}

ColorPickerScreen::~ColorPickerScreen()
{
}

void ColorPickerScreen::draw()
{
    ImGui::Begin("Color Picker", &isActive);

    if (ImGui::ColorPicker4("Color", color, ImGuiColorEditFlags_PickerHueWheel))
    {
	    
    };

    ImGui::End();
}