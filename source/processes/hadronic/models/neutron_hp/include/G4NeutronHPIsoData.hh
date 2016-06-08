// This code implementation is the intellectual property of
// neutron_hp -- header file
// J.P. Wellisch, Nov-1996
// A prototype of the low energy neutron transport model.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4NeutronHPIsoData.hh,v 2.4 1998/12/04 15:08:04 hpw Exp $
// GEANT4 tag $Name: geant4-00 $
//
#ifndef G4NeutronHPIsoData_h
#define G4NeutronHPIsoData_h 1

 // Hadronic Process: Very Low Energy Neutron X-Sections
 // original by H.P. Wellisch, TRIUMF, 14-Feb-97
 // Has the Cross-section data for on isotope.
 
#include "globals.hh"
#include "G4ios.hh"
#include <fstream.h>
#ifdef WIN32
  #include <strstrea.h>
#else
  #include <strstream.h>
#endif
#include <stdlib.h>
#include "G4NeutronHPVector.hh"
#include "G4NeutronHPNames.hh"

class G4NeutronHPIsoData
{
public:

  G4NeutronHPIsoData(){theChannelData = NULL;}
  
  ~G4NeutronHPIsoData(){if(theChannelData!=NULL) delete theChannelData;}
  
  inline G4double GetXsec(G4double energy)
  {
    return theChannelData->GetXsec(energy);
  }
  G4bool Init(G4int A, G4int Z, G4double abun, G4String dirName, G4String aFSType);
  
  void Init(G4int A, G4int Z, G4double abun); //fill PhysicsVector for this Isotope
  
  inline G4NeutronHPVector * MakeElasticData()
    {return theElasticData;}
  inline G4NeutronHPVector * MakeFissionData()
    {return theFissionData;}
  inline G4NeutronHPVector * MakeCaptureData()
    {return theCaptureData;}
  inline G4NeutronHPVector * MakeInelasticData()
    {return theInelasticData;}
  inline G4NeutronHPVector * MakeChannelData()
    {return theChannelData;}

  G4String GetName(G4int A, G4int Z, G4String base, G4String rest);
  
  inline void FillChannelData(G4NeutronHPVector * aBuffer)
  {
    if(theChannelData!=NULL) G4Exception("IsoData has channel full already!!!");
    theChannelData = new G4NeutronHPVector;
    for(G4int i=0; i<aBuffer->GetVectorLength(); i++)
    {
      theChannelData->SetPoint(i, aBuffer->GetPoint(i));
    }
  }
  
private:

  G4NeutronHPVector * theFissionData;
  G4NeutronHPVector * theCaptureData;
  G4NeutronHPVector * theElasticData;
  G4NeutronHPVector * theInelasticData;
  G4NeutronHPVector * theChannelData;

  G4String theFileName;
  G4NeutronHPNames theNames;
};

#endif