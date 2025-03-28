#include<iostream>
#include<map>
#include<vector>
using namespace std;
vector<int> singleNumber(vector<int>& nums) {
    int x = 0;
    for (auto& e : nums) {
        x ^= e;
    }
    int cnt = 0;
    int i = 1;
    while (1) {
        int r = i & (x>>cnt);
        if (r == 1) {
            break;
        }
        cnt++;
    }
    int x1 = 0;
    int x2 = 0;
    for (auto& e : nums) {
        if ((e>>cnt) & i) {
            x1 ^= e;
        }
        else {
            x2 ^= e;
        }
    }
    return { x1,x2 };
}
int main() {
	/*pair<int, int> k(1,2);
	map<int, int> test;
	map<int, int>* ptr = &test;
	test.insert(k);
	
	cout << (*((ptr->insert(make_pair(1, int()))).first)).second << endl;
	cout << test[1] << endl;
	
	map<int, int>::iterator it = test.begin();*/
    vector<int> tmp = { 1,2,1,3,2,5 };
    singleNumber(tmp);

	return 0;
}