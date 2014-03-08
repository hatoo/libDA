#include "Hand.h"
#include "Card.h"
#include "ucb1_tuned.h"
#include "simulate.h"
#include <cstdint>
#include <random>
#include <algorithm>
#include <chrono>
#include <vector>
#include <ctime>

#pragma once

namespace DA{
	inline uint64_t getrandseed(){
		return time(NULL);//chronoはmingw64で試してみたところ追加でdllが必要になったので使わない。
	}
	class simulatorInitializer{
		std::vector<Cards> yama;
		
		std::mt19937 mt;
		Cards mytefuda;
		Cards rest;
		int mypos;

		Hand ontable;
		int tefudanums[simulator::playernum];
		uint8_t passflag;
		uint8_t goalflag;
		int turn;
		bool lock;
		bool rev;
	public:
		simulatorInitializer(Cards _mytefuda,Cards _rest,int _mypos,const Hand &_ontable
			,int *_tefudanums,uint8_t _passflag,uint8_t _goalflag,bool _lock,bool _rev)
		:mytefuda(_mytefuda),rest(_rest),mypos(_mypos),ontable(_ontable),passflag(_passflag),goalflag(_goalflag),lock(_lock),rev(_rev){
			std::copy(_tefudanums,_tefudanums+simulator::playernum,tefudanums);
			std::mt19937 engine( getrandseed() ) ;
			mt = engine;
			rest = rest & (~mytefuda);
			for(int i=0;(rest>>i)!=0;i++){
				if(((rest>>i)&1ull) == 1){
					yama.push_back(u<<i);
				}
			}
			tefudanums[mypos] = 0;
		}
		void initialize(simulator &sim);
		void initialize_fromD3(simulator &sim);
	};

	//int playout_uniform(simulator &sim,int mypos);
	Hand montecarlo_uniform(Cards mytefuda,Cards rest,int mypos,const Hand &ontable
			,int *tefudanums,uint8_t passflag,uint8_t goalflag,bool lock,bool rev,int playoutnum);

	int exchanges(Cards tefuda,int num,Cards *out);
	Cards exchange_montecarlo_uniform(Cards tefuda,const int ranks[],int myrank,int playoutnum);

	extern "C" uint64_t montecarlo_uniform_foreign(uint64_t mytefuda,uint64_t rest,int32_t mypos,uint64_t ontable_bin
			,int32_t *tefudanums,uint8_t passflag,uint8_t goalflag,uint8_t lock,uint8_t rev,int32_t playoutnum);
	extern "C" uint64_t exchange_montecarlo_uniform_foreign(uint64_t tefuda,int32_t myrank,int32_t playoutnum);

}