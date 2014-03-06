#include "Card.h"
#include "Hand.h"
#include <cstdint>
#include <algorithm>

#pragma once
namespace DA{
	struct simulator{
		static constexpr int playernum = 5;
		Cards hands[playernum];
		Hand ontable;
		uint8_t goalflag;
		uint8_t passflag;
		int turn;
		bool lock;
		bool rev;
		simulator(const Cards* inithands,const Hand &_ontable,bool _goalflag,bool _passflag
			,int _turn,bool _lock,bool _rev):ontable(_ontable),goalflag(_goalflag)
			,passflag(_passflag),turn(_turn),lock(_lock),rev(_rev){
				std::copy(inithands,inithands+playernum,hands);
			}
		simulator():ontable(PassHand),goalflag(0),passflag(0),turn(0),lock(false),rev(false){
			std::fill(hands,hands+playernum,0ull);
		}
		inline Cards CurrentPlayerHand()const{
			return hands[turn];
		}
		void puthand(const Hand&);
		inline void reset(){
			lock = false;
			ontable = PassHand;
			passflag = goalflag;
		}
		void initializeRandom();
		inline bool isend(int pos){
			return ((goalflag&(1<<pos))!=0)||popcnt(goalflag)>=(playernum-1);
		}
		inline int rank(int pos){//return 0-4
			return (goalflag&(1<<pos))!=0?popcnt(goalflag)-1:playernum-1;
		}
	};
}