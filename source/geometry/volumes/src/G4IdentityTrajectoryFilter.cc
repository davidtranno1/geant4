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
//
// $Id: G4IdentityTrajectoryFilter.cc,v 1.4 2003/02/06 18:53:16 gcosmo Exp $
// GEANT4 tag $Name: geant4-05-00-patch-01 $

#include "G4IdentityTrajectoryFilter.hh"

G4IdentityTrajectoryFilter::G4IdentityTrajectoryFilter()
{
}

G4IdentityTrajectoryFilter::~G4IdentityTrajectoryFilter()
{
}

void
G4IdentityTrajectoryFilter::TakeIntermediatePoint( G4ThreeVector newPoint )
{
  // Just store every single point, initially. (jacek 30/10/2002)
  // Implement more sophisticated filters later.  Copy by value into
  // the vector; the vector will never be copied by value itself. In
  // the final version, will probably want to create the intermediate
  // points at this stage.
  fpFilteredPoints->push_back( newPoint );
  G4cout << "spong: G4IdentityTrajectoryFilter::TakeIntermediatePoint"
         << G4endl;
}