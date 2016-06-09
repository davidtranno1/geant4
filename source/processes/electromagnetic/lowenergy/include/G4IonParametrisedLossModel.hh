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
//
// ===========================================================================
// GEANT4 class header file
//
// Class:                G4IonParametrisedLossModel
//
// Base class:           G4VEmModel (utils)
// 
// Author:               Anton Lechner (Anton.Lechner@cern.ch)
//
// First implementation: 10. 11. 2008
//
// Modifications:
//
//
// Class description:
//    Model for computing the energy loss of ions by employing a 
//    parameterisation of dE/dx tables (default ICRU 73 tables). For 
//    ion-material combinations and/or projectile energies not covered 
//    by this model, the G4BraggIonModel and G4BetheBloch models are
//    employed.
//
// Comments:
//
// =========================================================================== 


#ifndef G4IONPARAMETRISEDLOSSMODEL_HH
#define G4IONPARAMETRISEDLOSSMODEL_HH

#include "G4VEmModel.hh"
#include "G4EmCorrections.hh"
#include "G4IonParametrisedLossTable.hh"
#include "G4EmCorrections.hh"
#include <iomanip>
#include <list>
#include <map>
#include <utility>

class G4BraggIonModel;
class G4BetheBlochModel;
class G4ParticleChangeForLoss;

typedef std::list<G4IonLossTableHandle*> LossTableList;
typedef std::pair<const G4ParticleDefinition*, const G4Material*> IonMatCouple;


class G4IonParametrisedLossModel : public G4VEmModel {

 public:
   G4IonParametrisedLossModel(const G4ParticleDefinition* particle = 0,
                              const G4String& name = "ParamICRU73");

   virtual ~G4IonParametrisedLossModel();

   virtual void Initialise(
                           const G4ParticleDefinition*, // Projectile
                           const G4DataVector&); // Cut energies

   virtual G4double MinEnergyCut(
                                 const G4ParticleDefinition*,  // Projectile
		        	 const G4MaterialCutsCouple*);

   virtual G4double ComputeCrossSectionPerAtom(
                                 const G4ParticleDefinition*, // Projectile
				 G4double,  // Kinetic energy of projectile
				 G4double,  // Atomic number
                                 G4double,  // Mass number
				 G4double,  // Energy cut for secondary prod.
				 G4double); // Maximum energy of secondaries
				 				 
   virtual G4double CrossSectionPerVolume(
                                 const G4Material*,  // Target material
				 const G4ParticleDefinition*, // Projectile
				 G4double,  // Kinetic energy
				 G4double,  // Energy cut for secondary prod.
				 G4double); // Maximum energy of secondaries
				 
   virtual G4double ComputeDEDXPerVolume(
                                 const G4Material*, // Target material
				 const G4ParticleDefinition*, // Projectile
				 G4double,  // Kinetic energy of projectile
				 G4double); // Energy cut for secondary prod.

   // Function, which computes the continuous energy loss (due to electronic
   // stopping) for a given pre-step energy and step length by using
   // range vs energy (and energy vs range) tables  
   G4double ComputeLossForStep(
                                 const G4Material*, // Target material
				 const G4ParticleDefinition*, // Projectile
				 G4double,  // Kinetic energy of projectile
                                 G4double,  // Energy cut for secondary prod.
				 G4double); // Length of current step

   // Function, which computes the mean energy transfer rate to delta rays 
   G4double DeltaRayMeanEnergyTransferRate(
                                 const G4Material*, // Target Material
			         const G4ParticleDefinition*, // Projectile
				 G4double,  // Kinetic energy of projectile
				 G4double); // Energy cut for secondary prod.


   virtual void SampleSecondaries(std::vector<G4DynamicParticle*>*,
				 const G4MaterialCutsCouple*,
				 const G4DynamicParticle*,
				 G4double,  // Energy cut for secondary prod.
                                 G4double); // Maximum energy of secondaries

   virtual G4double GetChargeSquareRatio(
                                 const G4ParticleDefinition*, // Projectile
		 	 	 const G4Material*,  // Target Material
				 G4double); // Kinetic energy of projectile

   virtual G4double GetParticleCharge(
                                 const G4ParticleDefinition*, // Projectile
				 const G4Material*,  // Target Material
				 G4double); // Kinetic energy of projectile 

   virtual void CorrectionsAlongStep(
                                 const G4MaterialCutsCouple*,// Mat.-Cut couple
				 const G4DynamicParticle*,  // Dyn. particle
				 G4double&, // Energy loss in current step
				 G4double&, 
				 G4double); // Length of current step


   // Template function which allows to add additional stopping power tables
   // in combination with a scaling algorithm, which may depend on dynamic
   // information like the current particle energy (the table and scaling 
   // algorithm are used via a wrapper class, which performs e.g.caching or
   // which applies the scaling of energy and dE/dx values)
   template <class TABLE, class SCALING_ALGO>
   void AddDEDXTable() {
       G4IonLossTableHandle* table =
               new G4IonParametrisedLossTable<TABLE, SCALING_ALGO>;      
 
       lossTableList.push_front(table);
   }

   // Template function which allows to add additional stopping power tables
   // (the table itself is used via a wrapper class, which performs e.g.
   // caching)
   template <class TABLE>
   void AddDEDXTable() {
       G4IonLossTableHandle* table =
               new G4IonParametrisedLossTable<TABLE>;      
 
       lossTableList.push_front(table);
   }

   // Function checking the applicability of physics tables to ion-material
   // combinations (Note: the energy range of tables is not checked)
   LossTableList::iterator IsApplicable(
                      const G4ParticleDefinition*,  // Projectile (ion) 
                      const G4Material*);           // Target material

   // Function printing a dE/dx table for a given ion-material combination
   // and a specified energy grid 
   void PrintDEDXTable(
                      const G4ParticleDefinition*,  // Projectile (ion) 
                      const G4Material*, // Absorber material
                      G4double,          // Minimum energy per nucleon
                      G4double,          // Maximum energy per nucleon
                      G4int,             // Number of bins
                      G4bool);           // Logarithmic scaling of energy
   
 protected:
   G4double MaxSecondaryEnergy(const G4ParticleDefinition*,
			       G4double);   // Kinetic energy of projectile

 private:
   // Function which updates parameters concerning the dE/dx calculation
   // (the parameters are only updated if the particle, the material or 
   // the associated energy cut has changed)
   void UpdateDEDXCache(
                  const G4ParticleDefinition*,   // Projectile (ion) 
                  const G4Material*,             // Target material
                  G4double cutEnergy);           // Energy cut

   // Function, which updates parameters concering particle properties
   void UpdateCache(
                  const G4ParticleDefinition*);  // Projectile (ion) 
 
   // Function, which builds range vs energy (and energy vs range) vectors
   // for a given particle, material and energy cut   
   void BuildRangeVector(
                  const G4ParticleDefinition*,   // Projectile (ion) 
                  const G4Material*,             // Target material
                  G4double);                     // Energy cut

   // Assignment operator and copy constructor are hidden:
   G4IonParametrisedLossModel & operator=(
                              const G4IonParametrisedLossModel &right);
   G4IonParametrisedLossModel(const G4IonParametrisedLossModel &);
   
   // ######################################################################
   // # Models and dE/dx tables for computing the energy loss 
   // # 
   // ######################################################################

   // G4BraggIonModel and G4BetheBlochModel are used for ion-target
   // combinations and/or projectile energies not covered by parametrisations
   // adopted by this model:
   G4BraggIonModel* braggIonModel;
   G4BetheBlochModel* betheBlochModel;

   // List of dE/dx tables plugged into the model
   LossTableList lossTableList;

   // ######################################################################
   // # Maps of Range vs Energy and Energy vs Range vectors
   // # 
   // ######################################################################

   typedef std::map<IonMatCouple, G4LPhysicsFreeVector*> RangeEnergyTable; 
   RangeEnergyTable r;

   typedef std::map<IonMatCouple, G4LPhysicsFreeVector*> EnergyRangeTable; 
   EnergyRangeTable E;

   // ######################################################################
   // # Energy grid definitions (e.g. used for computing range-energy 
   // # tables)
   // ######################################################################

   G4double lowerEnergyEdgeIntegr;
   G4double upperEnergyEdgeIntegr;

   size_t nmbBins;
   size_t nmbSubBins;

   // ######################################################################
   // # Particle change for loss
   // # 
   // ######################################################################

   // Pointer to particle change object, which is used to set e.g. the
   // energy loss due to nuclear stopping
   G4ParticleChangeForLoss* particleChangeLoss;

   // Flag indicating if model is initialized (i.e. if 
   // G4ParticleChangeForLoss was created)
   G4bool modelIsInitialised;

   // ######################################################################
   // # Corrections and energy loss limit
   // # 
   // ######################################################################
   
   // Pointer to an G4EmCorrections object, which is used to compute the
   // effective ion charge, and other corrections (like high order corrections
   // to stopping powers) 
   G4EmCorrections* corrections;

   // Corrections factor for effective charge, computed for each particle
   // step
   G4double corrFactor;

   // Parameter indicating the maximal fraction of kinetic energy, which
   // a particle may loose along a step, in order that the simple relation
   // (dE/dx)*l can still be applied to compute the energy loss (l = step 
   // length)
   G4double energyLossLimit;

   // ######################################################################
   // # Cut energies and properties of generic ion
   // # 
   // ######################################################################

   // Vector containing the current cut energies (the vector index matches
   // the material-cuts couple index):
   G4DataVector cutEnergies;

   // Pointer to generic ion and mass of generic ion
   G4ParticleDefinition* genericIon;
   G4double genericIonPDGMass;

   // ######################################################################
   // # "Most-recently-used" cache parameters
   // #
   // ######################################################################

   // Cached key (particle) and value information for a faster 
   // access of particle-related information
   const G4ParticleDefinition* cacheParticle; // Key: Current projectile
   G4double cacheMass;                        // Projectile mass
   G4double cacheElecMassRatio;               // Electron-mass ratio
   G4double cacheChargeSquare;                // Charge squared

   // Cached parameters needed during dE/dx computations:
   const G4ParticleDefinition* dedxCacheParticle; // Key: 1) Current ion,
   const G4Material* dedxCacheMaterial;           //      2) material and
   G4double dedxCacheEnergyCut;                   //      3) cut energy 
   LossTableList::iterator dedxCacheIter;         // Responsible dE/dx table
   G4PhysicsVector* dedxCacheEnergyRange;         // Energy vs range vector
   G4PhysicsVector* dedxCacheRangeEnergy;         // Range vs energy vector
   G4double dedxCacheTransitionEnergy;      // Transition energy between
                                            // parameterization and 
                                            // Bethe-Bloch model
   G4double dedxCacheTransitionFactor;      // Factor for smoothing the dE/dx
                                            // values in the transition region
   G4double dedxCacheGenIonMassRatio;       // Ratio of generic ion mass       
                                            // and current particle mass
};


#include "G4IonParametrisedLossModel.icc"

#endif