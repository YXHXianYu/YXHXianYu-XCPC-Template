/**
 * Created by YXH_XianYu in 2023.10
 * Blog: https://yxhxianyu.fun
*/
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'

typedef double db;

void work() {
	int px, py;
	int ax, ay;
	int bx, by;

	cin >> px >> py >> ax >> ay >> bx >> by;

	auto getDis = [&](db x, db y) {
		return sqrt(x * x + y * y);
	};

	db OA = getDis(ax, ay);
	db OB = getDis(bx, by);
	db AB = getDis(ax - bx, ay - by);
	db AP = getDis(ax - px, ay - py);
	db BP = getDis(bx - px, by - py);

	auto check = [&](db w) -> bool {
		int pina = AP <= w;
		int pinb = BP <= w;
		int oina = OA <= w;
		int oinb = OB <= w;
		int abTog = AB <= (2.0 * w);

		if(!pina && !pinb) return false;
		if(!oina && !oinb) return false;
		if(pina && oina) return true;
		if(pinb && oinb) return true;
		if(abTog) return true;

		return false;
	};

	db L = 0, R = 1e4;
	for(int i = 1; i <= 100; i++) {
		db mid = (L + R) / 2.0;
		if(check(mid)) {
			R = mid;
		} else {
			L = mid;
		}
	}

	cout << fixed << setprecision(10) << R << endl;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t = 1;
	cin >> t;
	while(t--) {
		work();
	}
	
	return 0;
}