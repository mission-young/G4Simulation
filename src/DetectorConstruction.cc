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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal
G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = 0;

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
    fScoringVolume=calorLV;
    return physicsWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
    G4NistManager* nistManager = G4NistManager::Instance();

    nistManager->FindOrBuildMaterial("G4_AIR");
    nistManager->FindOrBuildMaterial("G4_WATER");

    nistManager->FindOrBuildMaterial("G4_Al");
    nistManager->FindOrBuildMaterial("G4_Fe");
    nistManager->FindOrBuildMaterial("G4_Au");
    nistManager->FindOrBuildMaterial("G4_Ag");
    nistManager->FindOrBuildMaterial("G4_Cu");
    nistManager->FindOrBuildMaterial("G4_Si");
    nistManager->FindOrBuildMaterial("G4_Cr");
    nistManager->FindOrBuildMaterial("G4_Pb");


  // Liquid argon material
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;
  G4double density;
  new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density= 1.390*g/cm3);
         // The argon by NIST Manager is a gas with a different density

  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

  // Print materials
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

void DetectorConstruction::DefineWorldVolume(G4double x, G4double y, G4double z)
{
    // Geometry parameters
    G4int  nofLayers = 10;
    G4double  absoThickness = 10.*mm;
    G4double  gapThickness =  5.*mm;
    G4double  calorSizeXY  = 10.*cm;

    auto  layerThickness = absoThickness + gapThickness;
    auto  calorThickness = nofLayers * layerThickness;
    auto  worldSizeXY = 1.2 * calorSizeXY;
    auto  worldSizeZ  = 1.2 * calorThickness;

    // Get materials
    auto defaultMaterial = G4Material::GetMaterial("Galactic");

    //
    // World
    //
    G4Box* solidWorld
      = new G4Box("World",           // its name
                   worldSizeXY/2, worldSizeXY/2, worldSizeZ/2); // its size

    logicWorld
      = new G4LogicalVolume(
                   solidWorld,           // its solid
                   defaultMaterial,  // its material
                   "World");         // its name

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
    // Geometry parameters
    G4int  nofLayers = 10;
    G4double  absoThickness = 10.*mm;
    G4double  gapThickness =  5.*mm;
    G4double  calorSizeXY  = 10.*cm;

    auto  layerThickness = absoThickness + gapThickness;
    auto  calorThickness = nofLayers * layerThickness;


    // Get materials
    auto defaultMaterial = G4Material::GetMaterial("Galactic");
    auto absorberMaterial = G4Material::GetMaterial("G4_Pb");
    auto gapMaterial = G4Material::GetMaterial("liquidArgon");

    if ( ! defaultMaterial || ! absorberMaterial || ! gapMaterial ) {
      G4ExceptionDescription msg;
      msg << "Cannot retrieve materials already defined.";
      G4Exception("B4DetectorConstruction::DefineVolumes()",
        "MyCode0001", FatalException, msg);
    }



    //
    // Calorimeter
    //
    auto calorimeterS
      = new G4Box("Calorimeter",     // its name
                   calorSizeXY/2, calorSizeXY/2, calorThickness/2); // its size

    calorLV
      = new G4LogicalVolume(
                   calorimeterS,    // its solid
                   defaultMaterial, // its material
                   "Calorimeter");  // its name

    new G4PVPlacement(
                   0,                // no rotation
                   G4ThreeVector(),  // at (0,0,0)
                   calorLV,          // its logical volume
                   "Calorimeter",    // its name
                   logicWorld,          // its mother  volume
                   false,            // no boolean operation
                   0,                // copy number
                   fCheckOverlaps);  // checking overlaps

    //
    // Layer
    //
    auto layerS
      = new G4Box("Layer",           // its name
                   calorSizeXY/2, calorSizeXY/2, layerThickness/2); // its size

    auto layerLV
      = new G4LogicalVolume(
                   layerS,           // its solid
                   defaultMaterial,  // its material
                   "Layer");         // its name

    new G4PVReplica(
                   "Layer",          // its name
                   layerLV,          // its logical volume
                   calorLV,          // its mother
                   kZAxis,           // axis of replication
                   nofLayers,        // number of replica
                   layerThickness);  // witdth of replica

    //
    // Absorber
    //
    auto absorberS
      = new G4Box("Abso",            // its name
                   calorSizeXY/2, calorSizeXY/2, absoThickness/2); // its size

    auto absorberLV
      = new G4LogicalVolume(
                   absorberS,        // its solid
                   absorberMaterial, // its material
                   "AbsoLV");          // its name

     new G4PVPlacement(
                   0,                // no rotation
                   G4ThreeVector(0., 0., -gapThickness/2), //  its position
                   absorberLV,       // its logical volume
                   "Abso",           // its name
                   layerLV,          // its mother  volume
                   false,            // no boolean operation
                   0,                // copy number
                   fCheckOverlaps);  // checking overlaps

    //
    // Gap
    //
    auto gapS
      = new G4Box("Gap",             // its name
                   calorSizeXY/2, calorSizeXY/2, gapThickness/2); // its size

    auto gapLV
      = new G4LogicalVolume(
                   gapS,             // its solid
                   gapMaterial,      // its material
                   "GapLV");      // its name

    new G4PVPlacement(
                   0,                // no rotation
                   G4ThreeVector(0., 0., absoThickness/2), //  its position
                   gapLV,            // its logical volume
                   "Gap",            // its name
                   layerLV,          // its mother  volume
                   false,            // no boolean operation
                   0,                // copy number
                   fCheckOverlaps);  // checking overlaps

    //
    // print parameters
    //
    G4cout
      << G4endl
      << "------------------------------------------------------------" << G4endl
      << "---> The calorimeter is " << nofLayers << " layers of: [ "
      << absoThickness/mm << "mm of " << absorberMaterial->GetName()
      << " + "
      << gapThickness/mm << "mm of " << gapMaterial->GetName() << " ] " << G4endl
      << "------------------------------------------------------------" << G4endl;

}

void DetectorConstruction::DefineVisAttributes()
{
    //
    // Visualization attributes
    //
    logicWorld->SetVisAttributes (G4VisAttributes::GetInvisible());

    auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    simpleBoxVisAtt->SetVisibility(true);
    calorLV->SetVisAttributes(simpleBoxVisAtt);
}

void DetectorConstruction::DefineSensitiveDetector()
{
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
    //
    // Scorers
    //

    // declare Absorber as a MultiFunctionalDetector scorer
    //
    auto absDetector = new G4MultiFunctionalDetector("Absorber");
    G4SDManager::GetSDMpointer()->AddNewDetector(absDetector);

    G4VPrimitiveScorer* primitive;
    primitive = new G4PSEnergyDeposit("Edep");
    absDetector->RegisterPrimitive(primitive);

    primitive = new G4PSTrackLength("TrackLength");
    auto charged = new G4SDChargedFilter("chargedFilter");
    primitive ->SetFilter(charged);
    absDetector->RegisterPrimitive(primitive);

    SetSensitiveDetector("AbsoLV",absDetector);

    // declare Gap as a MultiFunctionalDetector scorer
    //
    auto gapDetector = new G4MultiFunctionalDetector("Gap");
    G4SDManager::GetSDMpointer()->AddNewDetector(gapDetector);

    primitive = new G4PSEnergyDeposit("Edep");
    gapDetector->RegisterPrimitive(primitive);

    primitive = new G4PSTrackLength("TrackLength");
    primitive ->SetFilter(charged);
    gapDetector->RegisterPrimitive(primitive);

    SetSensitiveDetector("GapLV",gapDetector);
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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineVolumes()
{
    DefineWorldVolume(1,1,1);
    DefineTargetVolume();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{
    DefineSensitiveDetector();
    DefineMagField();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
