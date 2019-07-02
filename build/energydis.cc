double f(double x)
{
    double energy[25] = {475, 721, 975, 1033, 1223, 1299, 1551, 1753, 2072, 2503, 2583, 2838, 3088, 3484, 4017, 4224, 4464, 4912, 5177, 5667, 5808, 5909, 6085, 6774, 7517};
    double br[25] = {4.73, 7.39, 0.25, 3, 0.75, 18.51, 0.81, 0.45, 0.48, 0.64, 4.89, 2.11, 1.89, 2.18, 1.078, 0.84, 3.21, 0.27, 0.29, 0.35, 0.18, 0.21, 0.41, 0.41, 0.33};
    double sig = 20;
    double c[25];
    double sum = 0;
    for (int i = 0; i < 25; i++)
    {
        c[i] = br[i] * TMath::Gaus(x, energy[i], sig);
        sum += c[i];
    }
    return sum;
}
void energydis()
{
    TF1 *fa = new TF1("fa", "f(x)", 0, 8000);
    fa->SetNpx(8000);
    fa->Draw();
    TFile *opf = new TFile("edis.root", "recreate");
    TH1F *h = new TH1F("energydis", "energydis", 8000, 0, 8000);
    h->FillRandom("fa", 10000000);
    h->Draw();
    h->Write();
    opf->Close();
}