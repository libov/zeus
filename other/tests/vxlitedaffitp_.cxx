  void vxlitedaffitp_(int& ntracks,float track_par[VXLITE_MAXTRACKS][5],
		      float track_cov[VXLITE_MAXTRACKS][15],float track_p[VXLITE_MAXTRACKS],
		      float vertex[3],float vertex_cov[6],float& chi2_cut,int& mode,float& chi2,
		      float& ndof,float weights[VXLITE_MAXTRACKS],
		      float constrained_track_par[VXLITE_MAXTRACKS][3],float constrained_track_p[VXLITE_MAXTRACKS], float& mass )
  { 
    static DAFVertexFinder finder;
    
    finder.setChi2Cut(chi2_cut);
    for(int i = 0 ; i < ntracks ; ++i) {
      finder.addTrack(new LinearizedTrack(i+1,track_par[i],track_cov[i]));
    }    
    
    double sumofweights = 0;
    
    if(mode == 1) {
      //with vertex constraint
      HepVector xin(3);
      xin[0] =  vertex[0];
      xin[1] =  vertex[1];
      xin[2] =  vertex[2];
      HepSymMatrix covxin(3);
      covxin[0][0] = vertex_cov[0];
      covxin[0][1] = vertex_cov[1];
      covxin[1][1] = vertex_cov[2];
      covxin[0][2] = vertex_cov[3];
      covxin[1][2] = vertex_cov[4];
      covxin[2][2] = vertex_cov[5];
      
      sumofweights =  finder.findVertex(xin,covxin);
    } else {
      sumofweights =  finder.findVertex();
    }
    const VertexFitter* fitter = finder.fitter();
    if(sumofweights == 0) {     
      for(int i = 0 ; i < 3 ; ++i ) vertex[i] = 0;
      for(int i = 0 ; i < 6 ; ++i ) vertex_cov[i] = 0;
      for(int i = 0 ; i < ntracks ; ++i) {
	constrained_track_par[i][0] = 0;
	constrained_track_par[i][1] = 0;
	constrained_track_par[i][2] = 0;
	constrained_track_p[i] = 0;
	weights[i] = 0;
      }
      ndof = 0;
      chi2 = 9999999;
      mass = 0;
      finder.reset();
      return ;
    }
    vertex[0] = fitter->vertex()[0];
    vertex[1] = fitter->vertex()[1];
    vertex[2] = fitter->vertex()[2];
    vertex_cov[0] = fitter->covariance()[0][0];
    vertex_cov[1] = fitter->covariance()[0][1];
    vertex_cov[2] = fitter->covariance()[1][1];
    vertex_cov[3] = fitter->covariance()[0][2];
    vertex_cov[4] = fitter->covariance()[1][2];
    vertex_cov[5] = fitter->covariance()[2][2];
    chi2 = fitter->chi2();
    ndof = fitter->ndof();
    HepLorentzVector p(0,0,0,0);
    for(int i = 0 ; i < ntracks ; ++i) {
      const LinearizedTrack* t = finder.track(i);
      if(! t->expanded()) {
	assert(t->weight() == 0);
	constrained_track_par[i][0] = 0;//theta
	constrained_track_par[i][1] = 0;//phi
	constrained_track_par[i][2] = t->charge() * 999999;//Q/R
	weights[i] = 0;
	continue;
      }
      constrained_track_par[i][0] = M_PI_2 - atan(t->q()[2]);//theta
      constrained_track_par[i][1] = (t->q()[0] < 0) ? 2 * M_PI + t->q()[0] : t->q()[0];//phi
      constrained_track_par[i][2] = t->q()[1];//Q/R
      weights[i] = t->weight();   
      HepLorentzVector tp = t->momentum(track_p[i]);
      constrained_track_p[i] = tp.v().mag();
      p +=  t->weight() * tp;
    }    
    mass = p.m();
    finder.reset();
  }
