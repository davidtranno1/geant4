// This code implementation is the intellectual property of
// the GEANT4 collaboration.
//
// By copying, distributing or modifying the Program (or any work
// based on the Program) you indicate your acceptance of this statement,
// and all its terms.
//
// $Id: G4Types.hh,v 1.3 1999/11/16 17:40:48 gcosmo Exp $
// GEANT4 tag $Name: geant4-01-00 $
//
//
// GEANT4 native types
//
// History:

#ifndef G4TYPES_HH
#define G4TYPES_HH

#include <CLHEP/config/CLHEP.h>

// Define G4std namespace for standard std.
// Needed to allow both ISO/not-ISO ANSI compliant code installations
//
#ifndef G4USE_STD_NAMESPACE
  #define G4std
#else
  #define G4std std
#endif

// Typedefs to decouple from library classes
// Typedefs for numeric types
//
typedef HepDouble G4double;
typedef HepFloat G4float;
typedef HepInt G4int;
#ifdef G4_HAVE_BOOL
  typedef bool G4bool;
#else
  typedef HepBoolean G4bool;
#endif
typedef long G4long;

#endif /* G4TYPES_HH */