#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4SDManager.hh"
#include "G4SDChargedFilter.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSTrackLength.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "SensitiveDetector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCheckOverlaps(true)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Define materials
    DefineMaterials();

    // Define volumes

    DefineVolumes();
    DefineVisAttributes();
    fScoringVolume=logicWorld;
    return physicsWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
    G4NistManager* nistManager = G4NistManager::Instance();



    nistManager->FindOrBuildMaterial("G4_Fe");
    nistManager->FindOrBuildMaterial("G4_Au");
    nistManager->FindOrBuildMaterial("G4_Ag");
    nistManager->FindOrBuildMaterial("G4_Cu");
    nistManager->FindOrBuildMaterial("G4_Si");
    nistManager->FindOrBuildMaterial("G4_Cr");
    nistManager->FindOrBuildMaterial("G4_Pb");
    nistManager->FindOrBuildMaterial("G4_Pu");
    nistManager->FindOrBuildMaterial("G4_H");
    nistManager->FindOrBuildMaterial("G4_Al");
    nistManager->FindOrBuildMaterial("G4_lH2");//液氢
    nistManager->FindOrBuildMaterial("G4_lN2");//液氮
    nistManager->FindOrBuildMaterial("G4_lO2");//液氧
    nistManager->FindOrBuildMaterial("G4_lAr");//液氩
    nistManager->FindOrBuildMaterial("G4_Si");
    nistManager->FindOrBuildMaterial("G4_Air");
    nistManager->FindOrBuildMaterial("G4_WATER");
    nistManager->FindOrBuildMaterial("G4_WATER_VAPOR");//水蒸气
    nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");//聚乙烯
    nistManager->FindOrBuildMaterial("G4_BGO");//BGO
    nistManager->FindOrBuildMaterial("G4_CARBON_DIOXIDE");//二氧化碳
    nistManager->FindOrBuildMaterial("G4_LEAD_OXIDE");//氧化铅
    nistManager->FindOrBuildMaterial("G4_MYLAR");//
    nistManager->FindOrBuildMaterial("G4_PLEXIGLASS");//有机玻璃
    nistManager->FindOrBuildMaterial("G4_STAINLESS-STEEL");//不锈钢
    nistManager->FindOrBuildMaterial("G4_LUCITE");//透明合成树脂(有机玻璃)
    nistManager->FindOrBuildMaterial("G4_CONCRETE");//混凝土
    nistManager->FindOrBuildMaterial("G4_GRAPHITE");//石墨
    nistManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");//二氧化硅
    nistManager->FindOrBuildMaterial("G4_RUBBER_NATURAL");//天然橡胶


    nistManager->FindOrBuildMaterial("G4_PbWO4");//
    nistManager->FindOrBuildMaterial("G4_URANIUM_OXIDE");//氧化铀
    nistManager->FindOrBuildMaterial("G4_URANIUM_MONOCARBIDE");//碳化铀
    nistManager->FindOrBuildMaterial("G4_URANIUM_DICARBIDE");//二碳化铀
    nistManager->FindOrBuildMaterial("G4_Galactic");//真空，银河系



    // elements
    G4Element* H = nistManager->FindOrBuildElement("H",false);//1
    G4Element* Li = nistManager->FindOrBuildElement("Li",false);//3
    G4Element* C = nistManager->FindOrBuildElement("C",false);//6
    G4Element* N = nistManager->FindOrBuildElement("N",false);//7
    G4Element* O = nistManager->FindOrBuildElement("O",false);//8
    G4Element* Mg = nistManager->FindOrBuildElement("Mg",false);//12
    G4Element* Al = nistManager->FindOrBuildElement("Al",false);//13
    G4Element* Si = nistManager->FindOrBuildElement("Si",false);//14
    G4Element* P = nistManager->FindOrBuildElement("P",false);//15
    G4Element* S =  nistManager->FindOrBuildElement("S",false);//16
    G4Element* Cr = nistManager->FindOrBuildElement("Cr",false);//24
    G4Element* Mn = nistManager->FindOrBuildElement("Mn",false);//25
    G4Element* Fe = nistManager->FindOrBuildElement("Fe",false);//26
    G4Element* Ni = nistManager->FindOrBuildElement("Ni",false);//28
    G4Element* I = nistManager->FindOrBuildElement("I",false);//53
    G4Element* Cs = nistManager->FindOrBuildElement("Cs",false);//55
    G4Element* Ce = nistManager->FindOrBuildElement("Ce",false);//58


    G4Isotope* U4 = new G4Isotope("U234",92,234,234.02*g/mole);
    G4Isotope* U5 = new G4Isotope("U235",92,235,235.01*g/mole);
    G4Isotope* U6 = new G4Isotope("U236",92,236,236.04*g/mole);
    G4Isotope* U8 = new G4Isotope("U238",92,238,238.03*g/mole);
    G4Element* HEU58 = new G4Element("Highly-enriched Uranium 58", "HEU58", 2);
    HEU58->AddIsotope(U5, 0.93);
    HEU58->AddIsotope(U8, 0.07);

    G4Element* HEU4568 = new G4Element("Highly-enriched Uranium 4568","HEU4568",4);
    HEU4568->AddIsotope(U4,0.0097);
    HEU4568->AddIsotope(U5,0.9315);
    HEU4568->AddIsotope(U6,0.0024);
    HEU4568->AddIsotope(U8,0.0564);


    //Scintillator(BC408) 塑闪
    G4Material* BC408 = new G4Material("BC408", 1.032*g/cm3, 2);
    BC408->AddElement(H, 11);BC408->AddElement(C, 10);
    // BC408->AddElement(H, 10);BC408->AddElement(C, 9);

    // LiquidScint(NE213) 液闪
    G4Material* NE213 = new G4Material("NE213",0.874*g/cm3,2);
    NE213->AddElement(H,1212);
    NE213->AddElement(C,1000);

    // He-3 detector materials
    G4Material* matHe3  = new G4Material("He3",  2., 3.*g/mole, 0.00049*g/cm3, kStateGas);

    // Uranium material
    G4Material* matHEU58 = new G4Material("HEU58", 19.1*g/cm3, 1, kStateSolid);
    matHEU58->AddElement(HEU58, 1.00);

    G4Material* matHEU4568 = new G4Material("HEU4568",18.75*g/cm3,1);
    matHEU4568->AddElement(HEU4568, 1.0);


    G4Material* matSteel = new G4Material("Steel",7.788*g/cm3,9);
    matSteel->AddElement(Fe,62.1805*perCent);
    matSteel->AddElement(Cr,20.26*perCent);
    matSteel->AddElement(Mn,9.37*perCent);
    matSteel->AddElement(Ni,7.5*perCent);
    matSteel->AddElement(Si,0.34*perCent);
    matSteel->AddElement(N,0.29*perCent);
    matSteel->AddElement(C,0.04*perCent);
    matSteel->AddElement(P,0.018*perCent);
    matSteel->AddElement(S,0.0015*perCent);


  new G4Material("liquidArgon", 18., 39.95*g/mole, 1.390*g/cm3);
         // The argon by NIST Manager is a gas with a different density

  // Vacuum
  new G4Material("Galactic", 1.,1.01*g/mole,universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  // Print materials
 // G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

void DetectorConstruction::DefineWorldVolume(G4double x, G4double y, G4double z)
{
    G4Box* solidWorld = new G4Box("World",x/2, y/2, z/2); // its size

    logicWorld
      = new G4LogicalVolume(solidWorld,G4Material::GetMaterial("Galactic"),"World");

    physicsWorld
      = new G4PVPlacement(
                   0,                // no rotation
                   G4ThreeVector(),  // at (0,0,0)
                   logicWorld,          // its logical volume
                   "World",          // its name
                   0,                // its mother  volume
                   false,            // no boolean operation
                   0,                // copy number
                fCheckOverlaps);  // checking overlaps
}

void DetectorConstruction::DefineTargetVolume()
{

}

void DetectorConstruction::DefineVisAttributes()
{
    //
    // Visualization attributes
    //
    logicWorld->SetVisAttributes (G4VisAttributes::GetInvisible());

    auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    simpleBoxVisAtt->SetVisibility(true);
    //calorLV->SetVisAttributes(simpleBoxVisAtt);
}

void DetectorConstruction::DefineSensitiveDetector()
{
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

    auto DSSD142=new SensitiveDetector("DSSD142SD","DSSD142HitsCollection",16*16);
    G4SDManager::GetSDMpointer()->AddNewDetector(DSSD142);
    SetSensitiveDetector("DSSD142_single",DSSD142);


    auto DSSD40=new SensitiveDetector("DSSD40SD","DSSD40HitsCollection",16*16);
    G4SDManager::GetSDMpointer()->AddNewDetector(DSSD40);
    SetSensitiveDetector("DSSD40_single",DSSD40);


    auto DSSD304=new SensitiveDetector("DSSD304SD","DSSD304HitsCollection",16*16);
    G4SDManager::GetSDMpointer()->AddNewDetector(DSSD304);
    SetSensitiveDetector("DSSD304_single",DSSD304);
}

void DetectorConstruction::DefineMagField()
{
    //
    // Magnetic field
    //
    // Create global magnetic field messenger.
    // Uniform magnetic field is then created automatically if
    // the field value is not zero.
    G4ThreeVector fieldValue;
    fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
    fMagFieldMessenger->SetVerboseLevel(1);

    // Register the field messenger for deleting
    G4AutoDelete::Register(fMagFieldMessenger);
}

G4LogicalVolume* DetectorConstruction::DefineDSSD(G4String name,G4int xn, G4int yn, G4double xl, G4double yl, G4double zl, G4double xd, G4double yd)
{
    G4Box* solidSi=new G4Box("Si",xl/2,yl/2,zl/2);
    G4LogicalVolume *logicSi=new G4LogicalVolume(solidSi,G4Material::GetMaterial("G4_Si"),name+"_single");
    G4Box* solidDSSD=new G4Box("DSSD",xn*(xl+xd)/2,yn*(xl+yd)/2,zl/2);

    G4LogicalVolume* logicDSSD=new G4LogicalVolume(solidDSSD,G4Material::GetMaterial("Galactic"),name);
    G4double x0=-(xn-1)*(xd+xl)/2;
    G4double y0=-(yn-1)*(yd+yl)/2;
    for (int i=0;i<xn;i++) {
        for (int j=0;j<yn;j++) {
            G4double xi=x0+i*(xd+xl);
            G4double yj=y0+j*(yd+yl);
            int icrys=i*xn+j;
            new G4PVPlacement(nullptr,
                              G4ThreeVector(xi,yj,0),
                              logicSi,
                              name+"_single",
                              logicDSSD,
                              false,
                              icrys,
                              fCheckOverLaps);
        }
    }
    return logicDSSD;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineVolumes()
{
    // TODO: 修改DSSD的参数，使之与实际DSSD一致。
    DefineWorldVolume(10*cm,10*cm,10*cm);
    //DefineTargetVolume();
    G4LogicalVolume* DSSD142 = DefineDSSD("DSSD142",16,16,3*mm,3*mm,142*um,100*um,100*um);
    new G4PVPlacement(nullptr,
                      G4ThreeVector(0,0,0),
                      DSSD142,
                      "DSSD142",
                      logicWorld,
                      false,
                      0,
                      fCheckOverLaps);
   G4LogicalVolume* DSSD40=DefineDSSD("DSSD40",16,16,3*mm,3*mm,40*um,100*um,100*um);
   new G4PVPlacement(nullptr,
                     G4ThreeVector(0,0,19*mm),
                     DSSD40,
                     "DSSD40",
                     logicWorld,
                     false,
                     0,
                     fCheckOverLaps);
   G4LogicalVolume* DSSD304=DefineDSSD("DSSD304",16,16,3*mm,3*mm,304*um,100*um,100*um);
   new G4PVPlacement(nullptr,
                     G4ThreeVector(0,0,38*mm),
                     DSSD304,
                     "DSSD304",
                     logicWorld,
                     false,
                     0,
                     fCheckOverLaps);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
    DefineSensitiveDetector();
    DefineMagField();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
