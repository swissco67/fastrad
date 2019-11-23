#include "B1ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4Timer.hh"
#include "TrackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
extern G4Timer duration_;

B1ActionInitialization::B1ActionInitialization()
 : G4VUserActionInitialization()
{
  G4cout << "B1ActionInitialization!!!" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1ActionInitialization::~B1ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1ActionInitialization::BuildForMaster() const
{
  RunAction* runAction = new RunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1ActionInitialization::Build() const
{
  // Running Times
  duration_.Start();
  
  SetUserAction(new PrimaryGeneratorAction);

  RunAction* runAction = new RunAction;
  SetUserAction(runAction);
  
  EventAction* eventAction = new EventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new SteppingAction(eventAction));
  SetUserAction(new TrackingAction);
  
        duration_.Stop();

        G4cout << G4endl;
        G4cout << "Run Duration: " << duration_.GetRealElapsed()       << " s"  << G4endl;
        G4cout << "              " << duration_.GetRealElapsed()/60.   << " mn" << G4endl;
        G4cout << "              " << duration_.GetRealElapsed()/3600. << " h"  << G4endl;
        G4cout << G4endl;

}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
