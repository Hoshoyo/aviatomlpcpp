#pragma once
#include <common.h>

namespace ho {
namespace game {

	enum class Turn
	{
		T_PLAYER1,
		T_PLAYER2
	};
	
	class HO_API Game
	{
	private:
		Turn turn;
	public:
		Game(Turn turn)
			: turn(turn)
		{
		}

		Game()
			: turn(Turn::T_PLAYER1)
		{
		}

		inline Turn GetTurn() { return turn; }
		inline void SwitchTurn()
		{
			if (turn == Turn::T_PLAYER1)
				turn = Turn::T_PLAYER2;
			else
				turn = Turn::T_PLAYER1;
		}
	};

}}