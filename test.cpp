#include <gtest/gtest.h>
#include "Card.h"
#include "Hand.h"
#include "montecarlo.h"
#include "simulate.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <set>

using namespace DA;

void dump(Cards cs){
	char prefixs[] = "SHDC";
	int nums[] = {0,3,4,5,6,7,8,9,10,11,12,13,1,2,99,99,99,99};
	std::cout << "[ ";
	for(int i=0;i<52+4;i++){
		if((cs>>i)&1)
		std::cout << prefixs[i%4] << std::dec << nums[i/4] << " ";
	}
	if(cs&JOKER){
		std::cout << "JOKER";
	}
	std::cout << " ]" << std::endl;
}

void dump(const Hand &h){
	switch(h.type){
		case HandType::PASS:
			std::cout << "type:Pass ";
			break;
		case HandType::GROUP:
			std::cout << "type:Group ";
			break;
		case HandType::STAIR:
			std::cout << "type:Stair ";
			break;
		default:
			std::cout << "type:broken("<<(int)h.type<<") ";
	}
	std::cout << "low: " << (int)h.low << " ";
	std::cout << "high: " << (int)h.high << " ";
	std::cout << "joker: " << (int)h.joker << " ";
	dump(h.cards());
}

void dump(const simulator &sim){
	std::cout << "ontable: ";
	dump(sim.ontable);
	for(int i=0;i<simulator::playernum;i++){
		std::cout << "player[" << i << "] has ";
		dump(sim.hands[i]);
	}
	std::cout << "turn: " << sim.turn << std::endl;
	std::cout << "pass: " << std::hex << (int)sim.passflag << " goalflag: " << (int)sim.goalflag;
	std::cout << " lock: " << (int)sim.lock << " rev: " << (int)sim.rev << std::endl;
}

TEST(popcnt,test){
	ASSERT_EQ(popcnt(0x111full),7);
}

TEST(SingleJoker,cards){
	ASSERT_EQ(SingleJoker.cards(),JOKER);
}

TEST(PassHand,cards){
	ASSERT_EQ(PassHand.cards(),0ull);
}

TEST(Hand,Bin){
	Hand h = Hand(HandType::GROUP,2,3,4,5);
	Hand h2 = Hand::fromBin(h.toBin());
	ASSERT_EQ(h,h2);
}

TEST(Hand_Group,qty){
	Hand h = Hand::Group(0x1,1);
	ASSERT_EQ(h.qty(),1);
	h = Hand::Group(0xf,4,0x1);
	ASSERT_EQ(h.qty(),4);
}

TEST(Hand_Group,cards){
	Hand h = Hand::Group(0x1,1);
	ASSERT_EQ(h.cards(),0x10ull);
	h = Hand::Group(0xf,1,0x1);
	ASSERT_EQ(h.cards(),JOKER|0xe0ull);
}

TEST(Hand_Stair,qty){
	Hand h = Hand::Stair(0x1,1,3);
	ASSERT_EQ(h.qty(),3);
}

TEST(Hand_Stair,cards){
	Hand h = Hand::Stair(0x1,1,3);
	ASSERT_EQ(h.cards(),0x1110ull);
	h = Hand::Stair(0x1,1,3,2);
	ASSERT_EQ(h.cards(),0x1010ull|JOKER);
}

TEST(getGroup,size){
	//ASSERT_EQ(a,1);
	Hand hs[256];
	int ret = getGroup(0x10ull,hs);
	ASSERT_EQ(ret,1);
	ASSERT_EQ(hs[0].cards(),0x10ull);
	ret = getGroup(0x10ull|JOKER,hs);
	ASSERT_EQ(ret,5);
}

TEST(getGroup,sim){
	Hand hs[256];
	int ret = getGroup(0x100ull,Hand::Group(1,1,0),false,false,hs);
	ASSERT_EQ(ret,1);
	ret = getGroup(0x100ull,Hand::Group(1,10,0),false,false,hs);
	ASSERT_EQ(ret,0);
}

TEST(getStair,size){
	Hand hs[512];
	int ret = getStair(0x1110ull,hs);
	ASSERT_EQ(ret,1);
	ret = getStair(0xfff0ull,hs);
	ASSERT_EQ(ret,4);
	ret = getStair(0xff00ull|JOKER,hs);
	ASSERT_EQ(ret,8);
}

TEST(getStair,sim){
	Hand hs[512];
	Hand h = Hand::Stair(1,1,3,Hand::nojokerord);
	int ret = getStair(0x1111000ull,h,false,false,hs);
	ASSERT_EQ(ret,1);
	ret = getStair(0x2222000ull,h,true,false,hs);
	ASSERT_EQ(ret,0);
	ret = getStair(0x1111000ull,h,false,true,hs);
	ASSERT_EQ(ret,0);
}

TEST(getGroup,random){
	Hand hs[512];
	std::random_device rd;
	std::mt19937_64 mt(rd());
	for(int i=0;i<1000;i++){
		Cards tefuda = mt()&((JOKER<<1)-1)&(~0xfull);//i==0?0x10100d220082100ull:mt()&((JOKER<<1)-1)&(~0xfull);
		int num = getGroup(tefuda,hs);
		ASSERT_LT(num,512);
		Cards t = 0;
		for(int k=0;k<num;k++){
			t|=hs[k].cards();
			//std::cout << std::hex << hs[k].cards() << std::endl;
			//std::cout << std::hex << (int)hs[k].suit << " " << (int)hs[k].low << " " << (int)hs[k].joker << std::endl; 
			EXPECT_EQ(hs[k].cards()&0xfull,0);
			EXPECT_EQ(popcnt(hs[k].cards()),hs[k].qty());
		}
		//std::cout << std::hex << (tefuda^t) << std::endl;
		ASSERT_EQ(tefuda,t);
	}
}

TEST(getStair,random){
	Hand hs[512];
	std::random_device rd;
	std::mt19937_64 mt(rd());
	for(int i=0;i<1000;i++){
		Cards tefuda = mt()&((JOKER<<1)-1)&(~0xfull);
		int num = getStair(tefuda,hs);
		Cards t = 0;
		for(int k=0;k<num;k++){
			t|=hs[k].cards();
			//std::cout << std::hex << hs[k].cards() << std::endl;
			//std::cout << std::hex << (int)hs[k].suit << " " << (int)hs[k].low << " " << (int)hs[k].high
			//	<<" "<< (int)hs[k].joker << std::endl; 
			EXPECT_EQ(hs[k].cards()&0xfull,0);
			EXPECT_EQ(popcnt(hs[k].cards()),hs[k].qty());
		}
		ASSERT_EQ(tefuda&t,t);
	}
}

TEST(validHands,1){
	Hand hs[512];
	int num = validHands(0xffffffffff0ull,Hand::Group(4,1),true,false,hs);
	for(int i=0;i<num;i++){
		if(!hs[i].ispass()){
			if(hs[i].suit!=4){
				std::cout << i << std::endl;
				FAIL();
			}
		}
	}
}

TEST(simulator,randominit){
	simulator sim;
	for(int k=0;k<100;k++){
		sim.initializeRandom();
		for(int i=0;i<sim.playernum;i++){
			ASSERT_EQ(sim.hands[i]&0xf,0);
			ASSERT_EQ(sim.hands[i]&(~((JOKER<<1)-1)),0);
		}
	}
}

TEST(simulator,finitetime){
	std::mt19937_64 mt(1234);
	simulator sim;
	Hand hs[512];
	int counts[5]={0};
	for(int i=0;i<10000;i++){
		sim.initializeRandom();
		int n = 0;
		uint8_t prevgoal = sim.goalflag;
		while(popcnt(sim.goalflag)<simulator::playernum){
			for(int k=0;k<simulator::playernum;k++){
				if(sim.goalflag&(1<<k)){
					ASSERT_EQ(sim.hands[k],0);
					ASSERT_EQ(sim.passflag&(1<<k),1<<k);
					ASSERT_EQ(sim.isend(k),true);
				}
			}
			counts[sim.turn]++;
			EXPECT_TRUE((sim.ontable.cards()&Eights)==0);
			Cards tefuda = sim.CurrentPlayerHand();
			ASSERT_EQ(tefuda&0xf,0);
			ASSERT_EQ(tefuda&(~((JOKER<<1)-1)),0);
			int num = validHands(tefuda,sim.ontable,sim.lock,sim.rev,hs);
			if(num>0){
				for(int k=0;k<num;k++){
					ASSERT_LT(hs[k].suit ,0x10);
					ASSERT_EQ(hs[k].cards()&0xf,0);
					EXPECT_EQ(hs[k].cards()&0xfull,0);
					EXPECT_EQ(hs[k].cards()&tefuda,hs[k].cards());
					if((hs[k].cards()&tefuda)!=hs[k].cards()){
						FAIL();
					}

					EXPECT_EQ(popcnt(hs[k].cards()),hs[k].qty());
					
					if(!hs[k].ispass()&& !(sim.ontable.cards()==JOKER&&hs[k].cards()==S3)){
						if(sim.rev){
							EXPECT_LT((int)hs[k].low,(int)sim.ontable.low);
						}else{
							EXPECT_LT((int)sim.ontable.low,(int)hs[k].low);
						}
					}
					if(!hs[k].ispass()&& !(sim.ontable.cards()==JOKER) && hs[k].cards()!=JOKER){
						if(sim.lock){
							ASSERT_EQ(hs[k].suit,sim.ontable.suit);
						}
					}
				}
				std::uniform_int_distribution<int> distribution( 0, num-1 );
				sim.puthand(hs[distribution(mt)]);
			}else{
				FAIL();
				sim.puthand(PassHand);
			}
			EXPECT_EQ(prevgoal,prevgoal&sim.goalflag);
			EXPECT_EQ(sim.passflag&sim.goalflag,sim.goalflag);
			prevgoal = sim.goalflag;
			if(++n > 1000){
				std::cout << std::hex 
				<< " turn:" << sim.turn
				<< " goal:" << (int)sim.goalflag 
				<< " pass:" << (int)sim.passflag 
				<< " passcount: " << (int)popcnt(sim.passflag) 
				<< " tefudacount " 
				<< popcnt(sim.hands[0]) << " " 
				<< popcnt(sim.hands[1]) << " "
				<< popcnt(sim.hands[2]) << " "
				<< popcnt(sim.hands[3]) << " "
				<< popcnt(sim.hands[4]) << " "
				<< std::endl;
				FAIL();
				break;
			}
		}
	}
	for(int i=0;i<5;i++){
		//std::cout << counts[i] << " " ;
	}
	//std::cout << std::endl;
}

TEST(simulator,humancheck){
	/*
	std::mt19937_64 mt(1234);
	simulator sim;
	Hand hs[512];
	int counts[5]={0};
	for(int i=0;i<1;i++){
		sim.initializeRandom();
		while(popcnt(sim.goalflag)<simulator::playernum){
			counts[sim.turn]++;
			Cards tefuda = sim.CurrentPlayerHand();
			ASSERT_EQ(tefuda&0xf,0);
			ASSERT_EQ(tefuda&(~((JOKER<<1)-1)),0);
			int num = validHands(tefuda,sim.ontable,sim.lock,sim.rev,hs);
			if(num>0){
				std::uniform_int_distribution<int> distribution( 0, num-1 );
				auto r = distribution(mt);
				auto h = hs[r];
				dump(sim);
				std::cout << "choose " << std::dec << r << "/" << num-1 << std::endl;
 				dump(h);
				std::cout << std::endl;
				sim.puthand(h);
			}else{
				FAIL();
				sim.puthand(PassHand);
			}
		}
	}*/
}

TEST(simulatorInitializer,initialize){
	Cards mytefuda = 0xf0ull;
	Cards rest = 0xffff00ull;
	int numtefudas[] = {4,4,4,4,4};
	simulatorInitializer si(mytefuda,rest,0,PassHand,numtefudas,0,0,false,false);
	simulator sim;
	Cards cs[5];
	for(int i=0;i<100;i++){
		si.initialize(sim);
		int sum = 0;
		Cards all = 0ull;
		for(int i=0;i<5;i++){
			EXPECT_EQ(popcnt(sim.hands[i]),4);
			sum+=popcnt(sim.hands[i]);
			all |= sim.hands[i];
			for(int k=i+1;k<5;k++){
				EXPECT_EQ(sim.hands[i]&sim.hands[k],0);
			}
		}
		EXPECT_EQ(sum,20);
		EXPECT_EQ(all,0xfffff0ull);
		EXPECT_EQ(sim.CurrentPlayerHand(),mytefuda);
		EXPECT_EQ(std::equal(cs,cs+5,sim.hands),false);
		std::copy(sim.hands,sim.hands+5,cs);
	}
}

TEST(ucb1_tuned,weaktest){
	Bandit::UCB1_tuned ut(100);
	std::set<int> idxs;
	for(int i=0;i<1000;i++){
		const int idx = ut.next();
		ut.putscore(idx,1.0/100*idx);
		idxs.insert(idx);
	}
	EXPECT_EQ(idxs.size(),100);
	EXPECT_EQ(ut.next(),99);
}

TEST(montecarlo_uniform,finitetime){
	simulator sim;
	for(int i=0;i<10;i++){
		sim.initializeRandom();
		Cards rest = 0;
		int nums[simulator::playernum];
		for(int i=1;i<simulator::playernum;i++){
			rest |= sim.hands[i];
			nums[i] = popcnt(sim.hands[i]);
		}
		/*Hand montecarlo_uniform(Cards mytefuda,Cards rest,int mypos,const Hand &ontable
			,int *tefudanums,uint8_t passflag,uint8_t goalflag,bool lock,bool rev,int playoutnum);*/
		montecarlo_uniform(sim.hands[0],rest,0,sim.ontable,nums,sim.passflag,sim.goalflag,sim.lock,sim.rev,5000);
	}
}

TEST(montecarlo_uniform,lock){
	simulator sim;
	for(int i=0;i<10;i++){
		sim.initializeRandom();
		sim.lock = true;
		sim.ontable = Hand::Group(1,1);
		Cards rest = 0;
		int nums[simulator::playernum];
		for(int i=1;i<simulator::playernum;i++){
			rest |= sim.hands[i];
			nums[i] = popcnt(sim.hands[i]);
		}
		/*
Hand montecarlo_uniform(Cards mytefuda,Cards rest,int mypos,const Hand &ontable
			,int *tefudanums,uint8_t passflag,uint8_t goalflag,bool lock,bool rev,int playoutnum);
		*/
auto h = montecarlo_uniform(sim.hands[0],rest,0,sim.ontable,nums,sim.passflag,sim.goalflag,sim.lock,sim.rev,5000);
if(!h.ispass()){
	if(h.suit!=sim.ontable.suit){
		std::cout << std::hex
		<< (int)sim.ontable.type << " "
		<< (int)sim.ontable.suit << " "
		<< (int)sim.ontable.low << " "
		<< (int)sim.ontable.high << " "
		<< (int)sim.ontable.joker << std::endl;
		std::cout << std::hex
		<< (int)h.type << " "
		<< (int)h.suit << " "
		<< (int)h.low << " "
		<< (int)h.high << " "
		<< (int)h.joker << std::endl;
		FAIL();
	}
}
}
}

TEST(exchange,t){
	for(int i=0;i<20;i++){
		simulator sim;
		sim.initializeRandom();
		auto h = sim.hands[0];
		int ranks[] = {0,1,2,3,4};
		auto e = exchange_montecarlo_uniform(h,ranks,0,4000);
		ASSERT_EQ(popcnt(e),2);
		ASSERT_EQ(h&e,e);
	}
}
TEST(exchange,foreign){
	for(int n=1;n<=2;n++)
	for(int i=0;i<20;i++){
		simulator sim;
		sim.initializeRandom();
		auto h = sim.hands[0];
		auto e = exchange_montecarlo_uniform_foreign(h,n==2?0:1,4000);
		ASSERT_EQ(popcnt(e),n);
		ASSERT_EQ(h&e,e);
	}
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}