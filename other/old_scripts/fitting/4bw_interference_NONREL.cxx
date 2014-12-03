Double_t bw_interference(Double_t *x,Double_t *par)
{
	Double_t		M[5],
					G[5];

	// Parameters of bw-functions
	M[1]=par[0];	// M1
	G[1]=par[1];	// G1

	M[2]=par[2];	// M2
	G[2]=par[3];	// G2

	M[3]=par[4];	// M3
	G[3]=par[5];	// G3

	Double_t			ReBW[5],	// Real part of ith peak
						ImBW[5],	// Imaginary part of ith peak
						den[5];		// denominator of ith peak

	Double_t		m=x[0];		// function variable

	// each bw-function calculation
	for (int i=1;i<4;i++)
	{
		den[i]=(m-M[i])**2+(G[i]/2)**2;
		ReBW[i]=sqrt(G[i])*(m-M[i])/den[i];
		ImBW[i]=-sqrt(G[i])*(G[i]/2)/den[i];
	}

	Double_t			ReTensor=0,
						ImTensor=0;
	ReTensor=5*ReBW[1]-3*ReBW[2]+2*ReBW[3];
	ImTensor=5*ImBW[1]-3*ImBW[2]+2*ImBW[3];

	Double_t	total=0;
	total=par[6]*(ReTensor**2+ImTensor**2);
	return	total;

}
Double_t bw(Double_t *x,Double_t *par)
{
	Double_t		M=par[0]; 	// peak position
	Double_t		G=par[1]; 	// peak width
	Double_t		m=x[0];		// function variable
	Double_t		ReBW=0,		// Real part of ith peak
					ImBW=0,		// Imaginary part of ith peak
					den=0;		// denominator of ith peak
	Double_t		temp1=0,
					temp2=0;

		den=(m-M)**2+(G/2)**2;
		ReBW=sqrt(G)*(m-M)/den;
		ImBW=-sqrt(G)*(G/2)/den;


	Double_t	total=0;
	total=par[2]*(ReBW**2+ImBW**2);
	return	total;
}
