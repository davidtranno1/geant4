//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
// $Id: G4VLeadingParticleBiasing.hh,v 1.3 2002/12/13 09:06:26 gcosmo Exp $
// GEANT4 tag $Name: geant4-05-00 $
//
// --------------------------------------------------------------------
#ifndef G4VLeadingParticleBiasing_h
#define G4VLeadingParticleBiasing_h

class G4VParticleChange;

class G4VLeadingParticleBiasing 
{
  public:
  
  virtual G4VParticleChange * Bias(G4VParticleChange * result) = 0;
};

#endif