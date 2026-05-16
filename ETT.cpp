vector<vector<int>> neighbors;
vector<int> start;
vector<int> end;
int timer = 0;

void euler_tour(int at, int prev) {
	start[at] = timer++;
	for (int n : neighbors[at]) {
		if (n != prev) { euler_tour(n, at); }
	}
	end[at] = timer;
}
