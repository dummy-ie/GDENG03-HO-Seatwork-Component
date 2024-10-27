#include "CreditsScreen.h"

#include "EngineTime.h"
#include "imgui.h"
#include "Logger.h"
#include "Vector4D.h"

using namespace math;

CreditsScreen::CreditsScreen() : UIScreen("CreditsScreen")
{
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::draw()
{
	float freq = 1.0f;
	count += EngineTime::getDeltaTime();
	Vector4D rainbow = Vector4D(
		std::sin(freq * count + 0) * 127 + 128,
		std::sin(freq * count + 2) * 127 + 128,
		std::sin(freq * count + 4) * 127 + 128,
		255);

	Vector4D rainbow2 = Vector4D(
		std::sin(freq * count + 2) * 127 + 128,
		std::sin(freq * count + 0) * 127 + 128,
		std::sin(freq * count + 4) * 127 + 128,
		255);

	Vector4D rainbow3 = Vector4D(
		std::sin(freq * count + 4) * 127 + 128,
		std::sin(freq * count + 2) * 127 + 128,
		std::sin(freq * count + 0) * 127 + 128,
		255);

	ImGui::Begin("Credits", &isActive, ImGuiWindowFlags_NoDocking);

	ImVec4 vec4 = ImVec4(rainbow.x / 255.0f, rainbow.y / 255.0f, rainbow.z / 255.0f, rainbow.w / 255.0f);
	ImVec4 vec4_2 = ImVec4(rainbow2.x / 255.0f, rainbow2.y / 255.0f, rainbow2.z / 255.0f, rainbow2.w / 255.0f);
	ImVec4 vec4_3 = ImVec4(rainbow3.x / 255.0f, rainbow3.y / 255.0f, rainbow3.z / 255.0f, rainbow3.w / 255.0f);

	ImGui::TextColored(vec4, "Scene Editor v0.02");
	ImGui::TextColored(vec4_2, "Developed by Shane Laurenze Cablayan");
	ImGui::TextColored(vec4_3, "Soon with Ray Tracing\n");
	ImGui::Text("");
	ImGui::Text("Acknowledgements");

	ImGui::End();
}
