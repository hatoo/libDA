#include <random>
//machine learn
namespace ML{
	inline int softmax(const double *vec,int n,std::mt19937 engine){
		double sum = 0;
		for(int i=0;i<n;i++){
			sum+=vec[i];
		}
		std::uniform_real_distribution<double> distribution( 0.0, sum ) ;
		double r = distribution(engine);
		int idx=0;
		while((sum-=vec[idx]) > 0){
			++idx;
		}
		return idx;
	}
}