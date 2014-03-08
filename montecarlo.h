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
/*
	Hand montecarlo_crow(Cards mytefuda,Cards rest,int mypos,const Hand &ontable
		,int *tefudanums,uint8_t passflag,uint8_t goalflag,bool lock,bool rev,int playoutnum);
*/
	int exchanges(Cards tefuda,int num,Cards *out);
	Cards exchange_montecarlo_uniform(Cards tefuda,const int ranks[],int myrank,int playoutnum);

	extern "C" uint64_t montecarlo_uniform_foreign(uint64_t mytefuda,uint64_t rest,int32_t mypos,uint64_t ontable_bin
		,int32_t *tefudanums,uint8_t passflag,uint8_t goalflag,uint8_t lock,uint8_t rev,int32_t playoutnum);
	extern "C" uint64_t exchange_montecarlo_uniform_foreign(uint64_t tefuda,int32_t myrank,int32_t *ranks,int32_t playoutnum);

/*
	extern "C" uint64_t montecarlo_crow_foreign(uint64_t mytefuda,uint64_t rest,int32_t mypos,uint64_t ontable_bin
		,int32_t *tefudanums,uint8_t passflag,uint8_t goalflag,uint8_t lock,uint8_t rev,int32_t playoutnum);
*/

	constexpr double crow_param[166] = {
	// for Normal
	// 5-Sequence
	-0.165103445, -1.367353957, -1.084887944, -0.103446973,  0.005614329, // 3-7
	-0.177613166,  0.020646977, -0.204253239,  0.018329075, // 8-J
	// 4-Sequence
	-1.250221599, -1.305045504, -1.456065252, -0.889654668, -2.987781810, // 3-7
	-1.388516263, -1.176554458, -0.794348341, -2.055029278, -1.890634784, // 8-Q
	// 3-Sequence
	-3.704179332, -4.281589257, -4.719447787, -4.495022219, // 3-6
	-5.089943875, -6.087235981, -2.976696921, -4.422503509, // 7-T
	-4.221070745, -4.222361704, -4.002477132, // J-K
	// Solo, Group(2-4pair)
	-3.902118723, -5.356407798, -4.459366682, -1.673269738, // 3
	-3.813512676, -5.646004771, -4.959193566, -0.598674962, // 4
	-3.707419103, -5.827590172, -5.076551563, -0.455296345, // 5
	-2.914792373, -5.043195734, -4.436616845, -0.790830702, // 6
	-2.659857260, -4.498763022, -3.548758188, -0.164144807, // 7
	-6.162883027, -7.620724057, -6.552047173, -0.409127296, // 8
	-3.377120658, -4.432217918, -3.604395246, -0.447012953, // 9
	-2.931679825, -3.827014698, -2.405417588, -0.186615449, // T
	-2.977701799, -3.088013233, -1.833889336, -0.034788011, // J
	-3.180260758, -2.933643112, -1.445919210,  0.025592376, // Q
	-3.039855900, -2.900483696, -1.851938754,  0.005744616, // K
	-2.396018281, -2.156369375, -1.014889482,  0.035431113, // A
	-2.386842708, -2.704110364, -2.010499011, -0.169877329, // 2
	 0.557952043, // JOKER
	// for Revolution
	// 5-Sequence
	 0.015941512, -0.076186286, -1.869357120, -0.280747683, -0.003119470, // 3-7
	-0.892415555,  0.001491174, -0.634278907, -1.064733776, // 8-J
	// 4-Sequence
	-1.496744051, -0.825525999, -2.733283880, -0.894995405, -1.898804633, // 3-7
	-1.538144313, -1.025547067, -0.837688942, -1.185448678, -3.504837011, // 8-Q
	// 3-Sequence
	-4.213282878, -3.897294649, -4.012261980, -4.517719657, // 3-6
	-5.015807231, -5.507484021, -4.051525440, -4.608462404, // 7-T
	-4.057425508, -4.326998459, -5.129364509, // J-K
	// Solo, Group(2-4pair)
	-2.415693628, -2.782669751, -1.843946193, -0.004313174, // 3
	-2.704387616, -2.350158654, -1.209685749,  0.019062053, // 4
	-3.187466989, -2.919736669, -1.705203490, -0.060453580, // 5
	-3.442788490, -3.467241349, -2.027801109, -0.012216187, // 6
	-3.321312748, -3.495115522, -2.244767429, -0.129789376, // 7
	-5.744447193, -5.757793499, -5.355164182, -2.659961621, // 8
	-3.147674227, -3.078045473, -2.287018461, -0.368540465, // 9
	-2.965633813, -4.850912354, -3.522098268,  0.016110389, // T
	-3.047409384, -4.952092305, -4.031908245, -0.387839210, // J
	-3.378235820, -5.678286406, -4.574724270, -0.436443491, // Q
	-3.720091654, -6.173770806, -5.468976055, -0.706931919, // K
	-4.073372779, -6.424423870, -5.079275011, -0.898643720, // A
	-4.051587944, -5.937719397, -5.274388701, -2.298538090, // 2
	 0.848130302, // JOKER
	};
}