// Graph builder
#include<canvas.cxx>
int main(int style=20)
{
	CreateCanvas();
	Double_t 	x1[100],
			x2[100],
			x3[100],
			x4[100],
			x5[100],
			y1[100],
			y2[100],
			y3[100],
			y4[100],
			y5[100],
			x_err[100],
			y_err[100],
			y1_err[100];

	/*x[0]=0.9;	y[0]=1.11;
	x[1]=1.35;	y[1]=0.2;
	x[2]=1.16;	y[2]=0.3;
	x[3]=1.05;	y[3]=0.4;
	x[4]=0.98;	y[4]=0.5;
	x[5]=0.94;	y[5]=0.6;
	x[6]=0.89;	y[6]=1.0;
	x[7]=0.9;	y[7]=1.5;
	x[8]=0.96;	y[8]=3.0;*/

	/*x[0]=0.92;	y[0]=0.98;
	x[1]=1.36;	y[1]=0.2;
	x[2]=1.06;	y[2]=0.4;
	x[3]=0.99;	y[3]=0.5;
	x[4]=0.95;	y[4]=0.6;
	x[5]=0.91;	y[5]=1.00;
	x[6]=0.93;	y[6]=1.5;
	x[7]=1.02;	y[7]=3;*/

	// width=0.08
	x1[0]=0.2; 	y1[0]=1.67;
	x1[1]=0.4;	y1[1]=1.32;
	x1[2]=0.6;	y1[2]=1.43;
	x1[3]=0.8;	y1[3]=1.73;
	x1[4]=1.0;	y1[4]=2.11;
	x1[5]=1.20;	y1[5]=2.5;
	x1[6]=1.4;	y1[6]=2.87;
	x1[7]=1.6;	y1[7]=3.2;
	x1[8]=1.8;	y1[8]=3.5;
	x1[9]=2.0;	y1[9]=3.77;
	x1[10]=0;	y1[10]=0;
	x1[11]=0;	y1[11]=0;
	// width=0.1
	x2[0]=0.2; 	y2[0]=1.76;
	x2[1]=0.4;	y2[1]=1.3;
	x2[2]=0.6;	y2[2]=1.24;
	x2[3]=0.8;	y2[3]=1.4;
	x2[4]=1.0;	y2[4]=1.67;
	x2[5]=1.20;	y2[5]=1.97;
	x2[6]=1.4;	y2[6]=2.28;
	x2[7]=0.3;	y2[7]=1.47;
	x2[8]=0.25;	y2[8]=1.6;
	x2[9]=0.35;	y2[9]=1.37;
	x2[10]=0.5;	y2[10]=1.23;
	x2[11]=0.7;	y2[11]=1.3;
	// width=0.12
	x3[0]=0.2; 	y3[0]=1.84;
	x3[1]=0.3;	y3[1]=1.55;
	x3[2]=0.4;	y3[2]=1.35;
	x3[3]=0.5;	y3[3]=1.23;
	x3[4]=0.6;	y3[4]=1.18;
	x3[5]=0.7;	y3[5]=1.18;
	x3[6]=0.8;	y3[6]=1.22;
	x3[7]=0.9;	y3[7]=1.29;
	x3[8]=1.0;	y3[8]=1.39;
	x3[9]=1.5;	y3[9]=1.97;
	x3[10]=2.5;	y3[10]=2.55;
	x3[11]=0;	y3[11]=0;
	// width=0.14
	x4[0]=0.2; 	y4[0]=1.92;
	x4[1]=0.4;	y4[1]=1.43;
	x4[2]=0.6;	y4[2]=1.19;
	x4[3]=0.7;	y4[3]=1.15;
	x4[4]=0.9;	y4[4]=1.18;
	x4[5]=1.00;	y4[5]=1.23;
	x4[6]=1.2;	y4[6]=1.37;
	x4[7]=1.6;	y4[7]=1.64;
	x4[8]=0;		y4[8]=0;
	x4[9]=0;		y4[9]=0;
	x4[10]=0;	y4[10]=0;
	x4[11]=0;	y4[11]=0;
	// width=0.16
	x5[0]=0.3; 	y5[0]=1.73;
	x5[1]=0.5;	y5[1]=1.36;
	x5[2]=0.6;	y5[2]=1.25;
	x5[3]=0.7;	y5[3]=1.18;
	x5[4]=0.8;	y5[4]=1.14;
	x5[5]=0.9;	y5[5]=1.14;
	x5[6]=1.3;	y5[6]=1.29;
	x5[7]=1.5;	y5[7]=1.42;
	x5[8]=0;	y5[8]=0;
	x5[9]=0;	y5[9]=0;
	x5[10]=0;	y5[10]=0;
	x5[11]=0;	y5[11]=0;

	for (int k=0;k<12;k++)
	{
		x_err[k]=0;
		y_err[k]=0;
	}


	TGraphErrors *gr1 = new TGraphErrors (12, x1,y1,y_err,x_err);
	TGraphErrors *gr2 = new TGraphErrors (12, x2,y2,y_err,x_err);
	TGraphErrors *gr3 = new TGraphErrors (12, x3,y3,y_err,x_err);
	TGraphErrors *gr4 = new TGraphErrors (12, x4,y4,y_err,x_err);
	TGraphErrors *gr5 = new TGraphErrors (12, x5,y5,y_err,x_err);
	gr1->SetMarkerStyle(style);
	gr2->SetMarkerStyle(style);
	gr3->SetMarkerStyle(style);
	gr4->SetMarkerStyle(style);
	gr5->SetMarkerStyle(style);
	gr1->SetMarkerColor(2);
	gr2->SetMarkerColor(3);
	gr3->SetMarkerColor(4);
	gr4->SetMarkerColor(5);
	gr5->SetMarkerColor(6);
	gr1->Draw("pa");
	gr2->Draw("psame");
	gr3->Draw("psame");
	gr4->Draw("psame");
	gr5->Draw("psame");
	leg = new TLegend(0.4,0.6,0.89,0.89);
    	leg->AddEntry(gr1,"#Gamma (f_{0})=80 MeV","p");
    	leg->AddEntry(gr2,"#Gamma (f_{0})=100 MeV","p");
	leg->AddEntry(gr3,"#Gamma (f_{0})=120 MeV","p");
	leg->AddEntry(gr4,"#Gamma (f_{0})=140 MeV","p");
	leg->AddEntry(gr5,"#Gamma (f_{0})=160 MeV","p");
	leg->Draw("same");
 	//leg->SetHeader("Different cuts comaparing");




//---------------- collinearity 2D ----------------------------------------

/*	x[0]=0.08;
	x[1]=0.09;
	x[2]=0.1;
	x[3]=0.11;
	x[4]=0.12;
	x[5]=0.13;
	x[6]=0.14;
	x[7]=0.15;
	x[8]=0.07;
	x[9]=0.06;
	x[10]=0.05;
	x[11]=0.04;
	x[12]=0.03;

	y[0]=0.898;
	y[1]=0.892;
	y[2]=0.886;
	y[3]=0.881;
	y[4]=0.876;
	y[5]=0.872;
	y[6]=0.867;
	y[7]=0.863;
	y[8]=0.905;
	y[9]=0.912;
	y[10]=0.920;
	y[11]=0.929;
	y[12]=0.938;

	y1[0]=259059.0;
	y1[1]=270641.0;
	y1[2]=280832.0;
	y1[3]=290229.0;
	y1[4]=298633.0;
	y1[5]=306559.0;
	y1[6]=313484.0;
	y1[7]=319981.0;
	y1[8]=245921.0;
	y1[9]=231089.0;
	y1[10]=213248.0;
	y1[11]=191379.0;
	y1[12]=163304.0;
	for(int i=0;i<13;i++) {if (i!=7) y1[i]=y1[i]/y1[7]; cout<<y1[i]<<endl;}
	y1[7]=1;
*/
//--------------------------------------------------------------------------------
//---------------- proton-pion mass combination ----------------------------------
/*
x[0]=1.115;  y1[0]=315239;  y[0]=0.864279;
x[1]=1.116;  y1[1]=315239;  y[1]=0.864279;
x[2]=1.117;  y1[2]=314247;  y[2]=0.868349;
x[3]=1.118;  y1[3]=313128;  y[3]=0.871039;
x[4]=1.119;  y1[4]=312143;  y[4]=0.873156;
x[5]=1.12; y1[5]=311182;  y[5]=0.874879;
x[6]=1.121;  y1[6]=310231;  y[6]=0.876292;
x[7]=1.122;  y1[7]=309254; y[7]=0.877416;
x[8]=1.123;  y1[8]=308314;  y[8]=0.878468;
x[9]=1.124;  y1[9]=307385;  y[9]=0.879632;
x[10]=1.125; y1[10]=306454;  y[10]=0.880673;
x[11]=1.126; y1[11]=305283; y[11]=0.881348;
x[12]=1.127; y1[12]= 304234;  y[12]=0.88232;
x[13]=1.128;  y1[13]=303097; y[13]=0.883055;
x[14]=1.129;  y1[14]=301956;  y[14]=0.88382;
x[15]=1.13;  y1[15]=300791;  y[15]=0.884601;
x[16]=1.131;  y1[16]=299663;  y[16]=0.88549;
x[17]=1.132;  y1[17]=298398;  y[17]=0.886257;
x[18]=1.133; y1[18]= 297199;  y[18]=0.887052;
for(int i=1;i<19;i++) y1[i]=y1[i]/y1[0];
y1[0]=1;
*/
//--------------------------------------------------------------------------------
//----------------- K0s transverse momenta ---------------------------------------
/*x[0]=0.1; y1[0]=316706; y[0]=0.87428;
x[1]=0.115; y1[1]=316413; y[1]=0.874405;
x[2]=0.13; y1[2]=316061; y[2]=0.874688;
x[3]=0.145; y1[3]=315570; y[3]=0.87487;
x[4]=0.16; y1[4]=314859; y[4]=0.875018;
x[5]=0.175; y1[5]=313972; y[5]=0.875191;
x[6]=0.19; y1[6]=312959; y[6]=0.875395;
x[7]=0.205; y1[7]=311880; y[7]=0.875709;
x[8]=0.22; y1[8]=310606; y[8]=0.875968;
x[9]=0.235; y1[9]=309254; y[9]=0.876451;
x[10]=0.25; y1[10]=307746; y[10]=0.876859;
x[11]=0.265; y1[11]=306134; y[11]=0.877226;
x[12]=0.28; y1[12]=304428; y[12]=0.877577;
x[13]=0.295; y1[13]=302566; y[13]=0.877923;
x[14]=0.31; y1[14]=300415; y[14]=0.878154;
x[15]=0.325; y1[15]=298192; y[15]=0.87841;
x[16]=0.34; y1[16]=295858; y[16]=0.878827;
x[17]=0.355; y1[17]=293431; y[17]=0.879103;
x[18]=0.37; y1[18]=290828; y[18]=0.879342;
for(int i=1;i<19;i++) y1[i]=y1[i]/y1[0];
y1[0]=1;
*/
//--------------------------------------------------------------------------------

// ------------------  Pseudorapidity of K0s  -----------------------------------
/*
x[0]=1.1; y1[0]=259221; y[0]=0.899287;
x[1]=1.13; y1[1]=264796; y[1]=0.89773;
x[2]=1.16; y1[2]=270326; y[2]=0.896157;
x[3]=1.19; y1[3]=275705; y[3]=0.894864;
x[4]=1.22; y1[4]=280651; y[4]=0.893216;
x[5]=1.25; y1[5]=285393; y[5]=0.891809;
x[6]=1.28; y1[6]=289916; y[6]=0.890358;
x[7]=1.31; y1[7]=294033; y[7]=0.888789;
x[8]=1.34; y1[8]=297978; y[8]=0.887211;
x[9]=1.37; y1[9]=301668; y[9]=0.885724;
x[10]=1.4; y1[10]=305012; y[10]=0.884471;
x[11]=1.43; y1[11]=308105; y[11]=0.883042;
x[12]=1.46; y1[12]=310726; y[12]=0.881509;
x[13]=1.49; y1[13]=313346; y[13]=0.880327;
x[14]=1.52; y1[14]=315523; y[14]=0.87878;
x[15]=1.55; y1[15]=317339; y[15]=0.877226;
x[16]=1.58; y1[16]=319060; y[16]=0.875918;
x[17]=1.61; y1[17]=320544; y[17]=0.874783;
x[18]=1.64; y1[18]=321885; y[18]=0.873713;
x[19]=1.67; y1[19]=322977; y[19]=0.872619;
x[20]=1.7; y1[20]=323916; y[20]=0.871638;
x[21]=1.73; y1[21]=324679; y[21]=0.870699;
x[22]=1.76; y1[22]=325315; y[22]=0.869787;
x[23]=1.79; y1[23]=325908; y[23]=0.869166;
x[24]=1.82; y1[24]=326402; y[24]=0.868578;
x[25]=1.85; y1[25]=326713; y[25]=0.867928;
x[26]=1.88; y1[26]=326978; y[26]=0.867409;
x[27]=1.91; y1[27]=327239; y[27]=0.867027;
x[28]=1.94; y1[28]=327474; y[28]=0.866738;
x[29]=1.97; y1[29]=327631; y[29]=0.866452;
for(int i=0;i<29;i++) y1[i]=y1[i]/y1[29];
y1[29]=1;
*/
//------------------ Collinearity 3D  --------------------------
/*x[0]=0.05; y1[0]=292425; y[0]=0.950924;
x[1]=0.06; y1[1]=298673; y[1]=0.944126;
x[2]=0.07; y1[2]=303190; y[2]=0.937771;
x[3]=0.08; y1[3]=306546; y[3]=0.932026;
x[4]=0.09; y1[4]=308915; y[4]=0.926129;
x[5]=0.1; y1[5]=311004; y[5]=0.921364;
x[6]=0.11; y1[6]=312602; y[6]=0.916926;
x[7]=0.12; y1[7]=313647; y[7]=0.912197;
x[8]=0.13; y1[8]=314437; y[8]=0.907895;
x[9]=0.14; y1[9]=315051; y[9]=0.903985;
x[10]=0.15; y1[10]=315678; y[10]=0.900234;
x[11]=0.16; y1[11]=316064; y[11]=0.896471;
x[12]=0.17; y1[12]=316489; y[12]=0.893193;
x[13]=0.18; y1[13]=316863; y[13]=0.890022;
x[14]=0.19; y1[14]=317200; y[14]=0.886838;
x[15]=0.2; y1[15]=317437; y[15]=0.883782;
x[16]=0.21; y1[16]=317565; y[16]=0.88053;
x[17]=0.22; y1[17]=317821; y[17]=0.87787;
x[18]=0.23; y1[18]=317973; y[18]=0.875177;
x[19]=0.24; y1[19]=318079; y[19]=0.872484;
x[20]=0.25; y1[20]=318354; y[20]=0.870216;
x[21]=0.26; y1[21]=318422; y[21]=0.867534;
x[22]=0.27; y1[22]=318503; y[22]=0.865052;
x[23]=0.28; y1[23]=318549; y[23]=0.862542;
x[24]=0.29; y1[24]=318633; y[24]=0.860282;
x[25]=0.3; y1[25]=318633; y[25]=0.860282;
x[26]=0.31; y1[26]=318633; y[26]=0.860282;
x[27]=0.32; y1[27]=318633; y[27]=0.860282;
x[28]=0.33; y1[28]=318633; y[28]=0.860282;
x[29]=0.34; y1[29]=318633; y[29]=0.860282;


for(int i=0;i<29;i++) y1[i]=y1[i]/y1[29];
y1[29]=1;*/
//---------------------------------------------------------------------------------
	//TGraphErrors *gr1 = new TGraphErrors (30, x,y,x_err,y_err);
	//TGraphErrors *gr1 = new TGraphErrors (30, y,x,y_err,x_err);
	//gr1->SetMarkerStyle(style);
	//TGraphErrors *gr2 = new TGraphErrors (30, x,y1,x_err,y1_err);
	//gr2->SetMarkerStyle(style+1);
	//gr2->Draw("pa");
	//gr1->Draw("pa");
	//gr1->Draw("psame");
	//leg = new TLegend(0.4,0.6,0.89,0.89);
    	//leg->AddEntry(gr1,"Signal to background","p");
    	//leg->AddEntry(gr2,"Signal/SignalMAX","p");
 	//leg->SetHeader("Different cuts comaparing");
    	//leg->Draw();
	return 0;
}
