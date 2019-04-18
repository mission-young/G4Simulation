#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Colour.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"
DetectorConstruction::DetectorConstruction()
    :G4VUserDetectorConstruction(),fScoringVolume(nullptr){
    fCheckOverLaps=true;
    //Construct();
}

DetectorConstruction::~DetectorConstruction()
{

}

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

    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

void DetectorConstruction::DefineVolumes()
{
    DefineWorldVolume(10*cm,10*cm,20*cm);
    DefineTargetVolume();
    DefineChamberVolume();
    DefineOtherVolume();
}

void DetectorConstruction::DefineWorldVolume(G4double x,G4double y,G4double z)
{
    G4Box* solidWorld=new G4Box("World",0.5*x,0.5*y,0.5*z);
    logicWorld = new G4LogicalVolume(solidWorld,G4Material::GetMaterial("G4_AIR"),"World");
    physicsWorld=new G4PVPlacement(0,G4ThreeVector(),logicWorld,"World",0,false,0,fCheckOverLaps);
}

void DetectorConstruction::DefineTargetVolume()
{

}

void DetectorConstruction::DefineChamberVolume()
{

}

void DetectorConstruction::DefineOtherVolume()
{

}

void DetectorConstruction::DefineVisAttributes()
{
    logicWorld->SetVisAttributes(new G4VisAttributes(G4Colour(1,1,1)));
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    DefineMaterials();
    DefineVolumes();
    DefineVisAttributes();
    fScoringVolume=logicWorld;
    return physicsWorld;
}

G4LogicalVolume *DetectorConstruction::GetScoringVolume() const
{
    return fScoringVolume;
}


void DetectorConstruction::SetCheckOverlaps(G4bool checkOverLaps)
{
    fCheckOverLaps=checkOverLaps;
}
