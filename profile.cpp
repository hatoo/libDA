#include "montecarlo.h"
#include "simulate.h"
#include "Card.h"
#include "Hand.h"

int main(){
	DA::simulator sim;
	for(int i=0;i<100;i++){
		sim.initializeRandom();
		DA::Cards rest = 0;
		int nums[DA::simulator::playernum];
		for(int i=1;i<DA::simulator::playernum;i++){
			rest |= sim.hands[i];
			nums[i] = DA::popcnt(sim.hands[i]);
		}
		DA::montecarlo_uniform(sim.hands[0],rest,0,sim.ontable,nums,sim.passflag,sim.goalflag,sim.lock,sim.rev,5000);
	}
}