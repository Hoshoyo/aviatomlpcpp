#pragma once
#include <common.h>
#include <glm/glm.hpp>

namespace ho {

#define NUM_KEYS 1024

	struct HO_API Input
	{
		static bool Keys[NUM_KEYS];
		static glm::vec2 mouse_pos;
		static bool left_mouse_down;
		static bool right_mouse_down;

		static bool left_click;

		static void SetLeftMouse(bool set)
		{
			left_mouse_down = set;
		}
	};

#define A_KEY 'A'
#define B_KEY 'B'
#define C_KEY 'C'
#define D_KEY 'D'
#define E_KEY 'E'
#define F_KEY 'F'
#define G_KEY 'G'
#define H_KEY 'H'
#define I_KEY 'I'
#define J_KEY 'J'
#define K_KEY 'K'
#define L_KEY 'L'
#define M_KEY 'M'
#define N_KEY 'N'
#define O_KEY 'O'
#define P_KEY 'P'
#define Q_KEY 'Q'
#define R_KEY 'R'
#define S_KEY 'S'
#define T_KEY 'T'
#define U_KEY 'U'
#define V_KEY 'V'
#define W_KEY 'W'
#define X_KEY 'X'
#define Y_KEY 'Y'
#define Z_KEY 'Z'
#define UP_KEY 38
#define DOWN_KEY 40
#define LEFT_KEY 37
#define RIGHT_KEY 39
#define SHIFT_KEY 16
#define SPACE_KEY 32
}