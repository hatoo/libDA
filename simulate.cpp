#include "simulate.h"
#include "Card.h"
#include "Hand.h"
#include <cstdint>
#include <vector>
#include <algorithm>
#include <random>

inline bool resethand(DA::Cards ontable,DA::Cards put){
	if(put&DA::Eights){
		return true;
	}
	if(ontable==DA::JOKER&&put==DA::S3){
		return true;
	}
	return false;
}

inline int nextturn(int turn,uint8_t flag){
	if(flag==((1<<DA::simulator::playernum)-1)){
		return turn;
	}
	do{
		turn=(turn+1)%DA::simulator::playernum;
	}while((flag&(1<<turn))!=0);
	return turn;
}

void DA::simulator::puthand(const Hand& hand){
	Cards cs = hand.cards();
	Cards tefuda = CurrentPlayerHand()^cs;
	Cards tablecards = ontable.cards();
	hands[turn] = tefuda;

	lock = lock||ontable.suit==hand.suit;
	if(hand.qty()>=4){
		rev = !rev;
	}
	if(tefuda==0){
		//上がり!!
		goalflag|=1<<turn;
		passflag|=goalflag;
		if(resethand(tablecards,cs) || popcnt(passflag)==playernum){
			reset();
		}
		turn = nextturn(turn,passflag);
	}else{
		if(resethand(tablecards,cs)){
			reset();
		}else{
			if(cs){
				ontable = hand;
				turn = nextturn(turn,passflag);
			}else{
				//pass
				passflag|=(1<<turn);
				if(popcnt(passflag)==playernum){
					reset();
				}else{
					turn = nextturn(turn,passflag);
				}
			}
		}
	}
}

void DA::simulator::initializeRandom(){
	std::random_device rd;
	std::mt19937 mt(rd());
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
