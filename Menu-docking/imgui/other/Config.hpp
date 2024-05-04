#pragma once

namespace config
{
	namespace menu_color
	{
		inline float theme_col[3] = {.12f,.89f,.17f };
		inline float begin_title_col[3] = { 0.07f, 0.07f, 0.08f };
		inline float begin_bgcol[3] = { 0.04f, 0.05f, 0.05f };
		inline float begin_left_bgcol[3] = { 0.04f, 0.05f, 0.05f };
		inline float begin_right_bgcol[3] = { 0.04f, 0.04f, 0.05f };
	}

	namespace legitbot
	{
		inline bool aim_enable = true;
		inline bool tig_enable = true;
		inline bool rec_enable = true;

		inline float aim_zoom_dis = 200.f;
		inline float aim_hip_dis = 50.f;
		inline int aim_key_1 = 1;
		inline int aim_key_2 = 5;

		inline float tig_dis = 100.f;
		inline int tig_key = 5;
		
		inline bool hitbox_adv = false;
		inline bool hitbox_advidx[7] = {};
		inline int  hitbox_idx = 1;

		inline float recoil_x = 0.85f;
		inline float recoil_y = 0.85f;
	}
}