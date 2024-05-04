#pragma once
#include "imgui.h"
#include "imgui_internal.h"
#include "other/Config.hpp"

#include <array>
#include <string_view>
#include <unordered_map>

extern ImFont* icon_font;
extern ImFont* small_font;
extern ImFont* big_font;
extern ID3D11ShaderResourceView* pTextureView;
typedef void(*CallBack)();
bool AddCheckBox(const char* label, bool* v);

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

bool AddTabBar(const char* ico, const char* title, bool check, ImU32 shadowCol)
{
	bool ret = false;
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return ret;

	ImGuiContext& g = *GImGui;
	const ImGuiID id = window->GetID(title);
	const ImVec2 pos = window->DC.CursorPos;
	auto cursorpos = ImGui::GetCursorPos();

	const float ContentX = ImGui::GetContentRegionAvail().x;						// ����������
	const ImRect item_bb = { pos,{pos.x + ContentX, pos.y + 38.f} };				// �ؼ���С����
	const float height = item_bb.Max.y - item_bb.Min.y;
	const float width  = item_bb.Max.x - item_bb.Min.x;
	ImGui::ItemSize(item_bb, g.Style.FramePadding.y);
	if (!ImGui::ItemAdd(item_bb, id))
		return ret;

	const bool hovered = ImGui::ItemHoverable(item_bb, id, g.LastItemData.InFlags);
	if (check)
	{
		window->DrawList->AddCircleFilled(ImVec2(item_bb.Max.x, item_bb.Min.y + height / 2), 7.f, ImColor(ImVec4(config::menu_color::theme_col[0], config::menu_color::theme_col[1], config::menu_color::theme_col[2], .7f)));
		window->DrawList->AddCircleFilled(ImVec2(item_bb.Min.x, item_bb.Min.y + height / 2), 7.f, ImColor(ImVec4(config::menu_color::theme_col[0], config::menu_color::theme_col[1], config::menu_color::theme_col[2], .7f)));
	}

	if(hovered)
	{
		window->DrawList->AddCircleFilled(ImVec2(item_bb.Max.x, item_bb.Min.y + height / 2), 7.f, ImColor(78, 78, 78, 100));
		window->DrawList->AddCircleFilled(ImVec2(item_bb.Min.x, item_bb.Min.y + height / 2), 7.f, ImColor(78, 78, 78, 100));
		if (ImGui::IsMouseClicked(0))
			ret = true;
	}

	ImGui::PushFont(icon_font); 
	ImGui::PushStyleColor(ImGuiCol_Text, shadowCol);
	const ImVec2 ico_size = ImGui::CalcTextSize(ico, NULL, true);
	ImGui::RenderText(ImVec2(item_bb.Min.x + 35.f, item_bb.Min.y + (height - ico_size.y) / 2.f + 2.f), ico);
	ImGui::PopStyleColor();

	const ImVec2 title_size = ImGui::CalcTextSize(title, NULL, true);
	ImGui::RenderText(ImVec2(item_bb.Min.x + 80.f, item_bb.Min.y + (height - title_size.y) / 2.f), title);
	ImGui::PopFont();
	
	return ret;
}

void myBeginChild(const char* str_id, ImVec2 childSize, bool* v = NULL)
{
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 3);
	ImVec2 pos = ImGui::GetCursorPos();
	ImGui::PushStyleColor(ImGuiCol_ChildBg, { config::menu_color::begin_title_col[0], config::menu_color::begin_title_col[1], config::menu_color::begin_title_col[2], 1.f});
	ImGui::BeginChild(std::string(str_id).append(".main").c_str(), childSize, false, ImGuiWindowFlags_NoScrollbar);

	auto cursorpos = ImGui::GetCursorPos();
	if (v)
	{
		ImGui::SetCursorPos(ImVec2(cursorpos.x + 3, cursorpos.y));
		AddCheckBox(str_id, v);
	}
	else
	{
		ImGui::SetCursorPos(ImVec2(cursorpos.x + 7, cursorpos.y + 5));
		ImGui::Text(str_id);
	}
	ImGui::PopStyleColor(1);

	ImGui::SetCursorPosY(25);
	ImGui::Separator();

	ImGui::SetCursorPosY(26); 
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(config::menu_color::begin_bgcol[0], config::menu_color::begin_bgcol[1], config::menu_color::begin_bgcol[2], 1.00f));

	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0);
	ImGui::BeginChild(str_id, { childSize.x, childSize.y - 26 }, false, ImGuiWindowFlags_NoScrollbar);
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void myEndChild()
{
	ImGui::EndChild();
	ImGui::EndChild();
}

void AddIconButton(const char* ico, const char* title, const char* title1, ImU32 shadowCol, CallBack fun)
{
	ImGui::PushStyleColor(ImGuiCol_Text, shadowCol);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6);
	ImGui::PushFont(icon_font);

	auto txt_size = ImGui::CalcTextSize(title1);
	auto cursorpos = ImGui::GetCursorPos();
	if (ImGui::Button(("##" + std::string(title)).c_str(), { txt_size.x + 30,txt_size.y + 10 }))
	{
		fun();
	}

	ImGui::SetCursorPos({ cursorpos.x + 14.f, cursorpos.y + 7.5f });
	ImGui::Text(ico);

	ImGui::SetCursorPos({ cursorpos.x + 37.f, cursorpos.y + 5.0f });
	ImGui::Text(title);

	ImGui::PopFont();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

float Clamp(float value, float min, float max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
}
float Lerp(float a, float b, float t)
{
	return a + (b - a) * t;
}
static std::unordered_map<ImGuiID, float> current_values_slider{};
void AddSliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImGuiID id = window->GetID(label);

	const ImVec2 pos = window->DC.CursorPos;
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);				// �����ı���С
	const float ContentX = ImGui::GetContentRegionAvail().x;						// ����������
	const ImRect item_bb = { pos,{pos.x + ContentX, pos.y + label_size.y + 19.f} };	// �ؼ���С����
	const ImRect slider_bb = { 
		{pos.x + g.Style.FramePadding.x, pos.y + label_size.y + 3.f}, 
		{item_bb.Max.x - g.Style.FramePadding.x, item_bb.Max.y} };	// �����С����

	ImGui::ItemSize(item_bb, g.Style.FramePadding.y);
	if (!ImGui::ItemAdd(item_bb, id))
		return;

	float& current_value = current_values_slider[id];
	const bool hovered = ImGui::ItemHoverable(slider_bb, id, g.LastItemData.InFlags); // �������Ƿ���ͣ�ڻ�����
	if (hovered) {
		ImGui::SetHoveredID(id); // ��������ͣ�ڻ����ϣ�������ͣID
	}

	if (hovered && g.IO.MouseClicked[0]) {
		g.ActiveId = id; // ��������������£����ûID
	}

	if (g.ActiveId == id) { // ������鱻����
		if (g.IO.MouseDown[0]) { // ���������������
			const float u = Clamp((g.IO.MousePos.x - slider_bb.Min.x) / (slider_bb.Max.x - slider_bb.Min.x), 0.0f, 1.0f); // ��������λ�ö�Ӧ��ֵ
			*v = Lerp(v_min, v_max, u); // ��������λ�ø��»����ֵ
		}
		else {
			g.ActiveId = 0; // ������������ͷţ����ûID
		}
	}

	current_value = Lerp(current_value, *v, 0.1f);
	const float value = (current_value - v_min) / (v_max - v_min);

	const ImRect bgbb = { ImVec2(slider_bb.Min.x, slider_bb.Min.y + 8.0f),
	ImVec2(slider_bb.Min.x + (ContentX - g.Style.FramePadding.x * 2.f), slider_bb.Min.y + 11.f) };
	const ImVec2 value_pos = { (slider_bb.Min.x) + (value * (bgbb.Max.x - bgbb.Min.x)),
	slider_bb.Min.y + 9.5f };

	ImGui::RenderFrame(bgbb.Min, bgbb.Max, ImColor(30, 30, 30, 255)); // ���鱳��
	window->DrawList->AddCircleFilled(value_pos,4.5f, ImColor(ImVec4(config::menu_color::theme_col[0], config::menu_color::theme_col[1], config::menu_color::theme_col[2], 255))); // ����Բ��

	//ImGui::RenderText(ImVec2(item_bb.Min.x + g.Style.FramePadding.x, item_bb.Min.y), label); 
	ImGui::RenderText(ImVec2(item_bb.Min.x + g.Style.FramePadding.x, item_bb.Min.y + 5.f), label);

	ImGui::PushFont(small_font);
	char value_buf[64];
	snprintf(value_buf, sizeof(value_buf), format, *v);
	const ImVec2 number_size = ImGui::CalcTextSize(value_buf, NULL, true);			// ��ֵ�ı���С
	ImGui::RenderText(ImVec2(item_bb.Min.x + (ContentX - number_size.x - g.Style.FramePadding.x), item_bb.Min.y + 8.f), value_buf);
	ImGui::PopFont();
}

void AddColorEdit3(const char* label, float col[3])
{
	static int flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoTooltip;// | ImGuiColorEditFlags_NoBorder;
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImGuiID id = window->GetID(label);

	auto cursorpos = ImGui::GetCursorPos();
	const ImVec2 pos = window->DC.CursorPos;
	const float check_x = 20.5f;
	const float ContentX = ImGui::GetContentRegionAvail().x;						// ����������
	const ImRect item_bb = { pos, {pos.x + ContentX - (check_x * 1.5f) - g.Style.FramePadding.x, pos.y + check_x + 6.f} };	// �ؼ���С����
	static float height = item_bb.Max.y - item_bb.Min.y;

	if (!ImGui::ItemAdd(item_bb, id))
		return;

	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1.00f, 1.00f, 1.00f, 0.15f));
	ImGui::SetCursorPos(ImVec2(cursorpos.x + ContentX - g.Style.FramePadding.x - (check_x * 1.5f), cursorpos.y + (height - check_x) / 2.f));
	if (ImGui::ColorButton((std::string("##color.") + label).c_str(), ImVec4(col[0], col[1], col[2], 1.f), flags, ImVec2(check_x * 1.5f, check_x))) {
		ImGui::OpenPopup((std::string("##popup.") + label).c_str());
	}

	if (ImGui::BeginPopup((std::string("##popup.") + label).c_str())) {
		ImGui::ColorPicker3((std::string("##picker.") + label).c_str(), col);
		ImGui::EndPopup();
	}
	ImGui::SetCursorPos(cursorpos);
	ImGui::ItemSize(item_bb, g.Style.FramePadding.y);
	ImGui::RenderText(ImVec2(item_bb.Min.x + g.Style.FramePadding.x, item_bb.Min.y + 5.f), label);
	ImGui::PopStyleColor();
}

static std::unordered_map<ImGuiID, float> current_states_check{};
bool AddCheckBox(const char* label, bool* v)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return *v;

	ImGuiContext& g = *GImGui;
	const ImGuiID id = window->GetID(label);

	auto cursorpos = ImGui::GetCursorPos();
	const ImVec2 pos = window->DC.CursorPos;
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);				// �����ı���С
	const float check_x = 20.5f;
	const float ContentX = ImGui::GetContentRegionAvail().x;						// ����������
	const ImRect item_bb = { pos, {pos.x + ContentX - g.Style.FramePadding.x, pos.y + check_x + 6.f} };	// �ؼ���С����

	const ImRect check_bb = { 
		{pos.x + ContentX - check_x - g.Style.FramePadding.x, pos.y + g.Style.FramePadding.y},
		{item_bb.Max.x, pos.y + check_x + g.Style.FramePadding.y} };	// �ؼ���С����
	
	ImGui::ItemSize(item_bb, g.Style.FramePadding.y);
	if (!ImGui::ItemAdd(item_bb, id))
		return *v;

	float& current_value = current_states_check[id];
	const bool hovered = ImGui::ItemHoverable(check_bb, id, g.LastItemData.InFlags); // �������Ƿ���ͣ�ڻ�����
	if (hovered)
	{
		ImGui::SetHoveredID(id); // ��������ͣ�ڻ����ϣ�������ͣID
		if(ImGui::IsMouseClicked(0))
			*v = !*v;
	}

	current_value = Lerp(current_value, *v ? 1.f : 0.0f, 0.05f);
	ImGui::RenderText(ImVec2(item_bb.Min.x + g.Style.FramePadding.x, item_bb.Min.y + 5.f), label);
	ImGui::RenderFrame(check_bb.Min, check_bb.Max, hovered ? ImColor(62, 65, 58, 255) : ImColor(52, 55, 48, 255));
	if(current_value > 0.1f)
	{ // ѡ��ͼ��
		ImGui::RenderFrame({ check_bb.Min.x + 2.f, check_bb.Min.y + 2.f }, { check_bb.Max.x - 2.f, check_bb.Max.y - 2.f }, 
			ImColor(ImVec4(config::menu_color::theme_col[0], config::menu_color::theme_col[1], config::menu_color::theme_col[2], current_value)));
		static float width = check_bb.Max.x - check_bb.Min.x;
		window->DrawList->AddCircleFilled(
		{ check_bb.Min.x + (width / 2.f),check_bb.Min.y + (width / 2.f) }
		, width / 2.75f, ImColor(0, 0, 0, int(current_value * 58.f)));
		window->DrawList->AddCircleFilled(
		{ check_bb.Min.x + (width / 2.f),check_bb.Min.y + (width / 2.f) }
		, width / 6.f, ImColor(22, 22, 22, int(current_value * 175.f)));
	}
	return *v;
}

static std::unordered_map<ImGuiID, float> current_states_combo{};
void AddCombo(const char* label, int* current_item, const char* const items[], int items_count, float width)
{
	static bool isOpen = false;

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImGuiID id = window->GetID(label);

	auto cursorpos = ImGui::GetCursorPos();
	const ImVec2 pos = window->DC.CursorPos;
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);				// �����ı���С
	const ImVec2 text_size = ImGui::CalcTextSize(items[*current_item], NULL, true);	// ѡ���ı���С
	const float check_x = 20.5f;
	const float ContentX = ImGui::GetContentRegionAvail().x;						// ����������
	const ImRect item_bb = { pos, {pos.x + ContentX - g.Style.FramePadding.x, pos.y + check_x + 6.f} };	// �ؼ���С����
	const ImRect comb_bb = { 
		{pos.x + ContentX - width, pos.y + g.Style.FramePadding.y},
		{item_bb.Max.x, pos.y + check_x + g.Style.FramePadding.y}};	// �ؼ���С����

	ImGui::ItemSize(item_bb, g.Style.FramePadding.y);
	if (!ImGui::ItemAdd(item_bb, id))
		return;

	float& current_value = current_states_combo[id];
	const bool hovered = ImGui::ItemHoverable(comb_bb, id, g.LastItemData.InFlags); // �������Ƿ���ͣ�ڻ�����
	if (hovered)
	{
		ImGui::SetHoveredID(id); // ��������ͣ�ڻ����ϣ�������ͣID
		if (ImGui::IsMouseClicked(0))
		{
			isOpen = !isOpen;
		}
	}

	current_value = Lerp(current_value, isOpen ? 70.0f : 18.0f, 0.09f);
	if (current_value > 32.f)
	{
		ImVec2 windowsize = ImVec2(width - 4.f, current_value);
		ImGui::SetNextWindowSize(windowsize);
		ImGui::SetNextWindowPos(ImVec2(comb_bb.Min.x, pos.y + g.Style.FramePadding.y + check_x));
		ImGui::Begin("##Dropdown", &isOpen, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar);
		if (!ImGui::IsWindowFocused())
		{
			isOpen = false;
		}
		ImGui::PushFont(small_font);
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(config::menu_color::theme_col[0], config::menu_color::theme_col[1], config::menu_color::theme_col[2], .61f));
		ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(config::menu_color::theme_col[0], config::menu_color::theme_col[1], config::menu_color::theme_col[2], .61f));
		for (int i = 0; i < items_count; i++)
		{
			if (ImGui::Selectable(items[i]))
			{
				*current_item = i;
				isOpen = false;
			}
		}
		ImGui::PopStyleColor(2);
		ImGui::PopFont();
		ImGui::End();
	}

	ImGui::RenderFrame(comb_bb.Min, comb_bb.Max, ImColor(ImVec4(0.07f, 0.07f, 0.07f, 1.00f)));
	char tempChar[64]{};
	snprintf(tempChar, sizeof(tempChar), "%s", items[*current_item]);
	while (ImGui::CalcTextSize(tempChar, NULL, true).x > width)
	{
		tempChar[strlen(tempChar) - 4] = '.';
		tempChar[strlen(tempChar) - 3] = '.';
		tempChar[strlen(tempChar) - 2] = '.';
		tempChar[strlen(tempChar) - 1] = 0;
	}
	window->DrawList->AddText(icon_font, 13.f, ImVec2(comb_bb.Min.x + 4.f, comb_bb.Min.y + 4.f), ImColor(ImVec4(1.f, 1.f, 1.f, 1.00f)), tempChar);
	window->DrawList->AddText(icon_font, 13.f, ImVec2(comb_bb.Min.x + (width - 20.f), comb_bb.Min.y + 5.4f), 
		ImColor(ImVec4(config::menu_color::theme_col[0], config::menu_color::theme_col[1], config::menu_color::theme_col[2], 255)), ICON_DOWN);
	ImGui::RenderText(ImVec2(item_bb.Min.x + g.Style.FramePadding.x, item_bb.Min.y + 5.f), label);
}

static std::unordered_map<ImGuiID, float> current_states_hitbox{};
void AddHitBoxex(const char* const sItems[], const ImVec2 const vItems[], bool bItems[], const int items_count)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	const ImVec2 pos = window->DC.CursorPos;
	ImGuiID* const id = new ImGuiID[items_count]{};
	ImRect* const item_bb = new ImRect[items_count]{};
	const auto textSize = ImGui::CalcTextSize("X", NULL, true);

	for (size_t i = 0; i < items_count; i++)
	{
		ImGuiContext& g = *GImGui;
		id[i] = window->GetID(sItems[i]);

		float& current_value = current_states_hitbox[id[i]];
		const auto textSize = ImGui::CalcTextSize(ICON_DIAN, NULL, true);

		auto ppos = ImGui::GetCursorPos();
		const ImVec2 xPos = ImVec2(vItems[i].x - textSize.x / 2.0f, vItems[i].y - textSize.y / 2.0f + 6.f);

		item_bb[i] = ImRect(
			{ pos.x + vItems[i].x - 10.f,pos.y + vItems[i].y - 10.f },
			{ pos.x + vItems[i].x + 10.f,pos.y + vItems[i].y + 10.f }
		);

		if (!ImGui::ItemAdd(item_bb[i], id[i]))
			return;

		// ����
		{
			const char* Title = "Advanced hitbone";//Hitboxex
			auto logoSize = ImGui::CalcTextSize(Title, NULL, true);
			auto tete = (340.f - logoSize.x) / 2.f;
			auto tete2 = (35.f - logoSize.y) / 2.f + 4.f;
			ImGui::PushStyleColor(ImGuiCol_Text, ImGui::ColorConvertFloat4ToU32(ImVec4(config::menu_color::theme_col[0], config::menu_color::theme_col[1], config::menu_color::theme_col[2], 0.8f)));
			ImGui::SetCursorPos(ImVec2(ppos.x + tete - 1.f, ppos.y + tete2));
			ImGui::Text(Title);
			ImGui::SetCursorPos(ImVec2(ppos.x + tete + 1.f, ppos.y + tete2));
			ImGui::Text(Title);
			ImGui::SetCursorPos(ImVec2(ppos.x + tete, ppos.y + tete2 + 1.f));
			ImGui::Text(Title);
			ImGui::SetCursorPos(ImVec2(ppos.x + tete, ppos.y + tete2 + 1.f));
			ImGui::Text(Title);
			ImGui::PopStyleColor();
			ImGui::SetCursorPos(ImVec2(ppos.x + tete, ppos.y + tete2));
			ImGui::Text(Title);
		}

		ImGui::SetCursorPos(ImVec2(ppos.x, ppos.y + 35.f));
		ImGui::Image((ImTextureID)pTextureView, ImVec2(340.f,565.f));
		ImGui::SetCursorPos(ppos);

		const bool hovered = ImGui::ItemHoverable(item_bb[i], id[i], g.LastItemData.InFlags);

		if (!bItems[i])
		{
			ImGui::PushStyleColor(ImGuiCol_Text, { 0.f,0.f,0.f,1.f });
			ImGui::SetCursorPos(ImVec2(xPos.x - 1.f, xPos.y - 1.f));
			ImGui::Text(ICON_DIAN);

			ImGui::SetCursorPos(ImVec2(xPos.x + 1.f, xPos.y - 1.f));
			ImGui::Text(ICON_DIAN);

			ImGui::SetCursorPos(ImVec2(xPos.x - 1.f, xPos.y + 1.f));
			ImGui::Text(ICON_DIAN);

			ImGui::SetCursorPos(ImVec2(xPos.x + 1.f, xPos.y + 1.f));
			ImGui::Text(ICON_DIAN);

			ImGui::SetCursorPos(xPos);
			ImGui::PushStyleColor(ImGuiCol_Text, { .5f, .5f, .5f, 1.f });
			ImGui::Text(ICON_DIAN);
			ImGui::PopStyleColor(2);
		}

		current_value = Lerp(current_value, bItems[i] ? 1.0f : 0.0f, 0.08f);
		if (hovered)
		{
			ImGui::SetHoveredID(id[i]); // ��������ͣ�ڻ����ϣ�������ͣID
			if (ImGui::IsMouseClicked(0))
				bItems[i] = !bItems[i];
		}
		if (current_value > 0.1f)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, { 0.f,0.f,0.f,current_value });
			ImGui::SetCursorPos(ImVec2(xPos.x - 1.f, xPos.y - 1.f));
			ImGui::Text(ICON_DJIA);

			ImGui::SetCursorPos(ImVec2(xPos.x + 1.f, xPos.y - 1.f));
			ImGui::Text(ICON_DJIA);

			ImGui::SetCursorPos(ImVec2(xPos.x - 1.f, xPos.y + 1.f));
			ImGui::Text(ICON_DJIA);

			ImGui::SetCursorPos(ImVec2(xPos.x + 1.f, xPos.y + 1.f));
			ImGui::Text(ICON_DJIA);

			ImGui::SetCursorPos(xPos);
			ImGui::PushStyleColor(ImGuiCol_Text, { 1.f,1.f,1.f,current_value });
			ImGui::Text(ICON_DJIA);
			ImGui::PopStyleColor(2);
		}
		ImGui::SetCursorPos(pos);
	}
}

void AddPageTitle(int* page, const char* const ico[], const char* const title[], const int count)
{
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return;
		ImGuiContext& g = *GImGui;
		const ImGuiID id = window->GetID("PageTitle");
		const ImVec2 pos = window->DC.CursorPos;
		const float ContentX = ImGui::GetContentRegionAvail().x;						// ����������
		const ImRect item_bb = { pos,{pos.x + ContentX, pos.y + 25.f} };				// �ؼ���С����
		ImGui::ItemSize(item_bb, g.Style.FramePadding.y);
		if (!ImGui::ItemAdd(item_bb, id))
			return;
	}

	for (size_t i = 0; i < count; i++)
	{
		if (AddTabBar(ico[i], title[i], i == *page, ImColor(ImVec4(config::menu_color::theme_col[0], config::menu_color::theme_col[1], config::menu_color::theme_col[2], 255))))
			*page = i;
	}
}

constexpr std::array< std::string_view, 256 > g_key_codes{
	"bind",
	"Left Mouse",
	"Right Mouse",
	"Control-break",
	"Middle Mouse",
	"X1 Mouse",
	"X2 Mouse",
	"Undefined",
	"Backspace",
	"TAB",
	"Reserved",
	"Reserved",
	"Clear",
	"Enter",
	"Reserved",
	"Reserved",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"CAPS Lock",
	"IME",
	"IME",
	"IME",
	"IME",
	"IME",
	"IME",
	"ESC",
	"IME",
	"IME",
	"IME",
	"IME",
	"Spacebar",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left Arrow",
	"Up Arrow",
	"Right Arrow",
	"Down Arrow",
	"Select",
	"Print",
	"Execute",
	"Print Screen",
	"Insert",
	"Delete",
	"Help",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Undefined",
	"Undefined",
	"Undefined",
	"Undefined",
	"Undefined",
	"Undefined",
	"Undefined",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"Left Window",
	"Right Window",
	"Applications",
	"Reserved",
	"Sleep",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Numpad *",
	"Numpad +",
	"Numpad Separator",
	"Numpad -",
	"Numpad .",
	"Numpad /",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"F13",
	"F14",
	"F15",
	"F16",
	"F17",
	"F18",
	"F19",
	"F20",
	"F21",
	"F22",
	"F23",
	"F24",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Numlock",
	"Scroll",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"Left Shift",
	"Right Shift",
	"Left Control",
	"Right Control",
	"Left Menu",
	"Right Menu",
	"Browser back",
	"Browser forward",
	"Browser refresh",
	"Browser stop",
	"Browser search",
	"Browser favorites",
	"Browser home",
	"Volume mute",
	"Volume down",
	"Volume up",
	"Next track",
	"Previous track",
	"Stop track",
	"Play/Pause track",
	"Start mail",
	"Select media",
	"Start app1",
	"Start app2",
	"Reserved",
	"Reserved",
	";:",
	"+",
	",",
	"-",
	".",
	"/?",
	"`~",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Reserved",
	"Unassigned",
	"Unassigned",
	"Unassigned",
	"[{",
	"\\|",
	"]}",
	"\'\"",
	"OEM",
	"Reserved",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"IME",
	"OEM",
	"VK_PACKET",
	"Unassigned",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"OEM",
	"Attn",
	"CrSel",
	"ExSel",
	"EOF",
	"Play",
	"Zoom",
	"Noname",
	"PA1",
	"Clear",
	"None"
};
constexpr const std::string_view& get_key_name(const size_t key_code)
{
	return g_key_codes.at(key_code < g_key_codes.size() ? key_code : 0u);
}
static std::unordered_map<ImGuiID, bool> waitingforkey_hotkey{};
void AddHotkey(const char* label, int* v)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	const ImGuiID id = window->GetID(label);

	auto cursorpos = ImGui::GetCursorPos();
	const ImVec2 pos = window->DC.CursorPos;
	const float check_x = 20.5f;
	const float ContentX = ImGui::GetContentRegionAvail().x;						// ����������
	const ImRect item_bb = { pos, {pos.x + ContentX - g.Style.FramePadding.x, pos.y + check_x + 6.f} };	// �ؼ���С����

	ImGui::ItemSize(item_bb, g.Style.FramePadding.y);
	if (!ImGui::ItemAdd(item_bb, id))
		return;


	ImGui::RenderText(ImVec2(item_bb.Min.x + g.Style.FramePadding.x, item_bb.Min.y + 5.f), label);
	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 3,0 });
	//ImGui::HotKeyButton((size_t*)v);
	ImGui::PushFont(small_font);

	std::string_view keyStr = get_key_name(*v);
	ImVec2 strSize = ImGui::CalcTextSize(keyStr.data(), NULL, true);			// �ı���С
	bool& waitingforkey = waitingforkey_hotkey[id];
	if (waitingforkey == false)
	{
		ImGui::SetCursorPos(ImVec2(cursorpos.x + (ContentX - strSize.x - g.Style.FramePadding.x * 3.f), cursorpos.y + 3.f));
		if (ImGui::Button(get_key_name(*v).data(),{ strSize.x + g.Style.FramePadding.x * 2.f , 20.f }))
			waitingforkey = true;
	}
	else
	{
		strSize = ImGui::CalcTextSize("...", NULL, true);			// �ı���С
		ImGui::SetCursorPos(ImVec2(cursorpos.x + (ContentX - strSize.x - g.Style.FramePadding.x * 3.f), cursorpos.y + 3.f));
		ImGui::Button("...",{strSize.x + g.Style.FramePadding.x * 2.f, 20.f});
		Sleep(20);
		for (size_t i = 0; i < ImGuiKey_COUNT; i++)
		{
			if (!ImGui::IsKeyDown(ImGuiKey(i))) continue;
			switch (i)
			{
			case 655:
				i = 1; break;
			case 656:
				i = 2; break;
			case 657:
				i = 4; break;
			case 658:
				i = 5; break;
			case 659:
				i = 6; break;
			}
			*v = i;
			waitingforkey = false;
			break;
		}
	}
	ImGui::PopFont();
	ImGui::PopStyleVar();
}