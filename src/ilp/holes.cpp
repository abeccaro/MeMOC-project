#include <cstdio>
#include <iostream>
#include <vector>
#include "cpxmacro.h"
#include "../TSPData.h"

using namespace std;

int status;
char errmsg[BUF_SIZE];
const int NAME_SIZE = 512;
char name[NAME_SIZE];


void setupLP(CEnv env, Prob lp, const TSPData& data) {
    const int N = data.size();
    double C[N*N];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            C[i*N+j] = data.cost(i,j);

	// x variables
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			char xtype = 'C';
			double obj = 0.0;
			double lb = 0.0;
			double ub = CPX_INFBOUND;
			snprintf(name, NAME_SIZE, "x_%d_%d", i, j);
			char* xname = (char*)(&name[0]);
			CHECKED_CPX_CALL(CPXnewcols, env, lp, 1, &obj, &lb, &ub, &xtype, &xname);
		}
	}
	
	// y variables
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			char xtype = 'B';
			double lb = 0.0;
			double ub = 1.0;
			snprintf(name, NAME_SIZE, "y_%d_%d", i, j);
			char* xname = (char*)(&name[0]);
			CHECKED_CPX_CALL( CPXnewcols, env, lp, 1, &C[i*N+j], &lb, &ub, &xtype, &xname );
		}
	}
	

	// First constraint {x_0j = N}
	std::vector<int> idx(N);
	std::vector<double> coef(N, 1.0);
	char sense = 'E';
	double value = N;
	for (int j = 0; j < N; j++)
		idx[j] = j; // x_0j
	int matbeg = 0;
	CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &value, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
	
	// Second constraint {foreach k: SUM_i (x_ik) - SUM_j (x_kj) = 1}
	for (int k = 1; k < N; k++) {
		std::vector<int> idx(2*N);
		std::vector<double> coef(2*N);
		for (int i = 0; i < N; i++) {
			idx[i] = i*N + k; // x_ik
			coef[i] = 1.0;
		}
		for (int j = 0; j < N; j++) {
			idx[N+j] = k*N + j; // x_kj
			coef[N+j] = -1.0;
		}
		double value = 1.0;
		char sense = 'E';
		int matbeg = 0;
		CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &value, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
	}
	
	// Third constraint {foreach i: SUM_j (y_ij) = 1}
	for (int i = 0; i < N; i++) {
		std::vector<int> idx(N);
		std::vector<double> coef(N, 1.0);
		double value = 1.0;
		char sense = 'E';
		for (int j = 0; j < N; j++)
			idx[j] = N*N + i*N + j; // y_ij
		int matbeg = 0;
		CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &value, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
	}
	
	// Fourth constraint {foreach j: SUM_i (y_ij) = 1}
	for (int j = 0; j < N; j++) {
		std::vector<int> idx(N);
		std::vector<double> coef(N, 1.0);
		double value = 1.0;
		char sense = 'E';
		for (int i = 0; i < N; i++)
			idx[i] = N*N + i*N + j; // y_ij
		int matbeg = 0;
		CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &value, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
	}
	
	// Fifth constraint {foreach i,j: x_ij - N * y_ij <= 0}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			std::vector<int> idx(2);
			std::vector<double> coef(2);
			idx[0] = i*N + j;		// x_ij
			idx[1] = N*N + i*N + j;	// y_ij
			coef[0] = 1.0;
			coef[1] = -N;
			double value = 0.0;
			char sense = 'L';
			int matbeg = 0;
			CHECKED_CPX_CALL(CPXaddrows, env, lp, 0, 1, idx.size(), &value, &sense, &matbeg, &idx[0], &coef[0], NULL, NULL);
		}
	}
}


int main (int argc, char const *argv[]) {
	try {
		// init
		DECL_ENV( env );
		DECL_PROB( env, lp );
		
		// read input data
		if (argc < 2)
		    throw std::runtime_error("usage: ./main filename.dat");
		TSPData data;
		data.read(argv[1]);
		
		// setup LP
		std::cout << "Calculating..." << std::endl;
		setupLP(env, lp, data);
		
		// optimize
		CHECKED_CPX_CALL( CPXmipopt, env, lp );
		
		// print
		double objval;
		CHECKED_CPX_CALL( CPXgetobjval, env, lp, &objval );
		std::cout << std::endl << "Optimal objval: " << objval << std::endl;
		
		int n = CPXgetnumcols(env, lp);
		if (n != 2 * data.size() * data.size())
		    throw std::runtime_error(std::string(__FILE__) + ":" + STRINGIZE(__LINE__) + ": " + "different number of variables");
	  	std::vector<double> varVals;
		varVals.resize(n);
  		CHECKED_CPX_CALL( CPXgetx, env, lp, &varVals[0], 0, n - 1 );
		/// status =      CPXgetx (env, lp, x          , 0, CPXgetnumcols(env, lp)-1);
  	  		
  	  	// output file.sol
		CHECKED_CPX_CALL( CPXsolwrite, env, lp, "ilp.sol" );
		
		// free
		CPXfreeprob(env, &lp);
		CPXcloseCPLEX(&env);
	} catch(std::exception& e) {
		std::cout << ">>>EXCEPTION: " << e.what() << std::endl;
	}

	return 0;
}

