db intergal(db x,db y,db r,db L,db R){
    return r*r*(R-L) + x*r*(sinl(R) - sinl(L)) + y*r*(-cosl(R) + cosl(L));
}

db calc_area_circle(P c,db r,db L,db R){
	return intergal(c.x,c.y,r,L,R) / 2;
}

db norm(db x){
	while(x < 0) x += 2 * PI;
	while(x > 2 * PI) x -= 2 * PI;
	return x;
}

P cs[N]; db rs[N];

void work(){
	vector<int> cand = {};
	rep(i,0,m){
		bool ok = 1;
		rep(j,0,m) if(i!=j){
			if(rs[j] > rs[i] + EPS && rs[i] + cs[i].distTo(cs[j]) <= rs[j] + EPS){
				ok = 0; break;
			}
			if(cs[i] == cs[j] && cmp(rs[i],rs[j]) == 0 && j < i){
				ok = 0; break;
			}
		}
		if(ok) cand.pb(i);
	}

	rep(i,0,cand.size()) cs[i] = cs[cand[i]], rs[i] = rs[cand[i]];
	m = cand.size();

	db area = 0;

	//work
	rep(i,0,m){
		vector<pair<db,int> > ev = {{0,0},{2*PI,0}};

		int cur = 0;

		rep(j,0,m) if(j!=i){
			auto ret = isCC(cs[i],rs[i],cs[j],rs[j]);
			if(!ret.empty()){
				db l = (ret[0] - cs[i]).alpha();
				db r = (ret[1] - cs[i]).alpha();
				l = norm(l); r = norm(r);
				ev.pb({l,1});ev.pb({r,-1});
				if(l > r) ++cur;
			}
		}

		sort(ev.begin(), ev.end());
		rep(j,0,ev.size() - 1){
			cur += ev[j].se;
			if(cur == 0){
				area += calc_area_circle(cs[i],rs[i],ev[j].fi,ev[j+1].fi);
			}
		}
	}
}