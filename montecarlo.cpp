#include "montecarlo.h"
#include <algorithm>
#include <vector>
#include "ucb1_tuned.h"
#include <random>
#include "Hand.h"
#include "Card.h"
#include <iostream>

void DA::simulatorInitializer::initialize(simulator &sim){
	std::shuffle(yama.begin(),yama.end(),mt);

	std::fill(sim.hands,sim.hands+simulator::playernum,0ull);
	auto itr = yama.begin();
	for(int i=0;i<simulator::playernum;i++){
		const int num = tefudanums[i];
		for(int k=0;k<num;k++){
			sim.hands[i] |= *itr;
			itr++;
		}
	}
	sim.hands[mypos] = mytefuda;
	sim.ontable = ontable;
	sim.goalflag = goalflag;
	sim.passflag = passflag;
	sim.turn = mypos;
	sim.lock = lock;
	sim.rev = rev;
}

DA::Hand DA::montecarlo_uniform(Cards mytefuda,Cards rest,int mypos,const Hand &ontable
			,int *tefudanums,uint8_t passflag,uint8_t goalflag,bool lock,bool rev,int playoutnum){
	std::mt19937 engine( 2525 ) ;
	Hand myhands[256];
	Hand buf[256];
	simulatorInitializer siminitter(mytefuda,rest,mypos,ontable,tefudanums,passflag,goalflag,lock,rev);
	simulator sim;

	const int handnum = validHands(mytefuda,ontable,lock,rev,myhands);
	if(handnum==0){
		return PassHand;
	}
	Bandit::UCB1_tuned bandit(handnum);
	for(int i=0;i<playoutnum;i++){
		const int idx = bandit.next();
		siminitter.initialize(sim);
		sim.puthand(myhands[idx]);
		while(!sim.isend(mypos)){
			Cards t = sim.CurrentPlayerHand();
			const int n = validHands(t,sim.ontable,sim.lock,sim.rev,buf);
			if(n==0){
				//std::cout << "pass " << std::hex << (int)sim.goalflag <<  std::endl;
				sim.puthand(PassHand);
			}else{
				std::uniform_int_distribution<int> distribution( 0, n-1 ) ;
				sim.puthand(buf[distribution(engine)]);
			}
		}
		constexpr double reward[] = {1,1,0.5,0,0};
		bandit.putscore(idx,reward[sim.rank(mypos)]);
	}
	return myhands[bandit.next()];
}

uint64_t DA::montecarlo_uniform_foreign(uint64_t mytefuda,uint64_t rest,int32_t mypos,uint64_t ontable_bin
			,int32_t *tefudanums,uint8_t passflag,uint8_t goalflag,uint8_t lock,uint8_t rev,int32_t playoutnum){
	const Hand ontable = Hand::fromBin(ontable_bin);
	int tn[5];
	for(int i=0;i<5;i++){
		tn[i] = tefudanums[i];
	}
	/*
	std::cout << (int)lock << " " << (int)rev << " " 
	<< (int) ontable.suit << " "
	<< std::hex << (int)ontable.type
	<<std::endl;
	*/
	const Hand ret = montecarlo_uniform(mytefuda,rest,mypos,ontable,tn,passflag,goalflag,lock,rev,playoutnum);
/*	
	std::cout << std::hex 
	<< (int)ret.type << " " 
	<< (int)ret.suit << " "
	<< (int)ret.low << " "
	<< (int)ret.high << " "
	<< (int)ret.joker
	<<std::endl;
*/
	return ret.toBin();
}