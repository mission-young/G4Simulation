
TH3F *rebin(vector<TH3F *> h)
{
    const int hn = 3;
    int zn[hn];
    int zntmp = hn;
    for (int i = 0; i < hn; i++)
    {
        zn[i] = h[i]->GetNbinsZ();
        zntmp += zn[i];
    }
    const int zbn = zntmp;
    int zw[hn], zmin[hn];
    for (int i = 0; i < hn; i++)
    {
        zw[i] = h[i]->GetZaxis()->GetBinWidth(1);
        zmin[i] = h[i]->GetZaxis()->GetXmin();
    }
    float binz[zbn];
    int id = 0;
    for (int i = 0; i < hn; i++)
    {
        for (int j = 0; j < zn[i] + 1; j++)
        {
            binz[j + id] = zmin[i] + j * zw[i];
        }
        id += zn[i] + 1;
    }

    const int xn = h[0]->GetNbinsX() + 1;
    float binx[xn];
    int xw = h[0]->GetXaxis()->GetBinWidth(1);
    int xmin = h[0]->GetXaxis()->GetXmin();
    for (int i = 0; i < xn; i++)
        binx[i] = xmin + i * xw;

    const int yn = h[0]->GetNbinsY() + 1;
    float biny[yn];
    int yw = h[0]->GetYaxis()->GetBinWidth(1);
    int ymin = h[0]->GetYaxis()->GetXmin();
    for (int i = 0; i < yn; i++)
        biny[i] = ymin + i * yw;

    TH3F *hnew = new TH3F("hnew", "hnew", xn - 1, binx, yn - 1, biny, zbn - 1, binz);

    for (int i = 0; i < hn; i++)
        for (int j = 1; j < xn; j++)
            for (int k = 1; k < yn; k++)
                for (int l = 1; l <= zn[i]; l++)
                    hnew->Fill(
                        h[i]->GetXaxis()->GetBinCenter(j),
                        h[i]->GetYaxis()->GetBinCenter(k),
                        h[i]->GetZaxis()->GetBinCenter(l),
                        h[i]->GetBinContent(j, k, l));
    return hnew;
}

TH3F *merge()
{
    static TFile *f = new TFile("pos2.root", "update");
    TTree *tree = (TTree *)f->Get("tree");
    tree->Draw("z:y:x>>h1(250,-25000,25000,250,-25000,25000,150,0,150)", "iz==1");
    tree->Draw("z:y:x>>h2(250,-25000,25000,250,-25000,25000,70,19000,19070)", "iz==2");
    tree->Draw("z:y:x>>h3(250,-25000,25000,250,-25000,25000,170,37990,38160)", "iz==3");
    vector<TH3F *> vet;
    vet.push_back((TH3F *)gROOT->FindObject("h1"));
    vet.push_back((TH3F *)gROOT->FindObject("h2"));
    vet.push_back((TH3F *)gROOT->FindObject("h3"));
    return rebin(vet);
}