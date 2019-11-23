/****************************************************************
* EventAction.cc
* Implementation file for class: EventAction
* (Geant4 compatible class)
*
* Project: Ht
*
*
* Neither the authors of this software system, nor their employing 
* institutes,nor the agencies providing financial support for this 
* work  make  any representation or  warranty, express or implied, 
* regarding  this  software system or assume any liability for its 
* use.                                                             
*
*
* Creation: 2019/11/22 by Fastrad ((C) 2019)
* Last Modified: 
*****************************************************************/

#include "EventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

#include "Histogram.hh"
#include "G4ThreeVector.hh"
#include <vector>
#include "TrackerSD.hh"
#include "RunAction.hh"
#include "G4RunManager.hh"

extern std::vector<SensitiveVolume*>   listeVS_;
//------------------------------------------------------------------

EventAction::EventAction(RunAction* runAction)
: G4UserEventAction()
{
}

EventAction::~EventAction()
{
}

//------------------------------------------------------------------

void EventAction::BeginOfEventAction(const G4Event*)
{

	for (unsigned int i = 0; i < listeVS_.size(); ++i)
	{
		listeVS_[i]->InitialisationDebutDuTir();
	}
}

void EventAction::EndOfEventAction(const G4Event* evt)
{
	for (unsigned int i = 0; i < listeVS_.size(); ++i)
	{
		listeVS_[i]->TraitementFinDuTir(evt);
	}

    G4int event_id = evt->GetEventID();

    // get number of stored trajectories

    G4TrajectoryContainer* trajectoryContainer = evt->GetTrajectoryContainer();
    G4int n_trajectories = 0;
    if (trajectoryContainer)
    {
        n_trajectories = trajectoryContainer->entries();
    }

    // periodic printing

    if (event_id < 10000 || event_id%10000 == 0) 
    {
//        G4cout << ">>> Event " << evt->GetEventID() << G4endl;
//        G4cout << "    " << n_trajectories 
//            << " trajectories stored in this event." << G4endl;
    }

    // extract the trajectories and draw them

    if (G4VVisManager::GetConcreteInstance())
    {
        for (G4int i=0; i<n_trajectories; i++) 
        { 
            G4Trajectory* trj = (G4Trajectory*)
	                            ((*(evt->GetTrajectoryContainer()))[i]);
            trj->DrawTrajectory();
        }
    }
}
