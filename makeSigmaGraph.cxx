void setGraph(TGraph* g, int color){
	g->SetMarkerColor(color);
	g->SetLineColor(color);
	g->SetMarkerStyle(20);
	g->SetMarkerSize(0.7);
	g->GetYaxis()->SetRangeUser(-0.2,1.2);
	g->GetYaxis()->SetTitle("Z");
	g->GetXaxis()->SetTitle("#sigma");
	g->SetTitle("");

	return;
}

void makeSigmaGraph(){
	//read files
	TString ifn = "original_0504_cutflow.txt";
	TString ifnl2 = "l2jet_0504_cutflow.txt";
	ifstream fin,finl2;
	std::string str,str2;

	//open files
	fin.open(ifn);
	finl2.open(ifnl2);
	vector<Float_t> sigma;
	vector<Float_t> Z,Zl2;

	//read file
	std::cout << "reading file..." << std::endl;
	float a,b,al2,bl2;
	while(getline(fin,str))
	{
		sscanf(str.data(), "%f\t%f", &a,&b);
		sigma.push_back(a);
		Z.push_back(b);

	}
	while(getline(finl2,str2))
	{
		sscanf(str2.data(), "%f\t%f", &al2,&bl2);
		Zl2.push_back(bl2);

	}

	//set graphs
	int n = sigma.size();
        Float_t* sigmapointer=&(sigma.at(0));
        Float_t* Zpointer=&(Z.at(0));
        Float_t* Zl2pointer=&(Zl2.at(0));
	TGraph *gr = new TGraph(n,sigmapointer,Zpointer);
	TGraph *gr2 = new TGraph(n,sigmapointer,Zl2pointer);

	//set config of grapus
	setGraph(gr,kRed);
	setGraph(gr2,kBlue);

        //set legend
        TLegend *l = new TLegend();
	//draw graphs
	TCanvas *c = new TCanvas("c","c",700,500);
	gr->Draw("APL");
	gr2->Draw("PL same");
        c->Print("SigmaGraph.pdf");

        fin.close();
        finl2.close();

	return;
}
