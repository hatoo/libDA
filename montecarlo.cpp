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

void DA::simulatorInitializer::initialize_fromD3(simulator &sim){
	initialize(sim);
	for(int i=0;i<simulator::playernum;i++){
		if(sim.hands[i]&D3){
			sim.turn = i;
		}
	}
}

int playout_uniform(DA::simulator &sim,int mypos,std::mt19937 &engine){
	DA::Hand buf[256];
	while(!sim.isend(mypos)){
		DA::Cards t = sim.CurrentPlayerHand();
		const int n = validHands(t,sim.ontable,sim.lock,sim.rev,buf);
		if(n==0){
			sim.puthand(DA::PassHand);
		}else if(n==1){
			sim.puthand(buf[0]);
		}else{
			bool f =false;
			for(int k=0;k<n;k++){
				if(buf[k].cards()==t){
					sim.puthand(buf[k]);
					f=true;
					break;
				}
			}
			if(!f){
				std::uniform_int_distribution<int> distribution( 0, n-1 ) ;
				sim.puthand(buf[distribution(engine)]);
			}
		}
	}
	return sim.rank(mypos);
}

DA::Hand DA::montecarlo_uniform(Cards mytefuda,Cards rest,int mypos,const Hand &ontable
	,int *tefudanums,uint8_t passflag,uint8_t goalflag,bool lock,bool rev,int playoutnum){
	std::mt19937 engine( getrandseed() ) ;
	Hand myhands[256];
	Hand buf[256];
	simulatorInitializer siminitter(mytefuda,rest,mypos,ontable,tefudanums,passflag,goalflag,lock,rev);
	simulator sim;

	const int handnum = validHands(mytefuda,ontable,lock,rev,myhands);

	if(handnum==1){//場に何もない時...これで上がる。それ以外...パス
		return myhands[0];
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
				sim.puthand(PassHand);
			}else if(n==1){
				sim.puthand(buf[0]);
			}else{
				bool f =false;
				for(int k=0;k<n;k++){
					if(buf[k].cards()==t){
						sim.puthand(buf[k]);
						f=true;
						break;
					}
				}
				if(!f){
					std::uniform_int_distribution<int> distribution( 0, n-1 ) ;
					sim.puthand(buf[distribution(engine)]);
				}
			}
		}
		
		//int rank = playout_uniform(sim,mypos,engine);
		constexpr double reward[] = {1.0,0.88,0.5,0.11,0.0};
		bandit.putscore(idx,reward[/*rank*/sim.rank(mypos)]);
	}
	return myhands[bandit.bestmean()];
}

int DA::exchanges(Cards tefuda,int num,Cards *out){
	std::vector<Cards> ones;
	for(int i=0;tefuda>>i;i++){
		if((tefuda>>i)&1){
			ones.push_back(u<<i);
		}
	}
	if(num==1){
		std::copy(ones.begin(),ones.end(),out);
		return ones.size();
	}else{
		Cards *ptr = out;
		for(int i=0;i<ones.size();i++){
			for(int k=i+1;k<ones.size();k++){
				*ptr = ones[i] | ones[k];
				ptr++;
			}
		}
		return ptr-out;
	}
}

void doexchange(DA::Cards &greater,DA::Cards &lesser,DA::Cards ex){
	DA::Cards ret = 0;
	{
		int n = 0;
		for(int i = 60;i>0;i++){
			if(lesser&(DA::u<<i)){
				ret |= DA::u<<i;
				n++;
				if(n>=DA::popcnt(ex)){
					break;
				}
			}
		}
	}
	greater^=ex;
	greater|=ret;
	lesser^=ret;
	lesser|=ex;
}

DA::Cards DA::exchange_montecarlo_uniform(DA::Cards tefuda,const int ranks[],int myrank,int playoutnum){
	std::mt19937 engine( getrandseed() ) ;
	int tefudanums[] = {10,10,10,10,10};
	int iranks[5]={0};
	Cards cs[256];
	const int exnum = exchanges(tefuda,myrank==0?2:1,cs);
	for(int i=0;i<5;i++){
		iranks[ranks[i]] = i;
	}
	{
		int d = iranks[0];
		for(int i=0;i<3;i++){
			tefudanums[d] = 11;
			d = (d+1)%5;
		}
	}
	Bandit::UCB1_tuned bandit(exnum);
	const int mypos = iranks[myrank];
	const int aite = iranks[myrank==0?4:3];
	simulatorInitializer siminitter(tefuda,AllCards^tefuda,mypos,PassHand,tefudanums,0,0,false,false);
	simulator sim;
	//Hand buf[256];
	for(int i=0;i<playoutnum;i++){
		const int idx = bandit.next();
		siminitter.initialize_fromD3(sim);
		const Cards e = cs[idx];
		doexchange(sim.hands[mypos],sim.hands[aite],e);
		
		/*while(!sim.isend(mypos)){
			Cards t = sim.CurrentPlayerHand();
			const int n = validHands(t,sim.ontable,sim.lock,sim.rev,buf);
			if(n==0){
				sim.puthand(PassHand);
			}else if(n==1){
				sim.puthand(buf[0]);
			}else{
				bool f =false;
				for(int k=0;k<n;k++){
					if(buf[k].cards()==t){
						sim.puthand(buf[k]);
						f=true;
						break;
					}
				}
				if(!f){
					std::uniform_int_distribution<int> distribution( 0, n-1 ) ;
					sim.puthand(buf[distribution(engine)]);
				}
			}
		}*/
			int rank = playout_uniform(sim,mypos,engine);
		constexpr double reward[] = {1.0,0.88,0.5,0.11,0.0};
		bandit.putscore(idx,reward[rank]);
	}
	return cs[bandit.bestmean()];
}

uint64_t DA::montecarlo_uniform_foreign(uint64_t mytefuda,uint64_t rest,int32_t mypos,uint64_t ontable_bin
	,int32_t *tefudanums,uint8_t passflag,uint8_t goalflag,uint8_t lock,uint8_t rev,int32_t playoutnum){
	const Hand ontable = Hand::fromBin(ontable_bin);
	int tn[5];
	for(int i=0;i<5;i++){
		//std::cout << tefudanums[i] << " ";
		tn[i] = tefudanums[i];
	}
	//std::cout << std::endl;
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

uint64_t DA::exchange_montecarlo_uniform_foreign(uint64_t tefuda,int32_t myrank,int32_t playoutnum){
	int tn[5]={0,1,2,3,4};
	return DA::exchange_montecarlo_uniform(tefuda,tn,myrank,playoutnum);
}