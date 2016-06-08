// G4 Gheisha High Energy model class -- header file
// H. Fesefeldt, RWTH Aachen 23-October-1996
// Last modified: 10-December-1996

// A prototype of the Gheisha High Energy collision model.

#ifndef G4HEXiMinusInelastic_h
#define G4HEXiMinusInelastic_h 1

#include "G4HEInelastic.hh"

class G4HEXiMinusInelastic : public G4HEInelastic  
{
 public: 
        G4HEXiMinusInelastic() : G4HEInelastic()
           {
             G4int    vecLen       = 0;
           }

        ~G4HEXiMinusInelastic(){ };
         
        G4int vecLength;
        
        G4VParticleChange * ApplyYourself( const G4Track &aTrack, G4Nucleus &targetNucleus );

        G4int  GetNumberOfSecondaries()
               { return vecLength; }         

 private:

        void   FirstIntInCasXiMinus(G4bool &inElastic, const G4double availableEnergy,
                                    G4HEVector pv[],
                                    G4int &vecLen, 
                                    G4HEVector incidentParticle,
                                    G4HEVector targetParticle,
                                    const G4double atomicWeight);
};
#endif                     
                                         
