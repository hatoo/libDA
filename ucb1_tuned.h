#include <vector>
#include <cmath>
#include <cfloat>

#pragma once

namespace Bandit{
	constexpr double MAX_V = DBL_MAX;
	class UCB1_record{
		int j;
		double sumsqr;
		double sum;
	public:
		UCB1_record():j(0),sumsqr(0),sum(0){}
		double v(int n);
		void put(double s);
		double mean()const{
			return j>0?sum/j:0;
		}
	};

	class UCB1_tuned{
		int n;
		std::vector<UCB1_record> records;
	public:
		UCB1_tuned(int num):n(0),records(num){}
		int next();
		int bestmean();
		int putscore(int idx,double score);
	};
}