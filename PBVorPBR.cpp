#include <iostream>
#include <vector>

using namespace std;

void fnPBV(vector<int>){}

void fnPBR(vector<int>*){}

int main(){

	vector<int> v(10000000, 144);

	fnPBV(v);

	fnPBR(&v);

	return 0;
}
