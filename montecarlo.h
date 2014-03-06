#include "Hand.h"
#include "Card.h"
#include "ucb1_tuned.h"
#include "simulate.h"
#include <cstdint>
#include <random>
#include <algorithm>
#include <chrono>
#include <vector>

#pragma once

namespace DA{
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
			unsigned seed1 = 1000000;//std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 engine( seed1 ) ;
			mt = engine;

			for(int i=0;(rest>>i)!=0;i++){
				if(((rest>>i)&1ull) == 1){
					yama.push_back(u<<i);
				}
			}
			tefudanums[mypos] = 0;
		}
		void initialize(simulator &sim);
	};
	Hand montecarlo_uniform(Cards mytefuda,Cards rest,int mypos,const Hand &ontable
			,int *tefudanums,uint8_t passflag,uint8_t goalflag,bool lock,bool rev,int playoutnum);

	extern "C" uint64_t montecarlo_uniform_foreign(Cards mytefuda,Cards rest,int mypos,uint64_t ontable_bin
			,int *tefudanums,uint8_t passflag,uint8_t goalflag,bool lock,bool rev,int playoutnum);
}