#pragma once
#include "imgui.h"
#include "imgui_internal.h"

extern ImFont* icon_font;

void AddLogoTitle(const char* title, ImU32 shadowCol)
{
	ImGui::PushStyleColor(ImGuiCol_Text, shadowCol);
	auto cursorpos = ImGui::GetCursorPos();
	ImGui::SetCursorPos(ImVec2(cursorpos.x + 1, cursorpos.y));
	ImGui::Text(title);
	ImGui::SetCursorPos(ImVec2(cursorpos.x - 1, cursorpos.y));
	ImGui::Text(title);
	ImGui::SetCursorPos(ImVec2(cursorpos.x, cursorpos.y + 1));
	ImGui::Text(title);
	ImGui::SetCursorPos(ImVec2(cursorpos.x, cursorpos.y - 1));
	ImGui::Text(title);
	ImGui::PopStyleColor();
	ImGui::SetCursorPos(ImVec2(cursorpos.x, cursorpos.y));
	ImGui::Text(title);
}

void AddTabBar(const char* ico, const char* title, ImU32 shadowCol)
{
	auto cursorpos = ImGui::GetCursorPos();
	ImGui::SetCursorPos(ImVec2(cursorpos.x + 30.f, cursorpos.y + 27.f));
	ImGui::PushStyleColor(ImGuiCol_Text, shadowCol);
	ImGui::PushFont(icon_font);
	ImGui::Text(ico);
	ImGui::PopStyleColor();

	ImGui::SetCursorPos(ImVec2(cursorpos.x + 60.f, cursorpos.y + 25.f));
	ImGui::Text(title);
	ImGui::PopFont();
}

void myBeginChild(const char* str_id, ImVec2 childSize, ImU32 shadowCol)
{
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 3);
	ImVec2 pos = ImGui::GetCursorPos();
	ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0.07f, 0.07f, 0.08f, 1.f });
	ImGui::BeginChild(std::string(str_id).append(".main").c_str(), childSize, false, ImGuiWindowFlags_NoScrollbar);

	auto cursorpos = ImGui::GetCursorPos();
	ImGui::PushStyleColor(ImGuiCol_Text, shadowCol);
	ImGui::SetCursorPos(ImVec2(cursorpos.x + 7, cursorpos.y + 8));
	ImGui::Text(str_id);
	ImGui::Separator();
	ImGui::PopStyleColor(2);
	ImGui::SetCursorPos(ImVec2(cursorpos.x + 7, cursorpos.y + 7));
	ImGui::Text(str_id);

	ImGui::SetCursorPosY(30); 
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.04f, 0.05f, 0.05f, 1.00f));
	ImGui::BeginChild(str_id, { childSize.x, childSize.y - 30 }, false, ImGuiWindowFlags_NoScrollbar);
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void myEndChild()
{
	ImGui::EndChild();
	ImGui::EndChild();
}

void AddIconButton(const char* ico, const char* title, const char* title1, ImU32 shadowCol /*还差一个按钮事件函数*/)
{
	ImGui::PushStyleColor(ImGuiCol_Text, shadowCol);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6);
	ImGui::PushFont(icon_font);

	auto txt_size = ImGui::CalcTextSize(title1);
	auto cursorpos = ImGui::GetCursorPos();
	if (ImGui::Button(("##" + std::string(title)).c_str(), { txt_size.x + 30,txt_size.y + 10 }))
	{

	}

	ImGui::SetCursorPos({ cursorpos.x + 14.f, cursorpos.y + 7.5f });
	ImGui::Text(ICON_SAVE);

	ImGui::SetCursorPos({ cursorpos.x + 37.f, cursorpos.y + 5.0f });
	ImGui::Text(title);

	ImGui::PopFont();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}