{
    tree->Draw("be>>b0(2000,0,8000)","cond==1&&bz==1&&dtime<1000");
    tree->Draw("be>>b1(2000,0,8000)","cond==1&&bz==1&&dtime>1000");
    TH1D *al1=new TH1D("al1","be cond==1 bz==1",2000,0,8000);
    al1->Add(b0,b1,1,-1);
    tree->Draw("be>>b2(2000,0,8000)","cond==1&&bz==2&&vsum[0]<200&&dtime<1000");
    tree->Draw("be>>b3(2000,0,8000)","cond==1&&bz==2&&vsum[0]<200&&dtime>1000");
    TH1D *al2=new TH1D("al2","be cond==1 bz==2",2000,0,8000);
    al2->Add(b2,b3,1,-1);
    
    tree->Draw("bea>>b4(2000,0,8000)","cond==1&&bz==1&&dtime<1000");
    tree->Draw("bea>>b5(2000,0,8000)","cond==1&&bz==1&&dtime>1000");
    TH1D *al3=new TH1D("al3","bea cond==1 bz==1",2000,0,8000);
    al3->Add(b4,b5,1,-1);
    tree->Draw("bea>>b6(2000,0,8000)","cond==1&&bz==2&&vsum[0]<200&&dtime<1000");
    tree->Draw("bea>>b7(2000,0,8000)","cond==1&&bz==2&&vsum[0]<200&&dtime>1000");
    TH1D *al4=new TH1D("al4","bea cond==1 bz==2",2000,0,8000);
    al4->Add(b6,b7,1,-1);

    tree->Draw("be>>b8(2000,0,8000)","cond==2&&bz==1&&dtime<1000");
    tree->Draw("be>>b9(2000,0,8000)","cond==2&&bz==1&&dtime>1000");
    TH1D *al5=new TH1D("al5","be cond==2 bz==1",2000,0,8000);
    al5->Add(b8,b9,1,-1);


    tree->Draw("be>>b10(2000,0,8000)","cond==2&&bz==2&&vsum[0]<200&&dtime<1000");
    tree->Draw("be>>b11(2000,0,8000)","cond==2&&bz==2&&vsum[0]<200&&dtime>1000");
    TH1D *al6=new TH1D("al6","be cond==2 bz==2",2000,0,8000);
    al6->Add(b10,b11,1,-1);

    tree->Draw("be>>b12(2000,0,8000)","cond==3&&dtime<1000&&vsum[0]<200");
    tree->Draw("be>>b13(2000,0,8000)","cond==3&&dtime>1000&&vsum[0]<200");
    TH1D *al7=new TH1D("al7","be cond==3",2000,0,8000);
    al7->Add(b12,b13,1,-1);

    TH1D *al8=new TH1D("al8","al1+al5",2000,0,8000);
    al8->Add(al1,al5,1,1);

    TH1D *al9=new TH1D("al9","al2+al6",2000,0,8000);
    al9->Add(al2,al6,1,1);

    TH1D *al10=new TH1D("al10","al8+al7",2000,0,8000);
    al10->Add(al8,al7,1,1);

    TH1D *al11=new TH1D("al11","al9+al7",2000,0,8000);
    al11->Add(al9,al7,1,1);

    TH1D *al12=new TH1D("al12","al3+al5",2000,0,8000);
    al12->Add(al3,al5,1,1);

    TH1D *al13=new TH1D("al13","al4+al6",2000,0,8000);
    al13->Add(al4,al6,1,1);

    TH1D *al14=new TH1D("al14","al12+al7",2000,0,8000);
    al14->Add(al12,al7,1,1);

    TH1D *al15=new TH1D("al15","al13+al7",2000,0,8000);
    al15->Add(al13,al7,1,1);
    /*
    al10->GetXaxis()->SetRangeUser(201,2000);
    al10->ShowBackground(40);
    TH1D *bkg1=(TH1D*)gROOT->FindObject("al10_background");
    TH1D *al16=new TH1D("al16","al10-bkg1",2000,0,8000);
    al16->Add(al10,bkg1,1,-1);

    al11->GetXaxis()->SetRangeUser(201,2000);
    al11->ShowBackground(40);
    TH1D *bkg2=(TH1D*)gROOT->FindObject("al11_background");
    bkg2->GetXaxis()->SetRangeUser(0,8000);
    TH1D *al17=new TH1D("al17","al11-bkg2",2000,0,8000);
    al17->Add(al11,bkg2,1,-1);
   */
    TFile *f=new TFile("al.root","recreate");
    al1->Write();
    al2->Write();
    al3->Write();
    al4->Write();
    al5->Write();
    al6->Write();
    al7->Write();
    al8->Write();
    al9->Write();
    al10->Write();
    al11->Write();
    al12->Write();
    al13->Write();
    al14->Write();
    al15->Write();
   // al16->Write();
   // al17->Write();
   // bkg1->Write();
   // bkg2->Write();
    f->Close();
}
