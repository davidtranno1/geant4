//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: G4DNAHeliumChargeIncrease.hh,v 1.2 2006/06/29 19:34:18 gunter Exp $
// GEANT4 tag $Name: geant4-08-02 $

#ifndef   G4DNAHELIUMCHARGEINCREASE_HH
 #define  G4DNAHELIUMCHARGEINCREASE_HH 1

 #include "G4DNAChargeIncreaseInWater.hh"
 #include "G4DNADingfelderChargeChangeTotalCrossSectionPolicy.hh"
 #include "G4DNAHeliumChargeIncreaseFinalStatesPolicy.hh"
 #include "G4DNAStopAndKillBelowEnergyLimitPolicy.hh"

 class G4DNAHeliumChargeIncreaseEnergyLimitsPolicy
 {
  protected:
                      G4DNAHeliumChargeIncreaseEnergyLimitsPolicy();

   const G4double     lowEnergyLimit;
   const G4bool       zeroBelowLowEnergyLimit;
   const G4double     highEnergyLimit;
   const G4bool       zeroAboveHighEnergyLimit;
 };

 class G4DNAHeliumChargeIncreaseIncomingParticlePolicy
 {
  protected:
                                        G4DNAHeliumChargeIncreaseIncomingParticlePolicy();
   const G4ParticleDefinition *         IncomingParticleDefinition(void) const;

   G4int                                NumberOfPartialCrossSections(void) const;

   G4double                             f0[2];
   G4double                             a0[2];
   G4double                             a1[2];
   G4double                             b0[2];
   G4double                             b1[2];
   G4double                             c0[2];
   G4double                             d0[2];
   G4double                             x0[2];
   G4double                             x1[2];
 };

 class G4DNAHeliumChargeIncrease : public G4DNAChargeIncreaseInWater<G4DNADingfelderChargeChangeTotalCrossSectionPolicy<G4DNAHeliumChargeIncreaseIncomingParticlePolicy, G4DNAHeliumChargeIncreaseEnergyLimitsPolicy>, G4DNAHeliumChargeIncreaseFinalStatesPolicy<G4DNAHeliumChargeIncreaseEnergyLimitsPolicy> >
 {
  public:
                                         G4DNAHeliumChargeIncrease(const G4String & name = "G4DNAHeliumChargeIncrease") : G4DNAChargeIncreaseInWater<G4DNADingfelderChargeChangeTotalCrossSectionPolicy<G4DNAHeliumChargeIncreaseIncomingParticlePolicy, G4DNAHeliumChargeIncreaseEnergyLimitsPolicy>, G4DNAHeliumChargeIncreaseFinalStatesPolicy<G4DNAHeliumChargeIncreaseEnergyLimitsPolicy> > (name) {}
   virtual                              ~G4DNAHeliumChargeIncrease() {}
 };
#endif /* G4DNAHELIUMCHARGEINCREASE_HH */