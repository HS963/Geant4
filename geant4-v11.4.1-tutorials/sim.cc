#include <iostream>
#include <memory>
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "PMPhysicsList.hh"
#include "PMDetectorConstruction.hh"
#include "PMActionInitialization.hh"

int main(int argc, char** argv)
{
#ifdef G4MULTITHREADED
    auto runManager = std::make_unique<G4MTRunManager>();
#else
    auto runManager = std::make_unique<G4RunManager>();
#endif

    runManager->SetUserInitialization(new PMDetectorConstruction());
    runManager->SetUserInitialization(new PMPhysicsList());
    runManager->SetUserInitialization(new PMActionInitialization());

    auto visManager = std::make_unique<G4VisExecutive>();
    visManager->Initialize();

    std::unique_ptr<G4UIExecutive> ui;
    if (argc == 1)
    {
        ui = std::make_unique<G4UIExecutive>(argc, argv);
        G4UImanager* UImanager = G4UImanager::GetUIpointer();
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
    }
    else
    {
        G4UImanager* UImanager = G4UImanager::GetUIpointer();
        G4String command = "/control/execute ";
        G4String filename = argv[1];
        UImanager->ApplyCommand(command + filename);
    }

    return 0;
}