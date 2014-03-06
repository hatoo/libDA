#include "simulate.h"
#include "Card.h"
#include "Hand.h"
#include <cstdint>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

inline bool resethand(DA::Cards ontable,DA::Cards put){
	if((put&DA::Eights)!=0){
		return true;
	}
	if(ontable==DA::JOKER&&put==DA::S3){
		return true;
	}
	return false;
}

inline int nextturn(int turn,uint8_t flag){
	if(flag==((1<<DA::simulator::playernum)-1)){
		std::cout << "debug" << std::endl;
		return turn;
	}
	do{
		turn=(turn+1)%DA::simulator::playernum;
	}while((flag&(1<<turn))!=0);
	return turn;
}

void DA::simulator::puthand(const Hand& hand){
	constexpr uint8_t fullraise = (1<<playernum)-1;

	if(hand.ispass()){
		passflag |= 1<<turn;
		if(passflag==fullraise){
			reset();
		}else{
			turn = nextturn(turn,passflag);
		}
	}else{
		lock = lock||(ontable.suit==hand.suit);
		if(hand.isrev()){
			rev = !rev;
		}
		const Cards cs = hand.cards();
		const Cards tefuda = CurrentPlayerHand()^cs;
		const Cards tablecards = ontable.cards();
		hands[turn] = tefuda;
		ontable = hand;
		if(tefuda==0ull){
			goalflag |= 1<<turn;
			passflag |= goalflag;
			if(goalflag==fullraise){
				return;
			}else{
				if(passflag==fullraise||resethand(tablecards,cs)){
					reset();
				}
				turn = nextturn(turn,passflag);
			}
		}else{
			if(resethand(tablecards,cs)){
				reset();
			}else{
				turn = nextturn(turn,passflag);
			}
		}
		
	}
		/*
	if(hand.ispass()){
		passflag |= 1<<turn;
		if(passflag==fullraise){
			reset();
		}else{
			turn = nextturn(turn,passflag);
		}
	}else{
		lock = lock||(ontable.suit==hand.suit);
		if(hand.isrev()){
			rev = !rev;
		}
		const Cards cs = hand.cards();
		const Cards tefuda = CurrentPlayerHand()^cs;
		const Cards tablecards = ontable.cards();
		hands[turn] = tefuda;
		if(tefuda==0ull){
			goalflag |= 1<<turn;
		}
		if(goalflag==fullraise)return;
		if(resethand(tablecards,cs)){
			reset();
			if(tefuda==0ull){
				turn = nextturn(turn,passflag);
			}
		}else{
			if(passflag==fullraise){
				reset();
			}else{
				ontable = hand;
			}
			turn = nextturn(turn,passflag);
		}
	}
	*/
}

void DA::simulator::initializeRandom(){
	std::random_device rd;
	std::mt19937 mt(159);
	std::fill(hands,hands+playernum,0ull);
	constexpr int yamasize = 53;
	int yama[yamasize];
	for(int i=0;i<yamasize;i++){
		yama[i] = i;
	}
	std::shuffle(yama,yama+yamasize,mt);
	for(int i=0;i<yamasize;i++){
		hands[i%playernum] |= (u<<(yama[i]+4));
	}
	lock = false;
	rev = false;
	ontable = PassHand;
	passflag = 0;
	goalflag = 0;
	turn = 0;
}
