#include <cstdint>
#include "Card.h"

#pragma once

namespace DA{
	enum class HandType{
		PASS=0,GROUP=1,STAIR=2
	};
	struct Hand{
		HandType type;
		uint8_t suit;
		uint8_t low;
		uint8_t	high;
		uint8_t joker;
		static constexpr uint8_t nojokerord = 0xff;
		Hand()=default;
		constexpr Hand(HandType _type,uint8_t _suit,uint8_t _low,uint8_t _high,uint8_t _joker):
			type(_type),suit(_suit),low(_low),high(_high),joker(_joker){}
		static constexpr Hand Pass(){
			return Hand(HandType::PASS,0,0,0,0);
		}
		static constexpr Hand Group(uint8_t suit,uint8_t ord,uint8_t jokersuit=0){
			return Hand(HandType::GROUP,suit,ord,ord,jokersuit);
		}
		static constexpr Hand Stair(uint8_t suit,uint8_t low,uint8_t high,uint8_t jokerord=nojokerord){
			return Hand(HandType::STAIR,suit,low,high,jokerord);
		}
		inline bool ispass()const{
			return type==HandType::PASS;
		}
		inline bool isrev()const{
			switch(type){
				case HandType::GROUP:
					return qty()>=4;
				case HandType::STAIR:
					return qty()>=5;
				default:
					return false;
			}
			return false;
		}
		inline int qty()const{
			switch(type){
				case HandType::PASS:
					return 0;
				case HandType::GROUP:
					return popcnt(suit);
				case HandType::STAIR:
					return high-low+1;
			}
			return 0;
		}
		inline Cards cards()const{
			switch(type){
				case HandType::PASS:
					return 0;
				case HandType::GROUP:
					return (joker?JOKER:0ull)|(((Cards)(suit^joker))<<(low*4));//演算子の優先順位知らず
				case HandType::STAIR:
					return ((joker==nojokerord?0:JOKER)|((0x1111111111111111ull>>(4*low)<<(4*low)<<(4*(15-high))>>(4*(15-high)))*suit))^(joker==nojokerord?0:(Cards)suit<<(4*joker));
			}
			return 0;
		}
		bool operator==(const Hand&)const;
		uint64_t toBin()const;
		static Hand fromBin(uint64_t);
	};
	constexpr Hand PassHand = Hand::Pass();
	constexpr Hand SingleJoker = Hand::Group(1,14,1);
	int getGroup(Cards,Hand*);
	int getGroup(Cards tefuda,const Hand &group,bool lock,bool rev,Hand *out);
	int getStair(Cards,Hand*);
	int getStair(Cards tefuda,const Hand &stair,bool lock,bool rev,Hand *out);
	int validHands(Cards,Hand*);
	int validHands(Cards tefuda,const Hand &hand,bool lock,bool rev,Hand *out);
}