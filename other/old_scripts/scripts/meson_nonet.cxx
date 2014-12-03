int main(float size_hor=0.125,float size_vert=0.25)
{
	//draw meson nonet

	float	x[20],
		y[20];

	x[0]=0.5-size_hor; y[0]=0.5+size_vert;
	x[1]=0.5+size_hor; y[1]=0.5+size_vert;
	x[2]=0.5+2*size_hor; y[2]=0.5;
	x[3]=0.5+size_hor; y[3]=0.5-size_vert;
	x[4]=0.5-size_hor; y[4]=0.5-size_vert;
	x[5]=0.5-2*size_hor; y[5]=0.5;
	x[6]=0.5-size_hor; y[6]=0.5+size_vert;
	TGraph *g=new TGraph(7,x,y);
	g->SetMarkerStyle(20);
	g->Draw("lp");
	Float_t		arr1_x1,
			arr1_x2,
			arr1_y1,
			arr1_y2;

	arr1_x1=0.5;
	arr1_y1=0.5-size_vert-0.1;
	arr1_x2=0.5;
	arr1_y2=0.5+size_vert+0.15;
	TArrow *vert=new TArrow(arr1_x1,arr1_y1,arr1_x2,arr1_y2,0.03);
	vert->SetAngle(30);
	vert->Draw("same");

	Float_t		arr2_x1,
			arr2_x2,
			arr2_y1,
			arr2_y2;

	arr2_x1=0.5-2*size_hor-0.1;
	arr2_y1=0.5;
	arr2_x2=0.5+2*size_hor+0.12;
	arr2_y2=0.5;
	TArrow *hor=new TArrow(arr2_x1,arr2_y1,arr2_x2,arr2_y2,0.03);
	hor->SetAngle(30);
	hor->Draw("same");

	//TLatex *lat1=new TLatex(0,0,"\pi");
	//TLatex *lat1=new TLatex();
	//lat1->Draw("same");
	//lat1->PaintLatex(0,0,"\pi");
	TLatex latex;
   	//latex.SetTextSize(0.025);
   	//latex.SetTextAlign(13);  //align at top
   	latex.DrawLatex(x[0]-0.03,y[0]+0.02,"K^{0}");
	latex.DrawLatex(x[1]+0.01,y[1]+0.02,"K^{+}");
	latex.DrawLatex(x[2]+0.01,y[2]+0.02,"#pi^{+}");
	latex.DrawLatex(x[3]+0.01,y[3]-0.06,"#bar{K^{0}}");
	latex.DrawLatex(x[4]-0.03,y[3]-0.06,"K^{-}");
	latex.DrawLatex(x[5]-0.03,y[5]+0.02,"#pi^{-}");
	latex.DrawLatex(0.5-0.04,y[2]+0.02,"#pi^{0}");
	latex.DrawLatex(0.5+0.02,y[2]+0.02,"#eta");
	latex.DrawLatex(0.5+0.02,y[2]-0.05,"#eta'");

	latex.DrawLatex(arr2_x2-0.01,arr2_y2-0.06,"I_{3}");
	latex.DrawLatex(arr1_x2-0.04,arr1_y2-0.03,"S");

	latex.DrawLatex(x[2],y[2]-0.06,"1");
	latex.DrawLatex(x[5]-0.03,y[2]-0.06,"-1");

	latex.DrawLatex(0.5-0.03,y[0]+0.02,"1");
	latex.DrawLatex(0.5-0.03,y[3]-0.06,"-1");

	latex.DrawLatex(0.08,0.8,"J^{PC}=0^{-+}");

	return 0;
}