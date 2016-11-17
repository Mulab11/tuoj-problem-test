#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

double a, b;
double out_ans, std_ans;

int main(int argc, char **argv) {
	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "r");
	FILE *ans = fopen(argv[3], "r");
	FILE *scr = fopen(argv[4], "w");
	FILE *log = fopen(argv[5], "w");

	fscanf(in, "%lf %lf", &a, &b);
	fscanf(out, "%lf", &out_ans);
	fscanf(ans, "%lf", &std_ans);
	
	double err = out_ans - std_ans;
	double score = 0;
	if (abs(err) < 1e-5)
		score = 1;
	
	fprintf(scr, "%.10lf", score);
	fprintf(log, "err = %.10lf", err); 	

	fclose(scr);
	fclose(log);
}
