#include "ucb1_tuned.h"
#include <vector>
#include <cmath>
#include <algorithm>

double Bandit::UCB1_record::v(int n){
	if(n==0 || j==0){
		return MAX_V;
	}
	const double ave = sum/j;
	const double avesqr = sumsqr/j;
	const double a = sqrt(2*log(n)/j);
	const double right = std::min(0.25,avesqr-ave*ave+a);
	const double left = log(n)/j;
	return ave+sqrt(left*right);
}

void Bandit::UCB1_record::put(double s){
	++j;
	sumsqr+=s*s;
	sum+=s;
}

int Bandit::UCB1_tuned::next(){
	int idx = 0;
	double mv = 0;
	for(int i=0;i<records.size();i++){
		double v = records[i].v(n);
		if(mv<v){
			idx = i;
			mv = v;
		}
	}
	return idx;
}

int Bandit::UCB1_tuned::putscore(int idx,double score){
	++n;
	records[idx].put(score);
}